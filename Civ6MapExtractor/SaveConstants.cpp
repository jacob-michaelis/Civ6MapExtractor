
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
