
#include "ParseHeader.h"

#include "stdio.h"
#include "string.h"

#define BLOCK_LEN 32
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

// This will be just full of arbitrary numbers as I'm
//   eyeballing an existing file
void ParseHeader(uint8 const* header, uint8 const* headerEnd)
{
    uint8 const* it = header;

    printf("Printing header contents:\n\n");
    printf("   %.4s", it);
    it += 4;

    it = ParseBase(it, headerEnd);

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