
#pragma warning( disable : 6385 6386 )

#include "Unpacker.h"

#define ZLIB_CONST
#include "zlib/zlib.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"

#include "BinaryDataTools.h"


// --- Constants --------------------------------------------------------------

#define ZLIB_COMPR_LOW "\x78\x01"
#define ZLIB_COMPR_STD "\x78\x9c"
#define ZLIB_COMPR_HGH "\x78\xda"

#define ZLIB_START   ZLIB_COMPR_STD
#define ZLIB_END     "\x00\x00\xff\xff"

#define CHUNK_SIZE (1024 * 64)

// --- File IO ----------------------------------------------------------------

static int32 LoadPackedSaveData(char const* filename, uint8** out)
{
    FILE* fp = fopen(filename, "rb");

    if (!fp)
    {
        printf("ERROR: Couldn't open %s!\n", filename);
        return -1;
    }

    // get file size
    fseek(fp, 0L, SEEK_END);
    int32 size = ftell(fp);
    rewind(fp);

    int32 bufSize = size + 1;

    // create a buffer to store it
    uint8* buffer = (uint8*)malloc(bufSize);
    if (!buffer)
    {
        printf("ERROR: Failed to allocate buffer of size %d.\n", bufSize);
        return -1;
    }

    size_t rdCnt = fread(buffer, sizeof * buffer, bufSize, fp);
    buffer[size] = '\0';
    fclose(fp);

    if (rdCnt != size)
        printf("WARNING: Full file wasn't read: size %d - read %d\n", size, rdCnt);


    uint8 bckup = buffer[4];
    buffer[4] = 0;
    printf("The first 4 characters should be 'CIV6': %s\n", buffer);
    buffer[4] = bckup;

    if (out)
        *out = buffer;
    return rdCnt;
}

static void SaveToFile(char const* filename, uint8 const* data, uint32 size)
{
    if (!data || !size)
    {
        printf("ERROR: No data to save for %s", filename);
        return;
    }

    FILE* fp = fopen(filename, "wb");

    if (!fp)
    {
        printf("ERROR: Couldn't open %s!\n", filename);
        return;
    }


    size_t written = fwrite(data, sizeof *data, size, fp);
    fclose(fp);

    if (written != size)
        printf("ERROR: Not all data in the buffer was written: payload %d - written %d\n", size, written);
}


// --- Data Extraction --------------------------------------------------------

static int32 inflateZlib(uint8 const* zlib, uint8 const* zlibEnd, uint8** out)
{
    size_t srcSize = zlibEnd - zlib;
    size_t srcChunks = srcSize / CHUNK_SIZE;
    size_t srcRemnant = srcSize % CHUNK_SIZE;
    // data chunks + last chunk but sans chunk buffer of 4 bytes
    size_t packedSize = srcChunks * CHUNK_SIZE + srcRemnant - 4 * srcChunks;

    uint8* packedData = (uint8*)malloc(packedSize);
    if (!packedData)
    {
        printf("ERROR: Couldn't allocate buffer for packed data!\n");
        return -1;
    }

    uint8 const* it = zlib;
    uint8* ins = packedData;
    // pack in the primary chunks
    for (uint32 i = 0; i < srcChunks; ++i, ins += CHUNK_SIZE)
    {
        memcpy(ins, it, CHUNK_SIZE);
        it += CHUNK_SIZE;
        printf("   Chunk padding is: '%02x%02x%02x%02x'\n", it[0], it[1], it[2], it[3]);
        it += 4;
    }


    // allocate a 1 MB buffer for decompressing data
    uint32 quarterGB = 1024 * 1024 * 256;
    uint8* decompressed = (uint8*)malloc(quarterGB);
    if (!decompressed)
    {
        printf("ERROR: Couldn't allocate 1 MB buffer for decompressing save data.\n");
        return -1;
    }

    // inflate the zlib
    z_stream strm;
    strm.next_in = packedData;
    strm.avail_in = packedSize;
    strm.next_out = decompressed;
    strm.avail_out = quarterGB;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;

    int res = Z_OK;
    if ((res = inflateInit(&strm)) != Z_OK)
    {
        printf("ERROR: An error occured initializing inflation: %d - %s\n", res, strm.msg);
        return -1;
    }

    if ((res = inflate(&strm, Z_SYNC_FLUSH)) != Z_OK)
    {
        printf("ERROR: An error occured while inflating: %d - %s\n", res, strm.msg);
        return -1;
    }

    if ((res = inflateEnd(&strm)) != Z_OK)
    {
        printf("ERROR: An error occured ending inflation: %d - %s\n", res, strm.msg);
        return -1;
    }

    // print the first 160 bytes
    printf("The first 160 bytes:\n");
    uint32 i = 0;
    for (uint32 j = 0; j < 10; ++j)
    {
        printf("   ");
        for (uint32 k = 0; k < 16; ++k, ++i)
            printf("%02x", decompressed[i]);
        putc('\n', stdout);
    }
    putc('\n', stdout);


    free(packedData);

    if (out)
        *out = decompressed;
    return strm.total_out;
}

void UnpackSave(char const* filename, SaveData* out)
{
    uint8* data;
    int32 len = LoadPackedSaveData(filename, &data);
    if (!data || len <= 0)
    {
        printf("Either no file or data data found!\n");
        return;
    }

    static const uint8  zlibStartSeq[] = ZLIB_START;
    static const uint32 zlibStartLen = sizeof zlibStartSeq - 1;
    static const uint8* zlibStartSeqEnd = zlibStartSeq + zlibStartLen;
    static const uint8  zlibEndSeq[] = ZLIB_END;
    static const uint32 zlibEndLen = sizeof zlibEndSeq - 1;
    static const uint8* zlibEndSeqEnd = zlibEndSeq + zlibEndLen;

    uint8 const* it = data;
    uint8 const* end = data + len;

    // find all instances of "MOD_TITLE"
    uint8 const modTitle[] = "MOD_TITLE";
    uint8 const modTitleLen = sizeof modTitle - 1;
    uint8 const* modTitleEnd = modTitle + modTitleLen;

    for (; it < end;)
    {
        uint8 const* title = FindFirstOfSubseq(it, end, modTitle, modTitleEnd);
        if (!title)
            break;
        printf("   %s found at offset %d\n", modTitle, title - data);
        it = title + modTitleLen;
    }

    uint8 const* zlib = FindFirstOfSubseq(it, end, zlibStartSeq, zlibStartSeqEnd);
    if (!zlib)
    {
        printf("ERROR: Couldn't find start of zlib, bad file\n");
        return;
    }
    uint8 const* zlibEnd = FindFirstOfSubseq(zlib, end, zlibEndSeq, zlibEndSeqEnd);
    if (!zlibEnd)
    {
        printf("ERROR: Couldn't find end of zlib, bad file\n");
        return;
    }
    zlibEnd += zlibEndLen;

    uint32 headerSize = zlib - data;
    uint32 zlibSize = zlibEnd - zlib;
    uint32 tailSize = end - it;
    printf("Header size is %d\n", headerSize);
    printf("Zlib size is %d\n", zlibSize);
    printf("Tail size is %d\n", tailSize);

    uint8* decompressedData = NULL;
    uint32 decompSize = inflateZlib(zlib, zlibEnd, &decompressedData);



    // Save off dat sections

    // get input name without extention
    char const* ext = strrchr(filename, '.');
    if (!ext)
    {
        uint32 len = strlen(filename);
        ext = filename + len;
    }
    uint32 nameSize = ext - filename;

    // create a name buffer
    char* name = (char*)malloc(nameSize + 50);
    if (!name)
    {
        printf("Name alloc failed.\n");
        return;
    }

    memcpy(name, filename, nameSize);

    static const char headerStr[] = "_0_header.dat";
    static const char gameDataStr[] = "_1_game_data.dat";
    static const char tailStr[] = "_2_tail.dat";
    memcpy(name + nameSize, headerStr, sizeof headerStr);
    SaveToFile(name, data, headerSize);
    memcpy(name + nameSize, gameDataStr, sizeof gameDataStr);
    SaveToFile(name, decompressedData, decompSize);
    memcpy(name + nameSize, tailStr, sizeof tailStr);
    SaveToFile(name, zlibEnd, tailSize);


    // reallocate fitted buffers for each dataset
    SaveData* save = out;

    save->header = (uint8*)malloc(headerSize);
    save->gamedata = (uint8*)malloc(decompSize);
    save->tail = (uint8*)malloc(tailSize);

    if (!save->header ||
        !save->gamedata ||
        !save->tail)
    {
        printf("Failed to alloc buffers for analyzing save data!\n");
        return;
    }

    save->headerEnd = save->header + headerSize;
    save->gamedataEnd = save->gamedata + decompSize;
    save->tailEnd = save->tail + tailSize;

    free(decompressedData);
    free(data);
}

void ReleaseSaveData(SaveData* save)
{

}
