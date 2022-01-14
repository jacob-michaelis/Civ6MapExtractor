
#include "ParseGameData.h"

#include <stdio.h>
#include <vector>

#include "BlockParser.h"

// 0   26103511   26 10 35 11
// 1   cf56a3f7   cf 56 a3 f7
// 2   8f2880d1   8f 28 80 d1   Discovered Resources
// 3   5cf9a6a8   5c f9 a6 a8
// 4   bdbef3c1   bd be f3 c1
#define TAG_UNK0 0x11351026
#define TAG_UNK1 0xf7a356cf
#define TAG_UNK2 0xd180288f
#define TAG_UNK3 0xa8a6f95c
#define TAG_UNK4 0xc1f3bebd


extern uint8 const* Parse03(uint8 const* data);
extern uint8 const* Parse05(uint8 const* data);

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
            printf("WARNING: Header mismatch at %d.", i);

    uint8 const* it = data;

    it = Parse03(it + 8);
    it = Parse05(it);


    return it;
}




uint8 const* ParseUnk00(uint8 const* tail, uint8 const* it)
{
    if (*(uint32*)(it + 4) != 0x00)
        return it;

    uint32 address = (it - tail);
    uint32 address32 = (it - tail) / 32 * 32;
    printf("Found features at address 0x%08x on line 0x%08x\n", address, address32);

    uint32 length0 = *(uint32*)(it + 8);
    uint32 width = *(uint32*)(it + 12);
    uint32 length1 = *(uint32*)(it + 16);
    uint8* arr = (uint8*)(it + 20);

    uint32 height = length0 / width;
    uint8* arrIt = arr;

    for (uint32 y = 0; y < height; ++y)
    {
        for (uint32 x = 0; x < width; ++x, arrIt += 2)
        {
            uint16 val = *(uint16*)arrIt;
            if (val != 0x0)
                printf("Found resource %d at %d (%d, %d)\n", val, arrIt - arr, x, y);
        }
    }

    return arrIt;
}

uint8 const* ParseUnk01(uint8 const* tail, uint8 const* it)
{
    if (*(uint32*)(it + 4) != 0x01)
        return it;

    uint32 address = (it - tail);
    uint32 address32 = (it - tail) / 32 * 32;
    printf("Found features at address 0x%08x on line 0x%08x\n", address, address32);

    uint32 length0 = *(uint32*)(it + 8);
    uint32 width = *(uint32*)(it + 12);
    uint32 length1 = *(uint32*)(it + 16);
    uint8* arr = (uint8*)(it + 20);

    uint32 height = length0 / width;
    uint8* arrIt = arr;

    for (uint32 y = 0; y < height; ++y)
    {
        for (uint32 x = 0; x < width; ++x, arrIt += 2)
        {
            uint16 val = *(uint16*)arrIt;
            if (val != 0x0)
                printf("Found resource %d at %d (%d, %d)\n", val, arrIt - arr, x, y);
        }
    }

    return arrIt;
}

uint8 const* ParseUnk02(uint8 const* tail, uint8 const* it)
{
    if (*(uint32*)(it + 4) != 0x02)
        return it;

    uint32 address = (it - tail);
    uint32 address32 = (it - tail) / 32 * 32;
    printf("Found features at address 0x%08x on line 0x%08x\n", address, address32);

    uint32 length0 = *(uint32*)(it + 8);
    uint32 width = *(uint32*)(it + 12);
    uint32 length1 = *(uint32*)(it + 16);
    uint8* arr = (uint8*)(it + 20);

    uint32 height = length0 / width;
    uint8* arrIt = arr;

    for (uint32 y = 0; y < height; ++y)
    {
        for (uint32 x = 0; x < width; ++x, arrIt += 2)
        {
            uint16 val = *(uint16*)arrIt;
            if (val != 0xFFFF)
                printf("Found resource %d at %d (%d, %d)\n", val, arrIt - arr, x, y);
        }
    }

    return arrIt;
}

uint8 const* ParseUnk03(uint8 const* tail, uint8 const* it)
{
    if (*(uint32*)(it + 4) != 0x03)
        return it;

    uint32 address = (it - tail);
    uint32 address32 = (it - tail) / 32 * 32;
    printf("Found features at address 0x%08x on line 0x%08x\n", address, address32);

    uint32 length0 = *(uint32*)(it + 8);
    uint32 width = *(uint32*)(it + 12);
    uint32 length1 = *(uint32*)(it + 16);
    uint8* arr = (uint8*)(it + 20);

    uint32 height = length0 / width;
    uint8* arrIt = arr;

    for (uint32 y = 0; y < height; ++y)
    {
        for (uint32 x = 0; x < width; ++x, arrIt += 2)
        {
            uint16 val = *(uint16*)arrIt;
            if (val != 0xFFFF)
                printf("Found resource %d at %d (%d, %d)\n", val, arrIt - arr, x, y);
        }
    }

    return arrIt;
}

uint8 const* ParseUnk04(uint8 const* tail, uint8 const* it)
{
    if (*(uint32*)(it + 4) != 0x04)
        return it;

    uint32 address = (it - tail);
    uint32 address32 = (it - tail) / 32 * 32;
    printf("Found features at address 0x%08x on line 0x%08x\n", address, address32);

    uint32 length0 = *(uint32*)(it + 8);
    uint32 width = *(uint32*)(it + 12);
    uint32 length1 = *(uint32*)(it + 16);
    uint8* arr = (uint8*)(it + 20);

    uint32 height = length0 / width;
    uint8* arrIt = arr;

    for (uint32 y = 0; y < height; ++y)
    {
        for (uint32 x = 0; x < width; ++x, arrIt += 3)
        {
            uint32 val = *(uint32*)arrIt & 0xFFFFFF;
            if (val)
                printf("Found token %d at %d (%d, %d)\n", val, arrIt - arr, x, y);
        }
    }

    return arrIt;
}

void ParseGameData(uint8 const* tail, uint8 const* tailEnd)
{
    uint8 const* it = tail;

    uint32 featuresDataTag = TAG_UNK4;
    uint32 featuresDataType = 0x00;

    for (; it < tailEnd; ++it)
    {
        uint32 prospectiveTag = *(uint32*)it;

        switch (prospectiveTag)
        {
        case TAG_UNK0:
            //it = ParseUnk00(tail, it);
            break;
        case TAG_UNK1:
            //it = ParseUnk01(tail, it);
            break;
        case TAG_UNK2:
            it = ParseUnk02(tail, it);
            break;
        case TAG_UNK3:
            //it = ParseUnk03(tail, it);
            break;
        case TAG_UNK4:
            //it = ParseUnk04(tail, it);
            break;
        default:
            break;
        }
    }


    /*std::vector<uint32> tags;

    for (; it < tailEnd; ++it)
    {
        while (it < tailEnd && (
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
