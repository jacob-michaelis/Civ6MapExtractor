
#include "ParseHeader.h"

#include "stdio.h"
#include "string.h"

#define BLOCK_LEN 32

enum BlockType
{
    btText     = 0x05,
    btTextWide = 0x06,
    btUnknown  = 0x18,
};

uint8 const* ParseJSON(uint8 const* data, uint8 const* end)
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

uint8 const* ParseString(uint8 const* data, uint8 const* end)
{
    if (*data == '{')
        return ParseJSON(data, end);

    printf("\n   ");
    uint32 cnt = printf("%s", data);

    return data + cnt;
}

uint8 const* ParseWideString(uint8 const* data, uint8 const* end)
{
    printf("\n   ");
    uint32 cnt = printf("%S", (wchar_t const*)data);

    return data + cnt * 2 + 1;
}

static void DumpBuffer(uint8 const* buffer, uint32 len, uint32 blockSize)
{
    return;
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
    bool newBlock = true;
    uint32 len = 0;
    uint8 dumpBuff[BLOCK_LEN];

    for (; it < end; ++it)
    {
        uint32 blockType = *(uint32*)it;
        uint32 blockLen = *(uint32*)(it + 4);

        switch (*it)
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
                    DumpBuffer(dumpBuff, len, BLOCK_LEN);
                    it = ParseString(it + 5, end);
                    newBlock = true;
                    break;
                }
                else if (type == 2)
                {
                    DumpBuffer(dumpBuff, len, BLOCK_LEN);
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
                DumpBuffer(dumpBuff, len, BLOCK_LEN);
                newBlock = true;
            }
            break;
        }
    }

    return it;
}

// This will be just full of arbitrary numbers as I'm
//   eyeballing an existing file
void ParseHeader(uint8 const* header, uint8 const* headerEnd)
{
    static const char a = '\x4e';

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
