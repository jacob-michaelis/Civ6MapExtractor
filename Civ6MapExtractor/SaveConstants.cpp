
#include "SaveConstants.h"

#include <assert.h>
#include <unordered_map>


// Data Tags

DataTagDetails dataTagDetails[] =
{
#undef CONVERT
#define CONVERT(id, val, leVal, name, desc) { name, desc, leVal },
    DATA_TAG_LIST
#undef CONVERT
};

std::unordered_map<uint32, DataTagDetails*> tagMap;

static void InitDataTagDetails()
{
    uint32 tagIDList[] =
    {
#undef CONVERT
#define CONVERT(id, val, leVal, name, desc) val,
        DATA_TAG_LIST
#undef CONVERT
    };
    uint32 tagListLen = sizeof dataTagDetails / sizeof * dataTagDetails;

    for (uint32 i = 0; i < tagListLen; ++i)
    {
        uint32 dtID = tagIDList[i];
        tagMap[dtID] = dataTagDetails + i;
    }
}

DataTagDetails GetDataTagDetails(uint32 dt)
{
    return *tagMap[dt];
}

char const* DataTagName(uint32 dt)
{
    return tagMap[dt]->name;
}

char const* DataTagDesc(uint32 dt)
{
    return tagMap[dt]->desc;
}

char const* DataTagLEID(uint32 dt)
{
    return tagMap[dt]->idLE;
}


#ifdef TRACK_TAGS
#include <vector>
std::vector<uint32> tags;

void TrackTag(uint32 tag)
{
    if (std::find(tags.begin(), tags.end(), tag) == tags.end())
        tags.push_back(tag);
}

void DumpTags()
{
    for (uint32 i = 0; i < tags.size(); ++i)
    {
        uint32 tag = tags[i];
        uint8* leTag = (uint8*)(&tags[i]);

        char num[5];
        sprintf(num, "%04d", i);
        char* it = num;
        char* end = num + 3;
        for (; it < end && *it == '0'; ++it)
            *it = '_';

        printf("    CONVERT(Unknown_%s, 0x%08x, \"%02x%02x%02x%02x\", \"NAME\", \"DESC\") \\\n", num, tag, leTag[0], leTag[1], leTag[2], leTag[3]);
    }
}

void DumpMissingTags()
{
    if (tagMap.find(tags.front()) == tagMap.end())
    {
        if (tags.size() == 1)
            printf("Missing tag %08x\n", tags[0]);
        else
            printf("Missing tag %08x before %08x\n", tags[0], tags[1]);
    }

    uint32 sizeM1 = tags.size() - 1;

    for (uint32 i = 1; i < sizeM1; ++i)
        if (tagMap.find(tags[i]) == tagMap.end())
            printf("Missing tag %08x after %08x before %08x\n", tags[i], tags[i-1], tags[i+1]);

    if (tagMap.find(tags.back()) == tagMap.end() &&
        tags.size() != 1)
        printf("Missing tag %08x after %08x\n", tags[sizeM1], tags[sizeM1 - 1]);

    for (uint32 i = 0; i < tags.size(); ++i)
        if (tagMap.find(tags[i]) == tagMap.end())
        {
            uint32 tag = tags[i];
            uint8* leTag = (uint8*)(&tags[i]);

            char num[5];
            sprintf(num, "%04d", i);
            char* it = num;
            char* end = num + 3;
            for (; it < end && *it == '0'; ++it)
                *it = '_';
            printf("    CONVERT(Unknown_%s, 0x%08x, \"%02x%02x%02x%02x\", \"NAME\", \"DESC\") \\\n", num, tag, leTag[0], leTag[1], leTag[2], leTag[3]);
        }
}
#endif


// Block Types

// Verify everything aligns, if there is an assert BLOCK_TYPES_LIST
//   has a gap in values that needs filling
#undef CONVERT
#define CONVERT(id, val) STATIC_ASSERT(bt##val##_##id == 0x##val);
BLOCK_TYPE_LIST
#undef CONVERT

char const* blockTypeStr[] =
{
#undef CONVERT
#define CONVERT(id, val) #id[0] == 't' ? "Unknown (0x"#val")" : #id,
    BLOCK_TYPE_LIST
#undef CONVERT

    "INVALID_BLOCK_NAME"
};

char const* BlockTypeStr(uint32 bt)
{
    assert(bt < btEND);
    return blockTypeStr[bt];
}


// Setup

void InitConstants()
{
    InitDataTagDetails();
}
