
#include "ParseGameData.h"

#include <stdio.h>
#include <assert.h>

#include "BlockParser.h"
#include "LoadSQLiteConstants.h"

#define DEBUG_BYTE_WIDTH 24

//#define ENABLE_AI_VISION_PRINTING
//#define ENABLE_UNKNOWN_SETTING_PRINTING
#define ENABLE_UNKNOWN1


// --- Globals ----------------------------------------------------------------

static uint32 width;
static uint32 height;
static uint32 length;


// --- Parsers ----------------------------------------------------------------

extern uint8 const* Parse03(uint8 const* data);
extern uint8 const* Parse05(uint8 const* data);

uint8 const* PrintRange(uint8 const* data, uint32 num, char const* label)
{
    uint32 const* it = (uint32 const*)(data);

    for (uint32 i = 0; i < num; ++i, ++it)
        printf("      %s: %d\n", label, *it);

    return (uint8 const*)it;
}

uint8 const* PrintTermCon(uint8 const* data, uint32 termValue, char const* label)
{
    uint32 const* it = (uint32 const*)(data);

    for (; *it != termValue; ++it)
        printf("      %s: %d\n", label, *it);

    return (uint8 const*)it;
}

uint8 const* AssertRange(uint8 const* data, uint32 cnt, uint8 const* pattern, uint32 len)
{
    uint8 const* it = data;
    uint8 const* end = it + (cnt * len);

    for (; it < end; it += len)
        for (uint32 i = 0; i < len; ++i)
            assert(it[i] == pattern[i]);

    return it;
}

uint8 const* PrintArray8(uint8 const* data, uint8 emptyVal)
{
    uint8 const* it = data;

    assert(*(uint32*)it == length);
    it += 4;
    uint8 const* ref = it + ((height - 1) * width);

#if defined(ENABLE_AI_VISION_PRINTING)
    for (int32 y = height - 1; y >= 0; --y)
    {
        printf("         ");
        if (y % 2)
            printf("  ");
        for (uint32 x = 0; x < width; ++x)
            printf("%c   ", ref[x] != emptyVal ? 'O' : '.');
        printf("\n");
        ref -= width;
    }
#endif

    return it + length;
}

uint8 const* PrintArray16(uint8 const* data, uint16 emptyVal)
{
    uint8 const* it = data;

    assert(*(uint32*)it == length);
    it += 4;
    assert(*(uint32*)it == width);
    it += 4;
    assert(*(uint32*)it == length);
    it += 4;
    uint16 const* ref = ((uint16 const*)it) + ((height - 1) * width);

#if defined(ENABLE_AI_VISION_PRINTING)
    for (int32 y = height - 1; y >= 0; --y)
    {
        printf("         ");
        if (y % 2)
            printf("  ");
        for (uint32 x = 0; x < width; ++x)
            printf("%c   ", ref[x] != emptyVal ? '0' + ref[x] : '.');
        printf("\n");
        ref -= width;
    }
#endif

    return it + (length * 2);
}

uint8 const* PrintVision(uint8 const* data)
{
    uint8 const* it = data;

    // In multiplayer games there is a buffer before every player other than 
    //   the first, so we'll just iterate until we see the first array length
    printf("      %2d", *(uint32*)it);
    it += 4;
    for (; *(uint32*)(it + 1) != length; it += 4)
        printf(" - %2d", *(uint32*)it);
    printf(" - %d", *it);
//#if defined(ENABLE_AI_VISION_PRINTING)
    printf("\n");
//#endif
    it += 1;

#if defined(ENABLE_AI_VISION_PRINTING)
    printf("         Explored Area:\n");
#endif
    it = PrintArray8(it, 0);

#if defined(ENABLE_AI_VISION_PRINTING)
    uint32 hash = *(uint32*)(it + 4);
    char const* name = LookupHash(hash, dkAll);
    printf("         Visibility / Fog-of-War:\n");
    if (name)
        printf("         %d - %s - %d\n", *(uint32*)it, name, *(uint32*)(it + 8));
    else
        printf("         %d - 0x%08x - %d\n", *(uint32*)it, hash, *(uint32*)(it + 8));
#endif
    // The array stores the the number of "things" that can see that tile
    it += 12;
    it = PrintArray16(it, 0);

#if defined(ENABLE_AI_VISION_PRINTING)
    hash = *(uint32*)(it);
    name = LookupHash(hash, dkAll);
    printf("         Improvements:\n");
    if (name)
        printf("         %s - %d\n", name, *(uint32*)(it + 4));
    else
        printf("         0x%08x - %d\n", hash, *(uint32*)(it + 4));
#endif
    it += 8;
    it = PrintArray16(it, 0xFFFF);

#if defined(ENABLE_AI_VISION_PRINTING)
    hash = *(uint32*)(it);
    name = LookupHash(hash, dkAll);
    printf("         Resources:\n");
    if (name)
        printf("         %s - %d\n", name, *(uint32*)(it + 4));
    else
        printf("         0x%08x - %d\n", hash, *(uint32*)(it + 4));
#endif
    it += 8;
    it = PrintArray16(it, 0xFFFF);

#if defined(ENABLE_AI_VISION_PRINTING)
    hash = *(uint32*)(it);
    name = LookupHash(hash, dkAll);
    printf("         Roads:\n");
    if (name)
        printf("         %s - %d\n", name, *(uint32*)(it + 4));
    else
        printf("         0x%08x - %d\n", hash, *(uint32*)(it + 4));
#endif
    it += 8;
    it = PrintArray16(it, 0xFFFF);

#if defined(ENABLE_AI_VISION_PRINTING)
    hash = *(uint32*)(it);
    name = LookupHash(hash, dkAll);
    printf("         Unit Adjacency:\n");
    if (name)
        printf("         %s - %d\n", name, *(uint32*)(it + 4));
    else
        printf("         0x%08x - %d\n", hash, *(uint32*)(it + 4));
#endif
    it += 8;
    it = PrintArray16(it, 0);


    //printf("      %d - %2d\n", *(uint32*)it, *(uint32*)(it + 4));
    //it += 8;

    return it;
}

uint8 const* PrintUnknownSettings(uint8 const* data)
{
    uint8 const* it = data;

    uint16 id = *(uint16*)it;
    it += 2;
    uint16 idAlt = *(uint16*)it;
    it += 2;
//#if defined(ENABLE_UNKNOWN_SETTING_PRINTING)
    printf("      %3d - %d - %d - %3d - %3d", id, idAlt,
        *(uint32*)it, *(uint16*)(it + 4), *(uint16*)(it + 6));
//#endif
    it += 8;
    for (; *(uint32*)(it) != 0x00000040; it += 4)
    {
//#if defined(ENABLE_UNKNOWN_SETTING_PRINTING)
        printf(" - %4d", *(uint32*)it);
//#endif
    }
#if defined(ENABLE_UNKNOWN_SETTING_PRINTING)
    printf("\n");
#endif

    uint32 jumpDist = *(uint32*)it;
    for (; jumpDist == 0x00000040;)
    {
        it += 4;

        AssertRange(it, jumpDist * 4, (uint8 const*)"\x00", 1);
        it += (jumpDist * 4);

        jumpDist = *(uint32*)it;
    }

    uint32 numEntries = *(uint32*)it;
    for (; numEntries == 6;)
    {
        it += 4;

#if defined(ENABLE_UNKNOWN_SETTING_PRINTING)
        printf("      ");
#endif
        for (uint32 i = 0; i < numEntries; ++i, it += 8)
        {
#if defined(ENABLE_UNKNOWN_SETTING_PRINTING)
            uint32 hash = *(uint32*)(it);
            char const* name = LookupHash(hash, dkAll);
            if (name)
                printf("   %s: %d", name, *(uint32*)(it + 4));
            else
                printf("   0x%08x: %d", hash, *(uint32*)(it + 4));
#endif
        }
#if defined(ENABLE_UNKNOWN_SETTING_PRINTING)
        printf("\n");
#endif

        numEntries = *(uint32*)it;
    }

    numEntries = *(uint32*)it;
    it += 4;
#if defined(ENABLE_UNKNOWN_SETTING_PRINTING)
    printf("         Settings 0:\n");
#endif
    for (uint32 i = 0; i < numEntries; ++i, it += 8)
    {
#if defined(ENABLE_UNKNOWN_SETTING_PRINTING)
        uint32 hash = *(uint32*)(it);
        char const* name = LookupHash(hash, dkAll);
        if (name)
            printf("            %s: %d\n", name, *(uint32*)(it + 4));
        else
            printf("            0x%08x: %d\n", hash, *(uint32*)(it + 4));
#endif
    }
    numEntries = *(uint32*)it;
    it += 4;
#if defined(ENABLE_UNKNOWN_SETTING_PRINTING)
    printf("         Settings 1:\n");
#endif
    for (uint32 i = 0; i < numEntries; ++i, it += 8)
    {
#if defined(ENABLE_UNKNOWN_SETTING_PRINTING)
        uint32 hash = *(uint32*)(it);
        char const* name = LookupHash(hash, dkAll);
        if (name)
            printf("            %s: %d\n", name, *(uint32*)(it + 4));
        else
            printf("            0x%08x: %d\n", hash, *(uint32*)(it + 4));
#endif
    }

//#if defined(ENABLE_UNKNOWN_SETTING_PRINTING)
    printf("         %2d - %2d - %2d - %2d - %d - %d - %d\n", *(uint32*)it, *(uint32*)(it + 4),
        *(uint32*)(it + 8), *(uint32*)(it + 12), *(it + 16), *(it + 17), *(it + 18));
//#endif
    it += 19;

    return it;
}

uint8 const* PrintUnknown1(uint8 const* data)
{
    uint8 const* it = data;

    uint32 id = *(uint32*)it;
    it += 4;
    uint32 delim = *(uint32*)it;
    it += 4;
    uint16 from = *(uint16*)it;
    it += 2;
    uint16 to = *(uint16*)it;
    it += 2;
    uint32 val0 = *(uint32*)it;
    it += 4;
    uint8 val1 = *it;
    it += 1;
    uint32 val2 = *(uint32*)it;
    it += 4;
    uint32 val3 = *(uint32*)it;
    it += 4;

    printf("         %2d - %2d - %2d - %2d - %5d - %d - %5d - %5d\n",
        id, delim, from, to, val0, val1, val2, val3);

    return it;
}

uint8 const* PrintUnknown2(uint8 const* data)
{
    uint8 const* it = data;

    uint32 id = *(uint32*)it;
    it += 4;
    uint32 delim = *(uint32*)it;
    it += 4;
    uint16 from = *(uint16*)it;
    it += 2;
    uint16 to = *(uint16*)it;
    it += 2;
    uint32 val0 = *(uint32*)it;
    it += 4;
    uint8 val1 = *it;
    it += 1;
    uint16 val2 = *(uint16*)it;
    it += 2;
    uint16 val3 = *(uint16*)it;
    it += 2;
    uint32 numPairs = *(uint32*)it;
    it += 4;

    printf("         %2d - %2d - %2d - %2d - %3d - %d - %2d - %2d   %4d: {",
        id, delim, from, to, val0, val1, val2, val3, numPairs);

    for (uint32 i = 0; i < numPairs; ++i, it += 4)
    {
        printf(" %2d, %2d,", *(uint16*)it, *(uint16*)(it + 2));
    }
    printf(" }\n");

    return it;
}

uint8 const* PrintUnknown3(uint8 const* data)
{
    uint8 const* it = data;

    uint32 id = *(uint32*)it;
    it += 4;
    uint32 delim = *(uint32*)it;
    it += 4;
    uint16 from = *(uint16*)it;
    it += 2;
    uint16 to = *(uint16*)it;
    it += 2;
    uint8 val0 = *it;
    it += 1;
    uint32 val1 = *(uint32*)it;
    it += 4;

    printf("         %2d - %d - %2d - %2d - %d - %d",
        id, delim, from, to, val0, val1);

    for (;;)
    {
        uint32 val = *(uint32*)it;
        printf("   %3d", val);
        it += 4;

        if (val <= 2)
        {
            uint16 n0 = *(uint16*)(it);
            uint16 n1 = *(uint16*)(it + 2);

            if (n0 == n1 - 1 ||
                (val == 0 && n0 == id + 1))
                break;
        }
    }

    printf("   {");
    uint32 endCnt = *(uint32*)(it - 4);

    for (uint32 i = 0; i < endCnt; ++i, it += 4)
        printf(" %2d, %2d,", *(uint16*)it, *(uint16*)(it + 2));

    printf(" }\n");

    return it;
}

uint8 const* Print8On8OffBlock(uint8 const* data)
{
    uint8 const* it = data;

    uint32 cnt = *(uint32*)it;
    it += 4;

    printf("      {");
    for (uint32 i = 0; i < cnt; ++i, it += 20)
        printf(" %d: [ 0x%016llx, %lld ]", *it, *(uint64*)(it + 4), *(uint64*)(it + 12));
    printf(" }\n");

    return it;
}

uint8 const* PrintUnknown4(uint8 const* data)
{
    uint8 const* it = data;

    uint32 id = *(uint32*)it;
    it += 4;
    uint16 val0 = *(uint16*)it;
    it += 2;
    uint32 cnt = *(uint32*)it;
    it += 4;

    printf("      %2d - %5d - %2d: {", id, val0, cnt);
    for (uint32 i = 0; i < cnt; ++i, it += 2)
        printf(" [ %3d, %3d ]", *it, *(it + 1));
    printf(" }\n");

    return it;
}

uint8 const* VerifyHeader(uint8 const* data)
{
    uint32 header[] =
    {
        5,
        3,
        0x4e33fe49,
        3,
        0,
        0,
        0,
        0xf4e540d8,
        5,
        0x21000025,
        1
    };
    uint32 len = sizeof header / sizeof * header;
    uint32* dIt = (uint32*)data;

    for (uint32 i = 0; i < len; ++i, ++dIt)
        if (*dIt != header[i])
            printf("WARNING: Header mismatch at %d.\n", i);

    uint8 const* it = data;

    it = Parse03(it + 8);
    it = Parse05(it);

    printf("   0x%02x - 0x%08x\n", *(uint32*)(it + 4), *(uint32*)it);
    it = PrintRange(it + 8, 7, "Label");

    uint8 const* civTurnCounters = it;
    it += (65 * 4);
    uint8 const* barbFreeTurnCounters = it;
    it += (2 * 4);
    uint8 const* civIndexNumbers = it; // Educated guess
    it += (64 * 4);
    uint8 const* turnCounter = it;
    it += (1 * 4) + 3;
    uint8 const* logicByteField = it; // Blind guess
    it += (288 * 4);
    it += 4;
    // seems to be a set of properties, related to mods?
    uint8 const* modNotModFlags = it;
    it += 4 + 1 + 8 + 4;
    uint32 numEntries = *(uint32*)it;
    it += 4 + (numEntries * 5);

    // seems to be set to 0x4c376b13 when in a multiplayer game, otherwise 0xFFFFFFFF
    uint32 isMultiplayerTag = *(uint32*)it; // Educated guess
    it += 4;
    uint32 currentTurn = *(uint32*)it;
    it += 4;
    uint32 gameTurnLength = *(uint32*)it;
    it += 4;
    // no clue what these are
    it = AssertRange(it, 12, (uint8 const*)"\x00", 1);
    assert(*(uint32*)it == 0x04);
    it += 4;
    width = *(uint32*)it;
    it += 4;
    height = *(uint32*)it;
    length = width * height;
    it += 4;
    assert(*(uint32*)it == 0x5a);
    it += 4;
    assert(*(uint32*)it == 0xffffffa6);
    it += 4;
    // Unknown section
    it += 2 + 6 + 6 + 4;
    uint32 numEntries1 = *(uint32*)it;
    it += 4;
    printf("   Settings/Game Records? set 0:\n");
    for (uint32 i = 0; i < numEntries1; ++i)
    {
        uint32 hash = *(uint32*)it;
        it += 4;
        uint32 value = *(uint32*)it;
        it += 4;
        char const* name = LookupHash(hash, dkAll);
        if (name)
            printf("      %s: %d\n", name, value);
        else
            printf("      0x%08x: %d\n", hash, value);
    }
    uint32 numEntries2 = *(uint32*)it;
    it += 4;
    printf("   Settings/Game Records? set 1:\n");
    for (uint32 i = 0; i < numEntries2; ++i)
    {
        uint32 hash = *(uint32*)it;
        it += 4;
        uint32 value = *(uint32*)it;
        it += 4;
        char const* name = LookupHash(hash, dkAll);
        if (name)
            printf("      %s: %d\n", name, value);
        else
            printf("      0x%08x: %d\n", hash, value);
    }
    assert(*(uint32*)it == 1);


    // Major civs + city states + barbarians + free cities
    uint32 numPlayers = *(uint32*)(it + 4);
    printf("   Player Vision:   %d - %d\n", *(uint32*)it, numPlayers);
    it += 8;
    // Order is:
    // Player(s)
    // Civs in the order listed when clicking the player portrait
    // City States listed in the order on the city states tab
    for (uint32 i = 0; i < numPlayers; ++i)
    {
#if defined(ENABLE_AI_VISION_PRINTING)
        printf("   Player %d Maps:\n", i);
#endif
        it = PrintVision(it);
    }

    printf("      %2d", *(uint32*)it);
    it += 4;
    uint32 const* tail = (uint32 const*)it;
    for (; !(*tail == 1 && *(tail + 1) == 0x10001 && *(tail + 2) == 0x10); ++tail)
        printf(" - %d", *tail);
    printf("\n");
    it = (uint8 const*)tail;
    it += 12;

    uint32 dist = it - data;
    printf("Offset: %d - 0x%08x - 0x%08x\n", dist, dist, dist - (dist % DEBUG_BYTE_WIDTH));


    // Game Stats/Turn Record?
    uint32 rundownId = *(uint32*)it;
    it += 4;
    uint32 lastId = *(uint32*)it;
    uint32 endId = lastId << 16;
    it += 4;

    printf("   Game Stats/Turn Record?:   %d - %d\n", rundownId, lastId);
    for (uint32 i = 0; *(uint32*)(it) != endId; ++i)
    {
#if defined(ENABLE_UNKNOWN_SETTING_PRINTING)
        printf("      Set %d:\n", i);
#endif
        it = PrintUnknownSettings(it);
    }

    uint32 tailLen = *(uint32*)(it + 4);
    it += 16 + (tailLen * 4);
    assert(*(uint32*)it == 1 && *(uint32*)(it + 4) == 0x10001 && *(uint32*)(it + 8) == 0x10);
    it += 12;

    dist = it - data;
    printf("Offset: %d - 0x%08x - 0x%08x\n", dist, dist, dist - (dist % DEBUG_BYTE_WIDTH));


    // Unknown 1
    rundownId = *(uint32*)it;
    it += 4;
    lastId = *(uint32*)it;
    endId = lastId << 16;
    it += 4;

    printf("   Unknown 1:   %d - %d\n", rundownId, lastId);
    for (; *(uint32*)(it) != endId;)
    {
        it = PrintUnknown1(it);
    }

    tailLen = *(uint32*)(it + 4);
    it += 16 + (tailLen * 4);
    assert(*(uint32*)it == 1 && *(uint32*)(it + 4) == 0x10001 && *(uint32*)(it + 8) == 0x10);
    it += 12;

    dist = it - data;
    printf("Offset: %d - 0x%08x - 0x%08x\n", dist, dist, dist - (dist % DEBUG_BYTE_WIDTH));


    // Unknown 2
    rundownId = *(uint32*)it;
    it += 4;
    lastId = *(uint32*)it;
    endId = lastId << 16;
    it += 4;

    printf("   Unknown 2:   %d - %d\n", rundownId, lastId);
    for (; *(uint32*)(it) != endId;)
    {
        it = PrintUnknown2(it);
    }

    tailLen = *(uint32*)(it + 4);
    it += 16 + (tailLen * 4);
    assert(*(uint32*)it == 0x10001 && *(uint32*)(it + 4) == 0x10);
    it += 8;

    dist = it - data;
    printf("Offset: %d - 0x%08x - 0x%08x\n", dist, dist, dist - (dist % DEBUG_BYTE_WIDTH));


    // Unknown 3
    rundownId = *(uint32*)it;
    it += 4;
    lastId = *(uint32*)it;
    endId = lastId << 16;
    it += 4;

    printf("   Unknown 3:   %d - %d\n", rundownId, lastId);
    for (; *(uint32*)(it) != endId;)
    {
        it = PrintUnknown3(it);
    }

    tailLen = *(uint32*)(it + 4);
    it += 16 + (tailLen * 4);

    it = Print8On8OffBlock(it);

    assert(*(uint32*)it == 1 && *(uint32*)(it + 4) == 0x10001 && *(uint32*)(it + 8) == 0x10);
    it += 12;

    dist = it - data;
    printf("Offset: %d - 0x%08x - 0x%08x\n", dist, dist, dist - (dist % DEBUG_BYTE_WIDTH));


    // Unknown 4
    rundownId = *(uint32*)it;
    it += 4;
    lastId = *(uint32*)it;
    endId = (lastId - 1) << 16;
    it += 4;

    printf("   Unknown 4:   %d - %d\n", rundownId, lastId);
    for (; *(uint32*)(it) != endId;)
    {
        it = PrintUnknown4(it);
    }

    tailLen = *(uint32*)(it + 4);
    it += 16 + (tailLen * 4);

    dist = it - data;
    printf("Offset: %d - 0x%08x - 0x%08x\n", dist, dist, dist - (dist % DEBUG_BYTE_WIDTH));

    return it;
}

#define MINIMUM_TILE_DATA_BREADTH 55

uint8 const* ExtractMap(uint8 const* data)
{
    uint8 const* it = data;

    uint32 arrayTag = *(uint32*)it;
    it += 4;
    uint32 arrayLen = *(uint32*)it;
    it += 4;

    for (uint32 i = 0; i < arrayLen; ++i)
    {

    }

    return it;
}


// --- Interface --------------------------------------------------------------

#include <vector>

void ParseGameData(uint8 const* body, uint8 const* bodyEnd)
{
    uint8 const* it = body;

    it = VerifyHeader(it);
    it = ExtractMap(it);
}
