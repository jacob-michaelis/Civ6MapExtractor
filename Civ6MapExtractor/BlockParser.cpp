
#include "BlockParser.h"

#include <stdio.h>
#include <string.h>

#include "BinaryDataTools.h"
#include "SaveConstants.h"
#include "Civ6MapWriter.h"

//#define PRINT_LETags

#define PRINT_UNTAGGED

#define PRINT_01
#define PRINT_02
#define PRINT_03
#define PRINT_04
#define PRINT_05
#define PRINT_06
#define PRINT_0a
#define PRINT_0b
#define PRINT_0d
#define PRINT_10
#define PRINT_14
#define PRINT_15
#define PRINT_18

#define PRINT_07
#define PRINT_08
#define PRINT_09
#define PRINT_0c
#define PRINT_0e
#define PRINT_0f
#define PRINT_11
#define PRINT_12
#define PRINT_13
#define PRINT_16
#define PRINT_17


// --- Globals ----------------------------------------------------------------

MapDetails details;


// --- Block Parsers ----------------------------------------------------------

uint8 const* ParseJSON(uint8 const* data)
{
    if (*data != '{')
    {
        printf("WARNING: First json character must be an opening bracket.");
        return data;
    }

    uint8 const* it = data;
    uint32 depth = 0;
    printf("      ");

    for (;; ++it)
    {
        switch (*it)
        {
            // start section
        case '{':
            printf("{\n      ");
            ++depth;
            for (uint32 i = 0; i < depth; ++i)
                printf("   ");
            break;
            // end section
        case '}':
            printf("\n      ");
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
            printf("[\n      ");
            ++depth;
            for (uint32 i = 0; i < depth; ++i)
                printf("   ");
            break;
        case ']':
            printf("\n      ");
            --depth;
            for (uint32 i = 0; i < depth; ++i)
                printf("   ");
            putc(']', stdout);
            break;
        case ',':
            printf(",\n      ");
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

    putc('\n', stdout);
    return it;
}

uint8 const* Parse01(uint8 const* data)
{
    uint32 tag = *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);
    uint32 boolData = *(uint32*)(data + 16);


#ifdef PRINT_01
    printf("   0x01 - 0x%08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", boolData);
#endif

    return data + 20;
}

uint8 const* Parse02(uint8 const* data)
{
    uint32 tag = *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);
    uint32 unk2 = *(uint32*)(data + 16);

#ifdef PRINT_02
    printf("   0x02 - 0x%08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
#endif

    return data + 20;
}

uint8 const* Parse03(uint8 const* data)
{
    uint32 tag = *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);
    uint32 unk2 = *(uint32*)(data + 16);

#ifdef PRINT_03
    printf("   0x03 - 0x%08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
#endif

    return data + 20;
}

uint8 const* Parse04(uint8 const* data)
{
    uint32 tag = *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);
    uint32 unk2 = *(uint32*)(data + 16);

#ifdef PRINT_04
    printf("   0x04 - 0x%08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
#endif

    return data + 20;
}

uint8 const* Parse05(uint8 const* data)
{
    uint32 tag = *(uint32*)(data);
    uint32 len = *(uint32*)(data + 8) & 0xFFFFFF;
    uint8  flags = *(data + 11);
    uint32 unk0 = *(uint32*)(data + 12);
    uint8 const* text = data + 16;
    uint8 const* textEnd = text + len;

    if (flags == '\x20' || flags == '\x00')
        textEnd += 4;

    // store specific data
    // as the text is stored nul terminated and isn't removed until the
    //   program exits, this should be fine
    if (tag == 0x0b835c40)
        details.size = (char const*)text;
    else if (tag == 0xc45925de)
        details.ruleSet = (char const*)text;

#ifdef PRINT_05
    printf("   0x05 - 0x%08x\n", tag);
    printf("      Length:  %d\n", len);
    printf("      Flags:   0x%02x\n", flags);
    printf("      Unknown: %d\n", unk0);

    if (flags == '\x21')
    {
        if (*text == '{')
        {
            ParseJSON(text);
        }
        else
        {
            printf("      Text: ");
            for (; text < textEnd - 1; ++text)
                putc(*text, stdout);
            //printf("TEXT GOES HERE");
            putc('\n', stdout);
        }
    }
    else if (flags == '\x20' || flags == '\x00')
        printf("      No text stored.\n");
    else
        bool bh = true;
#endif

    return textEnd;
}

uint8 const* Parse06(uint8 const* data)
{
    uint32 tag = *(uint32*)(data);
    uint32 len = *(uint32*)(data + 8) & 0xFFFFFF;
    uint8  flags = *(data + 11);
    uint32 unk0 = *(uint32*)(data + 12);
    wchar_t const* text = (wchar_t*)(data + 16);
    wchar_t const* textEnd = text + len;

#ifdef PRINT_06
    printf("   0x06 - 0x%08x\n", tag);
    printf("      Length:  %d\n", len);
    printf("      Flags:   0x%02x\n", flags);
    printf("      Unknown: %d\n", unk0);

    if (flags == '\x21')
    {
        printf("      Text: ");
        for (; text < textEnd - 1; ++text)
            putwc(*text, stdout);
        //printf("TEXT GOES HERE");
        putc('\n', stdout);
    }
    else
        bool bh = true;
#endif

    return (uint8 const*)textEnd;
}

uint8 const* Parse0a(uint8 const* data)
{
    uint32 tag = *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);
    uint32 unk2 = *(uint32*)(data + 16);

#ifdef PRINT_0a
    printf("   0x0a - 0x%08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
#endif

    return data + 20;
}

uint8 const* Parse0b(uint8 const* data)
{
    uint32 tag = *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);
    uint32 unk2 = *(uint32*)(data + 16);
    uint32 unk3 = *(uint32*)(data + 20);
    uint32 unk4 = *(uint32*)(data + 24);
    uint32 unk5 = *(uint32*)(data + 28);
    uint32 unk6 = *(uint32*)(data + 32);

#ifdef PRINT_0b
    printf("   0x0b - 0x%08x\n", tag);
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

// Scenario data?
uint8 const* Parse0d(uint8 const* data)
{
    uint16 unk0 = *(uint16*)(data + 4);
    uint16 unk1 = *(uint16*)(data + 6);
    uint32 unk2 = *(uint32*)(data + 8);
    uint32 unk3 = *(uint32*)(data + 12);
    uint32 unk4 = *(uint32*)(data + 16);
    uint32 tag = *(uint32*)(data + 20);

#ifdef PRINT_0d
    printf("   0x0d - 0x%08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
    printf("      Value: %d\n", unk3);
    printf("      Value: %d\n", unk4);
#endif

    return data + 24;
}

// Gamespeed settings?
uint8 const* Parse10(uint8 const* data)
{
    uint32 tag = *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);

#ifdef PRINT_10
    printf("   0x10 - 0x%08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
#endif

    return data + 16;
}

// Save time stamp
uint8 const* Parse14(uint8 const* data)
{
    uint32 tag = *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);
    uint32 saveTimeSinceEpoch = *(uint32*)(data + 16);
    uint32 unk2 = *(uint32*)(data + 20);

#ifdef PRINT_14
    printf("   0x14 - 0x%08x\n", tag);
    printf("      Value: %08x\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Save Time (seconds since epoch): %d\n", saveTimeSinceEpoch);
    printf("      Value: %d\n", unk2);
#endif

    return data + 24;
}

uint8 const* Parse15(uint8 const* data)
{
    uint32 tag = *(uint32*)(data);
    uint32 unk0 = *(uint32*)(data + 8);
    uint32 unk1 = *(uint32*)(data + 12);
    uint32 unk2 = *(uint32*)(data + 16);
    uint32 unk3 = *(uint32*)(data + 20);

#ifdef PRINT_15
    printf("   0x15 - 0x%08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
    printf("      Value: %d\n", unk3);
#endif

    return data + 24;
}

// Zlib buffers
uint8 const* Parse18(uint8 const* data)
{
    uint32 tag = *(uint32*)(data);
    uint8 unk0 = *(data + 8);
    uint8 unk1 = *(data + 9);
    uint8 unk2 = *(data + 10);
    uint8 unk3 = *(data + 11);
    uint32 unk4 = *(uint32*)(data + 12);
    uint32 unk5 = *(uint32*)(data + 16);
    uint32 unk6 = *(uint32*)(data + 20);
    uint32 unk7 = *(uint32*)(data + 24);
    uint8 const* zlib = data + 28;

    // typically volume size seems to be stored in unk7, but not always so this was added
    uint8 const endPattern[] = "\x00\x00\xff\xff";
    uint8 const* pos = FindFirstOfSubseq(zlib, zlib + 256 * 1024 * 1024, endPattern, endPattern + 4);
    uint32 zlibSize = (pos - zlib) + 4;

#ifdef PRINT_18
    printf("   0x18 - 0x%08x\n", tag);
    printf("      Value: %d\n", unk0);
    printf("      Value: %d\n", unk1);
    printf("      Value: %d\n", unk2);
    printf("      Value: %d\n", unk3);
    printf("      Value: %d\n", unk4);
    printf("      Value: %d\n", unk5);
    printf("      Value: %d\n", unk6);
    printf("      Value: %d\n", unk7);
    // TODO: unpack zlib
    printf("         TODO: Extract zlib\n");
    printf("      zlib Size: %d\n", zlibSize);
#endif

    return zlib + zlibSize;
}

uint8 const* ParseUntaggedData(uint32 lastTag, uint32 lastType, uint8 const* data)
{
    // seems like a normal value just w/o tags
    if (*(uint32*)data == 0x0a)
        return Parse0a(data - 4);

#ifdef PRINT_UNTAGGED
    printf("   Untagged data found after tag 0x%08x (data type 0x%02x):\n", lastTag, lastType);
#endif

    while (*(uint32*)data < 0x00FFFFFF)
    {
#ifdef PRINT_UNTAGGED
        printf("      Value: %d\n", *(uint32*)data);
#endif
        data += 4;
    }

    return data;
}


// --- Interface --------------------------------------------------------------

uint8 const* ParseBlock(uint8 const* data)
{
    static uint32 lastTag = 0;
    static uint32 lastType = 0;
    if (*(uint32*)(data) < 0x00FFFFFF)
        data = ParseUntaggedData(lastTag, lastType, data);
    uint32 tag = *(uint32*)(data);
    uint32 blockType = *(uint32*)(data + 4);

#ifdef PRINT_LETags
    printf("   LE Tag: %02x%02x%02x%02x\n", data[0], data[1], data[2], data[3]);
#endif

#ifdef TRACK_TAGS
    TrackTag(tag);
#endif

    lastTag = tag;
    lastType = blockType;


    switch (blockType)
    {
    case bt01_Bool:
        return Parse01(data);
    case bt02_t:
        return Parse02(data);
    case bt03_t:
        return Parse03(data);
    case bt04_t:
        return Parse04(data);
    case bt05_Text:
        return Parse05(data);
    case bt06_TextWide:
        return Parse06(data);
    case bt0a_t:
        return Parse0a(data);
    case bt0b_t:
        return Parse0b(data);
    case bt0d_t:
        return Parse0d(data);
    case bt10_t:
        return Parse10(data);
    case bt14_TimeStamp:
        return Parse14(data);
    case bt15_t:
        return Parse15(data);
    case bt18_Zlib:
        return Parse18(data);
    default:
        printf("Unknown block type! Please contact me with details.");
        break;
    }

    return NULL;
}

MapDetails* GetFoundMapDetails()
{
    return &details;
}
