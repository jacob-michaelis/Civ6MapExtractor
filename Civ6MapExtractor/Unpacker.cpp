
#pragma warning( disable : 6385 6386 )

#include "typedefs.h"

#include "zlib/zlib.h"

#include "stdlib.h"
#include "stdio.h"

#define ZLIB_COMPR_LOW "\x78\x01"
#define ZLIB_COMPR_STD "\x78\x9c"
#define ZLIB_COMPR_HGH "\x78\xda"

#define ZLIB_START ZLIB_COMPR_STD
#define ZLIB_END "\x00\x00\xff\xff"

static int32 LoadPackedSaveData(char const* filename, uint8** out)
{
    FILE* fp = fopen(filename, "rb");

    if (!fp)
    {
        printf("Couldn't open %s!\n", filename);
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
        printf("Failed to allocate buffer of size %d.\n", bufSize);
        return -1;
    }

    size_t rdCnt = fread(buffer, sizeof * buffer, bufSize, fp);
    fclose(fp);

    printf("Read %d bytes of data\n", rdCnt);

    uint8 bckup = buffer[4];
    buffer[4] = 0;
    printf("The first 4 characters should be 'CIV6': %s\n", buffer);
    buffer[4] = bckup;

    *out = buffer;
    return bufSize;
}

void UnpackSave(char const* filename)
{
    uint8* data;
    int32 len = LoadPackedSaveData(filename, &data);

    // break out the zlib bundles from the sub headers
    
    free(data);
}

