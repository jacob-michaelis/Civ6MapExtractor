
#include "ParseGameData.h"

#include <stdio.h>
#include <assert.h>

#include "BlockParser.h"

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

    return it + (length * 2);
}

uint8 const* PrintPlayer(uint8 const* data)
{
    uint8 const* it = data;

    printf("   %d - %2d - %2d - %2d - %2d - %2d - %d\n",
        *(uint32*)(it), *(uint32*)(it + 4), *(uint32*)(it + 8), *(uint32*)(it + 12),
        *(uint32*)(it + 16), *(uint32*)(it + 20), *(it + 24));
    it += (6 * 4) + 1;

    printf("      Explored Area:\n");
    it = PrintArray8(it, 0);

    printf("      Visibility / Fog-of-War:\n");
    printf("      %d - 0x%08x - %d\n", *(uint32*)it, *(uint32*)(it + 4), *(uint32*)(it + 8));
    // The array stores the the number of "things" that can see that tile
    it += 12;
    it = PrintArray16(it, 0);

    printf("      Improvements:\n");
    printf("      0x%08x - %d\n", *(uint32*)it, *(uint32*)(it + 4));
    it += 8;
    it = PrintArray16(it, 0xFFFF);

    printf("      Resources:\n");
    printf("      0x%08x - %d\n", *(uint32*)it, *(uint32*)(it + 4));
    it += 8;
    it = PrintArray16(it, 0xFFFF);

    printf("      Roads:\n");
    printf("      0x%08x - %d\n", *(uint32*)it, *(uint32*)(it + 4));
    it += 8;
    it = PrintArray16(it, 0xFFFF);

    printf("      Unit Adjacency:\n");
    printf("      0x%08x - %d\n", *(uint32*)it, *(uint32*)(it + 4));
    it += 8;
    it = PrintArray16(it, 0);

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
    printf("   Settings set 0:\n");
    for (uint32 i = 0; i < numEntries1; ++i)
    {
        uint32 tag = *(uint32*)it;
        it += 4;
        uint32 value = *(uint32*)it;
        it += 4;
        printf("      0x%08x: %d\n", tag, value);
    }
    uint32 numEntries2 = *(uint32*)it;
    it += 4;
    printf("   Settings set 1:\n");
    for (uint32 i = 0; i < numEntries2; ++i)
    {
        uint32 tag = *(uint32*)it;
        it += 4;
        uint32 value = *(uint32*)it;
        it += 4;
        printf("      0x%08x: %d\n", tag, value);
    }
    assert(*(uint32*)it == 1);
    // Major civs + city states + barbarians + free cities
    uint32 numPlayers = *(uint32*)(it + 4);

    // Order is:
    // Player(s)
    // Civs in the order listed when clicking the player portrait
    // City States listed in the order on the city states tab
    for (uint32 i = 0; i < numPlayers; ++i)
    {
        printf("   Player %d Maps:\n", i);
        it = PrintPlayer(it);
    }

    uint32 dist = it - data;
    printf("Offset: %d - 0x%08x - 0x%08x\n", dist, dist, dist - (dist % 24));

    return it;
}


// --- Interface --------------------------------------------------------------

#include <vector>

void ParseGameData(uint8 const* body, uint8 const* bodyEnd)
{
    uint8 const* it = body;

    it = VerifyHeader(it);


    /*std::vector<uint32> tags;

    for (; it < bodyEnd; ++it)
    {
        while (it < bodyEnd && (
            *(uint32*)it != 4536 ||
            *(uint32*)(it + 4) != 84 ||
            *(uint32*)(it + 8) != 4536))
            ++it;

        uint32 tag = *(uint32*)(it - 8);
        if (std::find(tags.begin(), tags.end(), tag) == tags.end())
        {
            printf("0x%08x %d\n", tag, *(uint32*)(it - 4));
            tags.push_back(tag);
        }
    }*/
}
