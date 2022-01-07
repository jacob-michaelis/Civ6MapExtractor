
#include "ParseHeader.h"

#include "stdio.h"
#include "string.h"

#include "BinaryDataTools.h"

#define BLOCK_LEN 32

#define PRINT_01 1
#define PRINT_02 1
#define PRINT_03 1
#define PRINT_04 1
#define PRINT_05 1
#define PRINT_06 1
#define PRINT_07 1
#define PRINT_08 1
#define PRINT_09 1
#define PRINT_0a 1
#define PRINT_0b 1
#define PRINT_0c 1
#define PRINT_0d 1
#define PRINT_0e 1
#define PRINT_0f 1
#define PRINT_10 1
#define PRINT_11 1
#define PRINT_12 1
#define PRINT_13 1
#define PRINT_14 1
#define PRINT_15 1
#define PRINT_16 1
#define PRINT_17 1
#define PRINT_18 1


static uint8 const unkTag[] = { 0x10, 0x07, 0x58, 0xf4, 0x05 };
static uint8 const unkTag0[] = { 0x2f, 0x52, 0x96, 0x1a, 0x02 };
static uint8 const unkTag1[] = { 0x95, 0xb9, 0x42, 0xce, 0x02 };
static uint8 const unkTag2[] = { 0x54, 0xb4, 0x8a, 0x0d, 0x02 };
static uint8 const unkTag3[] = { 0x31, 0xeb, 0x88, 0x62, 0x05 };
static uint8 const unkTag4[] = { 0x58, 0xba, 0x7f, 0x4c, 0x02 };
static uint8 const unkTag5[] = { 0x5b, 0x51, 0xd7, 0xc7, 0x02 };
static uint8 const unkTag6[] = { 0xb3, 0x36, 0xda, 0x2f, 0x03 };
static uint8 const unkTag7[] = { 0x8c, 0x54, 0xee, 0x04, 0x03 };
static uint8 const unkTag8[] = { 0x46, 0xfc, 0x0f, 0x83, 0x02 };
//static uint8 const unkTag[] = { 0x, 0x, 0x, 0x, 0x0 };


enum DataTag
{
    dtUID     = 0x04c45f54,
    dtModJson = 0x3034e172,
    dtCivJson = 0x760a632a,

    // Locale Tags
    dtDifficultyLocale = 0x0f32e71d,

    // Unknown:
    //   0x04ee548c
    //   0x0d8ab454
    //   0x1a96522f
    //   0x2fda36b3
    //   0x4c7fba58
    //   0x542a02a2
    //   0x6288eb31
    //   0x6db0f592
    //   0x830ffc46
    //   0x83f18cef
    //   0xc7d7515b
    //   0xce42b995
    //   0xd08444c1
    //   0xf4580710
    //   0x
};


enum BlockType
{
    btText     = 0x05,
    btTextWide = 0x06,
    btUnknown  = 0x18,
};

static uint8 const* ParseJSON(uint8 const* data, uint8 const* end)
{
    if (*data != '{')
    {
        printf("WARNING: First json character must be an opening bracket.");
        return data;
    }

    uint8 const* it = data;
    uint32 depth = 0;
    printf("\n   ");

    for (; it < end; ++it)
    {
        switch (*it)
        {
            // start section
        case '{':
            printf("{\n   ");
            ++depth;
            for (uint32 i = 0; i < depth; ++i)
                printf("   ");
            break;
            // end section
        case '}':
            printf("\n   ");
            --depth;
            for (uint32 i = 0; i < depth; ++i)
                printf("   ");
            putc('}', stdout);
            // exit if block finished
            break;
        case ':':
            printf(": ");
            break;
        case '[':
            printf("[\n   ");
            ++depth;
            for (uint32 i = 0; i < depth; ++i)
                printf("   ");
            break;
        case ']':
            printf("\n   ");
            --depth;
            for (uint32 i = 0; i < depth; ++i)
                printf("   ");
            putc(']', stdout);
            break;
        case ',':
            printf(",\n   ");
            for (uint32 i = 0; i < depth; ++i)
                printf("   ");
            break;
        default:
            if (*it >= 32 && *it < 128)
                putc(*it, stdout);
            else
                putc('.', stdout);
            break;
        }

        if (depth == 0)
            break;
    }

    ++it;
    return it;
}

static uint8 const* ParseString(uint8 const* data, uint8 const* end)
{
    if (*data == '{')
        return ParseJSON(data, end);

    printf("\n   ");
    uint32 cnt = printf("%s", data);

    return data + cnt;
}

static uint8 const* ParseWideString(uint8 const* data, uint8 const* end)
{
    printf("\n   ");
    uint32 cnt = printf("%S", (wchar_t const*)data);

    return data + cnt * 2 + 1;
}


static uint8 const* ParseText(uint8 const* data, uint8 const* end)
{
    uint32 blockType = *(uint32*)data;
    uint32 blockLen = *(uint32*)(data + 4) & 0xFFFFFF;
    uint8  blockExcl = *(data + 7);
    uint8  blockDataSize = *(data + 8);
    uint8  byte0 = *(data + 9);
    uint8  byte1 = *(data + 10);
    uint8  byte2 = *(data + 11);
    uint8  byte3 = *(data + 12);

    uint32 prevKey = *(uint32*)(data - 12);
    uint32 prevNum0 = *(uint32*)(data - 8);
    uint32 prevNum1 = *(uint32*)(data - 4);

    uint8 const* text = data + 12;

    switch (blockType)
    {
    case btText:
        if (blockExcl == '\x21' && blockDataSize == 1)
        {
            //printf("\n   Text Length: %d", blockLen);
            return ParseString(text, end);
        }
        //else if (
        //    byte0 == '\x54' &&
        //    byte1 == '\x5f' &&
        //    byte2 == 0xc4 &&
        //    byte3 == '\x04')
        //{
        //    printf("\n   Mod Details:");
        //    return text;
        //}
        //else if (!memcmp(data + 4, unkTag0, sizeof unkTag0)
        //    || !memcmp(data + 4, unkTag4, sizeof unkTag4))
        //    ; // some mod details
        //else if (!memcmp(data + 9, unkTag0, sizeof unkTag0)
        //    || !memcmp(data + 9, unkTag1, sizeof unkTag1)
        //    || !memcmp(data + 9, unkTag2, sizeof unkTag2)
        //    || !memcmp(data + 9, unkTag3, sizeof unkTag3)
        //    || !memcmp(data + 9, unkTag6, sizeof unkTag6)
        //    || !memcmp(data + 9, unkTag7, sizeof unkTag7)
        //    || !memcmp(data + 9, unkTag8, sizeof unkTag8))
        //    ; // some mod details
        //else if (!memcmp(data + 16, unkTag, sizeof unkTag)
        //    || !memcmp(data + 16, unkTag5, sizeof unkTag5))
        //    ; // some mod details
        //else if (blockLen && prevKey != 2 && prevKey != 3 && prevKey != 5 && prevKey != 6)
        //    bool bh = true;
        else
            bool bh = true;
        break;
    case btTextWide:
        if (blockExcl == '\x21' && blockDataSize == 2)
        {
            //printf("\n   Text Length: %d", blockLen);
            return ParseWideString(text, end);
        }
        //else if (!memcmp(data + 4, unkTag0, sizeof unkTag0))
        //{
        //    // some mod details block
        //}
        //else if (blockLen && prevKey != 2 && prevKey != 3 && prevKey != 5 && prevKey != 6)
        //    bool bh = true;
        else
            bool bh = true;
        break;
    default:
        break;
    }

    return data;
}

static void PrintBuffer(uint8 const* buffer, uint32 len, uint32 blockSize)
{
    //return;
    if (len == 0)
        return;
    for (uint32 i = len; i < blockSize; ++i)
        printf("  ");
    printf("   ");
    for (uint32 i = 0; i < len; ++i)
        putc(buffer[i] >= ' ' && buffer[i] < '\x7F' ? buffer[i] : '.', stdout);
}

uint8 const* ParseBase(uint8 const* data, uint8 const* end)
{
    uint8 const* it = data;
    uint8 dumpBuff[BLOCK_LEN];
    uint32 len = 0;

    for (; it < end; ++it)
    {
        uint32 blockType = *(uint32*)it;
        uint8 const* chng;

        switch (blockType)
        {
        case btText:
        case btTextWide:
            if (*(it + 7) == '\x21')
            {
                PrintBuffer(dumpBuff, len, BLOCK_LEN);
                len = 0;
                chng = ParseText(it, end);
                if (chng != it)
                {
                    it = chng;
                    continue;
                }
            }
        case btUnknown:
            break;

        default:
            break;
        }

        if (!len)
        {
            printf("\n   UNPARSED DATA:   ");
        }
        printf("%02x", *it);
        dumpBuff[len] = *it;
        ++len;
        if (len >= BLOCK_LEN)
        {
            PrintBuffer(dumpBuff, len, BLOCK_LEN);
            len = 0;
        }

        /*switch (*it)
        {
        case '\x21':
            if (!memcmp(it + 2, "\x00\x00\x00", 3))
            {
                uint8 type = *(it + 1);
                printf("\n");
                uint8 const* bck = it - 7;
                for (; bck < it; ++bck)
                    printf("%02x", *bck);

                if (type == 1)
                {
                    PrintBuffer(dumpBuff, len, BLOCK_LEN);
                    it = ParseString(it + 5, end);
                    newBlock = true;
                    break;
                }
                else if (type == 2)
                {
                    PrintBuffer(dumpBuff, len, BLOCK_LEN);
                    it = ParseWideString(it + 5, end);
                    newBlock = true;
                    break;
                }
                else
                    bool bh = true;
            }
        default:
            if (newBlock)
            {
                //printf("\n   UNPARSED DATA:   ");
                newBlock = false;
                len = 0;
            }
            //printf("%02x", *it);
            dumpBuff[len] = *it;
            ++len;
            if (len >= BLOCK_LEN)
            {
                PrintBuffer(dumpBuff, len, BLOCK_LEN);
                newBlock = true;
            }
            break;
        }*/
    }

    return it;
}

static uint8 const* Parse01(uint8 const* data)
{
    uint32 value = *(uint32*)(data + 4);
    uint32 tag;

    uint8 const* tagPos = (data + 4);
    for (; *(uint32*)tagPos < 0xFF; tagPos += 4)
        ; // just run to end
    tag = *(uint32*)tagPos;


#if PRINT_01
    printf("   0x01 - %08x\n", tag);
    for (uint32* it = (uint32*)(data + 4); it < (uint32*)tagPos; ++it)
        printf("      Value: %d\n", *it);
#endif

    return tagPos + 4;
}

static uint8 const* Parse02(uint8 const* data)
{
    uint32 unk0 = *(uint32*)(data + 4);
    uint32 unk1 = *(uint32*)(data + 8);
    uint32 unk2 = *(uint32*)(data + 12);
    uint32 tag = *(uint32*)(data + 16);
    bool bonus = false;

    if (tag == 0x43)
    {
        tag = *(uint32*)(data + 20);
        bonus = true;
    }

#if PRINT_02
    printf("   0x02 - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
    if (bonus)
        printf("      Value: %d\n", *(uint32*)(data + 16));
#endif

    return bonus ? data + 24 : data + 20;
}

static uint8 const* Parse03(uint8 const* data)
{
    uint32 unk0 = *(uint32*)(data + 4);
    uint32 unk1 = *(uint32*)(data + 8);
    uint32 unk2 = *(uint32*)(data + 12);
    uint32 tag = *(uint32*)(data + 16);

#if PRINT_03
    printf("   0x03 - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %08x\n", unk2);
#endif

    return data + 20;
}

static uint8 const* Parse04(uint8 const* data)
{
    uint32 unk0 = *(uint32*)(data + 4);
    uint32 unk1 = *(uint32*)(data + 8);
    uint32 unk2 = *(uint32*)(data + 12);
    uint32 tag = *(uint32*)(data + 16);

#if PRINT_04
    printf("   0x04 - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
#endif

    return data + 20;
}

static uint8 const* Parse05(uint8 const* data)
{
    uint32 len = *(uint32*)(data + 4) & 0xFFFFFF;
    uint8  id = *(data + 7);
    uint32 strCnt = *(uint32*)(data + 8);
    uint8 const* text = data + 12;
    uint8 const* textEnd = text + len;

    uint32 offset = id == '\x21' ? len : id == '\x20' || id == '\x00' ? 4 : 4;
    uint8 const* tagPos = text + offset;
    uint32 tag = *(uint32*)tagPos;

#if PRINT_05
    printf("   0x05 - %08x\n", tag);

    if (id == '\x21')
    {
        printf("      Value: ");
        for (; text < textEnd; ++text)
            putc(*text, stdout);
        //printf("TEXT GOES HERE");
        putc('\n', stdout);
    }
    else if (id == '\x20' || id == '\x00')
         printf("      No text stored.\n");
    else
        bool bh = true;
#endif

    // TODO: fix this wierd edge case, or switch to tags first
    return tag < 0xFF ? tagPos : tagPos + 4;
}

static uint8 const* Parse06(uint8 const* data)
{
    uint32 strLen = *(uint32*)(data + 4) & 0xFFFFFF;
    uint8  id = *(data + 7);
    uint32 strCnt = *(uint32*)(data + 8);
    wchar_t const* text = (wchar_t*)(data + 12);
    wchar_t const* textEnd = text + strLen;
    uint8 const* tagPos = (uint8 const*)(textEnd);
    uint32 tag = *(uint32*)tagPos;

#if PRINT_06
    printf("   0x06 - %08x\n", tag);

    if (id == '\x21')
    {
        printf("      Value: ");
        for (; text < textEnd; ++text)
            putwc(*text, stdout);
        //printf("TEXT GOES HERE");
        putc('\n', stdout);
    }
    else
        bool bh = true;
#endif

    return tagPos + 4;
}

static uint8 const* Parse0a(uint8 const* data)
{
    uint32 unk0 = *(uint32*)(data + 4);
    uint32 unk1 = *(uint32*)(data + 8);
    uint32 unk2 = *(uint32*)(data + 12);
    uint32 tag = *(uint32*)(data + 16);

#if PRINT_0a
    printf("   0x0a - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
#endif

    return data + 20;
}

static uint8 const* Parse0b(uint8 const* data)
{
    uint32 unk0 = *(uint32*)(data + 4);
    uint32 unk1 = *(uint32*)(data + 8);
    uint32 unk2 = *(uint32*)(data + 12);
    uint32 unk3 = *(uint32*)(data + 16);
    uint32 unk4 = *(uint32*)(data + 20);
    uint32 unk5 = *(uint32*)(data + 24);
    uint32 unk6 = *(uint32*)(data + 28);
    uint32 tag = *(uint32*)(data + 32);

#if PRINT_0b
    printf("   0x0b - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
    printf("      Value: %d\n", unk3);
    printf("      Value: %d\n", unk4);
    printf("      Value: %d\n", unk5);
    printf("      Value: %d\n", unk6);
#endif

    return data + 36;
}

static uint8 const* Parse0d(uint8 const* data)
{
    uint16 unk0 = *(uint16*)(data + 4);
    uint16 unk1 = *(uint16*)(data + 6);
    uint32 unk2 = *(uint32*)(data + 8);
    uint32 unk3 = *(uint32*)(data + 12);
    uint32 unk4 = *(uint32*)(data + 16);
    uint32 tag = *(uint32*)(data + 20);

#if PRINT_0d
    printf("   0x0d - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
    printf("      Value: %d\n", unk3);
    printf("      Value: %d\n", unk4);
#endif

    return data + 24;
}

static uint8 const* Parse10(uint8 const* data)
{
    uint32 unk0 = *(uint32*)(data + 4);
    uint32 unk1 = *(uint32*)(data + 8);
    uint32 tag = *(uint32*)(data + 12);

#if PRINT_10
    printf("   0x10 - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
#endif

    return data + 16;
}

static uint8 const* Parse14(uint8 const* data)
{
    uint32 unk0 = *(uint32*)(data + 4);
    uint32 unk1 = *(uint32*)(data + 8);
    uint32 saveTimeSinceEpoch = *(uint32*)(data + 12);
    uint32 unk2 = *(uint32*)(data + 16);
    uint32 tag = *(uint32*)(data + 20);

#if PRINT_14
    printf("   0x14 - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Save Time (seconds since epoch): %d\n", saveTimeSinceEpoch);
    printf("      Value: %d\n", unk2);
#endif

    return data + 24;
}

static uint8 const* Parse15(uint8 const* data)
{
    uint32 unk0 = *(uint32*)(data + 4);
    uint32 unk1 = *(uint32*)(data + 8);
    uint32 unk2 = *(uint32*)(data + 12);
    uint32 unk3 = *(uint32*)(data + 16);
    uint32 tag = *(uint32*)(data + 20);

#if PRINT_15
    printf("   0x15 - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
    printf("      Value: %d\n", unk3);
#endif

    return data + 24;
}

static uint8 const* Parse18(uint8 const* data)
{
    uint8 unk0 = *(data + 4);
    uint8 unk1 = *(data + 5);
    uint8 unk2 = *(data + 6);
    uint8 unk3 = *(data + 7);
    uint32 unk4 = *(uint32*)(data + 8);
    uint32 unk5 = *(uint32*)(data + 12);
    uint32 unk6 = *(uint32*)(data + 16);
    uint32 zlibSize = *(uint32*)(data + 20);
    uint8 const* zlib = data + 24;

    if (unk2)
    {
        // some volume markers don't seem to store the zlib size is greater than a
        //   given amount, this is a quick fix
        uint8 const end[] = "\x00\x00\xff\xff";
        uint8 const* pos = FindFirstOfSubseq(zlib, zlib + 200000, end, end + 4);
        zlibSize = (pos - zlib) + 4;
    }

    uint32 tag = *(uint32*)(zlib + zlibSize);

#if PRINT_18
    printf("   0x18 - %08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
    printf("      Value: %d\n", unk3);
    printf("      Value: %d\n", unk4);
    printf("      Value: %d\n", unk5);
    printf("      Value: %d\n", unk6);
    printf("      zlib Size: %d\n", zlibSize);
    // TODO: unpack zlib
    printf("         TODO: Extract zlib\n");
#endif

    return zlib + zlibSize + 4;
}

static uint8 const* ParseBlock(uint8 const* data)
{
    uint32 blockType = *(uint32*)data;

    switch (blockType)
    {
    case 0x01:
        return Parse01(data);
    case 0x02:
        return Parse02(data);
    case 0x03:
        return Parse03(data);
    case 0x04:
        return Parse04(data);
    case btText:
        return Parse05(data);
    case btTextWide:
        return Parse06(data);
    case 0x0a:
        return Parse0a(data);
    case 0x0b:
        return Parse0b(data);
    case 0x0d:
        return Parse0d(data);
    case 0x10:
        return Parse10(data);
    case 0x14:
        return Parse14(data);
    case 0x15:
        return Parse15(data);
    case 0x18:
        return Parse18(data);
    default:
        blockType = blockType;
        break;
    }
}

// This will be just full of arbitrary numbers as I'm
//   eyeballing an existing file
void ParseHeader(uint8 const* header, uint8 const* headerEnd)
{
    uint8 const* it = header;

    printf("Printing header contents:\n\n");
    printf("   %.4s\n", it);
    it += 4;

    while (it < headerEnd)
        it = ParseBlock(it);

    //it = ParseBase(it, headerEnd);

    // Name, Speed, Map Size
    /*printf("   ");
    // byte 17 might be GameSpeed_Duration
    for (uint32 i = 0; i < 24; ++i, ++it)
        printf("%02x", *it);
    putc('\n', stdout);
    printf("   ");
    for (; *it != '\0'; ++it)
        putc(*it, stdout);
    putc('\n', stdout);
    ++it;
    printf("   ");
    for (uint32 i = 0; i < 16; ++i, ++it)
        printf("%02x", *it);
    putc('\n', stdout);
    printf("   ");
    for (; *it != '\0'; ++it)
        putc(*it, stdout);
    putc('\n', stdout);
    printf("   ");
    for (; *it != '{'; ++it)
        printf("%02x", *it);
    putc('\n', stdout);

    // Handle JSON
    it = ParseJSON(it, headerEnd);
    printf("   ");
    for (; *it != '{'; ++it)
        printf("%02x", *it);
    putc('\n', stdout);
    it = ParseJSON(it, headerEnd);

    // Looks like this may be player data
    for (; (*it != '{' || *(it+1) != '"');)
    {
        printf("   ");
        uint32 i = 0;
        for (; i < 32 && (it[i] != '{' || it[i+1] != '"'); ++i)
            printf("%02x", it[i]);
        for (uint32 j = i; j < 32; ++j)
            printf("  ");
        printf("   ");
        for (uint32 j = 0; j < i; ++j)
            putc(it[j] >= 32 && it[j] < 128 ? it[j] : '.', stdout);
        it += i;
        putc('\n', stdout);
    }
    it = ParseJSON(it, headerEnd);

    // just dump everything
    for (; it < headerEnd;)
    {
        for (; it < headerEnd && (*it != '{' || *(it + 1) != '"');)
        {
            printf("   ");
            uint32 i = 0;
            for (; i < 32 && it + i < headerEnd && (it[i] != '{' || it[i + 1] != '"'); ++i)
                printf("%02x", it[i]);
            for (uint32 j = i; j < 32; ++j)
                printf("  ");
            printf("   ");
            for (uint32 j = 0; j < i; ++j)
                putc(it[j] >= 32 && it[j] < 128 ? it[j] : '.', stdout);
            it += i;
            putc('\n', stdout);
        }
        if (it < headerEnd)
            it = ParseJSON(it, headerEnd);
    }

    putc('\n', stdout);*/
}
