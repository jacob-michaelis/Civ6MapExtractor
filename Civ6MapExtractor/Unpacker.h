// This tool seeks to unpack the binary data of a Civ6Save
//   file and but it in more readable .dat files
#pragma once

#include "typedefs.h"


struct SaveData
{
    uint8* header;
    uint8* headerEnd;
    uint8* gamedata;
    uint8* gamedataEnd;
    uint8* tail;
    uint8* tailEnd;
};

// exposed for utilities sake
void SaveToFile(char const* filename, uint8 const* data, uint32 size);

void UnpackSave(char const* filename, SaveData* out);
void ReleaseSaveData(SaveData* save);
