
#include "ParseGameData.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

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

static uint8 const* p0Vision;
static uint16 const* p0Visible;


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
    if (!p0Vision)
        p0Vision = it + 4;
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
    if (!p0Visible)
        p0Visible = (uint16 const*)(it + 12);
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

    uint32 id = *(uint32*)it;
    it += 4;
//#if defined(ENABLE_UNKNOWN_SETTING_PRINTING)
    printf("      %3d - %d - %3d - %3d", id,
        *(uint32*)it, *(uint16*)(it + 4), *(uint16*)(it + 6));
//#endif
    it += 8;
    for (uint32 i = 0; i < 10; ++i, it += 4)
    {
//#if defined(ENABLE_UNKNOWN_SETTING_PRINTING)
        uint32 val = *(uint32*)it;
        if (val)
            printf(" - %4d", val);
        else
            printf(" -     ");
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
    do
    {
        it = PrintUnknown4(it);
    } while (*(uint32*)(it) != endId);

    tailLen = *(uint32*)(it + 4);
    it += 16 + (tailLen * 4);

    dist = it - data;
    printf("Offset: %d - 0x%08x - 0x%08x\n", dist, dist, dist - (dist % DEBUG_BYTE_WIDTH));

    return it;
}

#define MINIMUM_TILE_DATA_BREADTH 55

struct BaseTile
{
    uint16 s0;
    uint16 s1;
    uint16 s2;
    uint16 s3;
    uint16 s4;
    uint16 s5;
    uint32 terrainHash;
    uint32 featureHash;
    uint16 s6;
    uint32 unkHash0;
    uint8 b7;
    uint32 resourceHash;
    uint16 s8;
    uint32 unkHash1;
    uint8 b9;
    uint16 s10;
    uint16 s11;
    uint8 b12;
    uint16 s13;
    uint8 b15;
    uint8 b16;
    uint8 b17;
    uint8 b18;
    uint8 b19;
    uint8 b20;
    uint32 i21;
};

uint8 const* ExtractMap(uint8 const* data)
{
    uint8 const* it = data;

    uint32 arrayTag = *(uint32*)it;
    it += 4;
    uint32 arrayLen = *(uint32*)it;
    it += 4;

    for (uint32 i = 0; i < arrayLen; ++i)
    {
        uint32 x = i % width;
        uint32 y = i / width;
        printf("   Tile %5d: (%3d, %3d)", i, x, y);


        uint16 areaID = *(uint16*)it;
        uint16 areaIDPlus1 = *(uint16*)(it + 2);
        uint16 landVsWaterID = *(uint16*)(it + 4);
        uint16 landVsWaterIDPlus1 = *(uint16*)(it + 6);
        uint16 navMeshClusterID = *(uint16*)(it + 8);
        uint16 navMeshClusterIDPlus1 = *(uint16*)(it + 10);
        it += 12;

        printf("   %3d-%3d  %3d-%3d", areaID, areaIDPlus1, landVsWaterID, landVsWaterIDPlus1);
        if (navMeshClusterID != 0xFFFF)
            printf("  %3d-%3d", navMeshClusterID, navMeshClusterIDPlus1);
        else
            printf("         ");


        uint32 terrainHash = *(uint32*)it;
        uint32 featureHash = *(uint32*)(it + 4);
        uint16   multiTileFeatureID = *(uint16*)(it + 8);
        uint32 continentHash = *(uint32*)(it + 10);
        uint8    hasUnit = *(it + 14);
        uint32 resourceHash = *(uint32*)(it + 15);
        uint16   hasResource = *(uint16*)(it + 19);
        uint32 improvementHash = *(uint32*)(it + 21);
        it += 25;

        char const* name = LookupHash(terrainHash, dkTERRAIN);
        if (name)
            printf("   %-23s", name);
        else if (terrainHash != 0xFFFFFFFF)
            printf("                0x%08x", terrainHash);

        name = LookupHash(featureHash, dkFEATURE);
        if (name)
            printf("   %-29s", name);
        else if (featureHash != 0xFFFFFFFF)
            printf("                      0x%08x", featureHash);
        else
            printf("                                ");

        if (multiTileFeatureID)
            printf("   %2d", multiTileFeatureID);
        else
            printf("     ");

        name = LookupHash(continentHash, dkCONTINENT);
        if (name)
            printf("   %-25s", name);
        else if (continentHash != 0xFFFFFFFF)
            printf("                  0x%08x", continentHash);
        else
            printf("                            ");

        // does not track religious units
        if (hasUnit)
            printf("   %d", hasUnit);
        else
            printf("    ");

        name = LookupHash(resourceHash, dkRESOURCE);
        if (name)
            printf("   %-25s", name);
        else if (resourceHash != 0xFFFFFFFF)
            printf("                  0x%08x", resourceHash);
        else
            printf("                            ");

        if (hasResource)
            printf("   %d", hasResource);
        else
            printf("    ");

        name = LookupHash(improvementHash, dkIMPROVEMENT);
        if (name)
            printf("   %-30s", name);
        else if (improvementHash != 0xFFFFFFFF)
            printf("                       0x%08x", improvementHash);
        else
            printf("                                 ");


        // { Improvement Owner, Road Age, Road Type }
        int8 improvementOwner = *it;
        int8 roadAge = *(it + 1);
        int8 roadType = *(it + 2);
        int16 appeal = *(int16*)(it + 3);
        int8 riverFlowE = *(it + 5);
        int8 riverFlowSE = *(it + 6);
        int8 riverFlowSW = *(it + 7);
        it += 8;

        printf("   { %2d, %2d, %2d }", improvementOwner, roadAge, roadType);
        printf("   %3d", appeal);
        printf("   { %2d, %2d, %2d }", riverFlowE, riverFlowSE, riverFlowSW);


        uint8 numberOfRiverEdges = *(uint8*)(it);
        // 0 : SW of X
        // 1 : W of X
        // 2 : NW of X
        // 3 : NE of X
        // 4 : E of X
        // 5 : SE of X
        uint8 rivers = *(uint8*)(it + 1);
        uint8 cliffs = *(uint8*)(it + 2);
        // 0 : pillaged improvement
        // 1 : pillaged road
        // 2 : ? favored tile when forming trade route?
        // 3 : initial settler spawn location
        //
        // 5 : NE of river
        // 6 : W of river
        // 7 : NW of river
        uint8 tileProperties = *(uint8*)(it + 3);
        // 0 : NE of cliff
        // 1 : W of cliff
        // 2 : NW of cliff
        // 
        // 
        // 5 : Impassable
        // 6 : Controlled Territory
        // 
        // 8 : cracked ice
        uint16 flags = *(uint16*)(it + 4);
        it += 6;

        if (numberOfRiverEdges)
            printf("   %d", numberOfRiverEdges);
        else
            printf("    ");
        if (rivers)
            printf(" - %2x", rivers);
        else
            printf(" -   ");
        if (cliffs)
            printf("   %2x", cliffs);
        else
            printf("     ");
        if (tileProperties)
            printf("   %2x", tileProperties);
        else
            printf("     ");
        if (flags)
            printf(" - %4x", flags);
        else
            printf(" -     ");


        uint32 cnt = *(uint32*)it;
        it += 4;
        if (cnt)
            printf("   %2d:", cnt);


        if (cnt)
        {
            assert(cnt == *(uint32*)it);
            it += 4;

            for (uint32 j = 0; j < cnt; ++j)
            {
                uint32 unkHash = *(uint32*)it;
                assert(*(uint32*)(it + 4) == 0x0a);
                assert(*(uint32*)(it + 8) == 0x05000000);
                assert(*(uint32*)(it + 12) == 0);
                uint32 cont = *(uint32*)(it + 16);
                it += 20;

                name = LookupHash(unkHash, dkAll);
                if (name)
                    printf("   %s", name);
                else if (unkHash == 0x2f95b305)
                    printf("   has had feature");
                else if (unkHash == 0xd9a34c75)
                    printf("   has had improvement");
                else
                    printf("   unknown");


                // unknown
                if (cont)
                {
                    printf("  - %2d:", cont);

                    for (uint32 k = 0; k < cont; ++k)
                    {
                        uint32 unkHashCont = *(uint32*)it;
                        assert(*(uint32*)(it + 4) == 0x02);
                        assert(*(uint32*)(it + 8) == 0);
                        assert(*(uint32*)(it + 12) == 0);
                        uint32 val = *(uint32*)(it + 16);
                        it += 20;

                        name = LookupHash(unkHashCont, dkAll);
                        if (name)
                            printf("   %s", name);
                        else if (unkHashCont != 0xFFFFFFFF)
                            printf("   0x%08x", unkHashCont);
                        printf("  - %2d:", val);
                    }
                }
            }
        }

        // Territory control details
        if (flags & 0x40)
        {
            // if the civ has twelve cities this is 0 to 11 for that civ
            uint16 currCivCityID = *(uint16*)(it);
            // if the civ has 5, conquered 3 and destroyed 2, this has 1 to 9,
            //   missing 2 numbers
            uint16 iterativeCivCityID = *(uint16*)(it + 2);
            uint16 currCivCityID2 = *(uint16*)(it + 4);
            uint16 iterativeCivCityID2 = *(uint16*)(it + 6);
            uint16 currDistrictID = *(uint16*)(it + 8);
            uint16 iterativeDistrictID = *(uint16*)(it + 10);
            printf("   %3d - %3d", currCivCityID, iterativeCivCityID);
            if (currDistrictID != 0xFFFF)
                printf("   %3d - %3d", currDistrictID, iterativeDistrictID);
            it += 12;
            assert(currCivCityID == currCivCityID2 &&
                iterativeCivCityID == iterativeCivCityID2);

            uint8 civID = *it;
            printf("   %d", civID);
            it += 1;

            uint32 wonderHash = *(uint32*)(it);
            if (wonderHash != 0xFFFFFFFF)
            {
                name = LookupHash(wonderHash, dkBUILDING);
                if (name)
                    printf("   %s", name);
            }
            it += 4;
        }

        printf("\n");
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

    uint32 dist = it - body;
    printf("Offset: %d - 0x%08x - 0x%08x\n", dist, dist, dist - (dist % DEBUG_BYTE_WIDTH));
}
