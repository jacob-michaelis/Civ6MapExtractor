
#include "Unpacker.h"
#include "ParseHeader.h"
#include "ParseGameData.h"
#include "ParseTail.h"
#include "SaveConstants.h"

#pragma comment(lib, "sqlite/sqlite3-static.lib")

#define SAVE 29

char const* saves[] =
{
    "ghaz0.Civ6Save",
    "long_test.Civ6Save",
    "pw6.Civ6Save",
    "ghaz1.Civ6Save", // 84 x 54
    "khmer0.Civ6Save", // 84 x 54
    "khmer1.Civ6Save", // 84 x 54
    "pure_duel.Civ6Save", // 44 x 26 - 1144
    "First1.Civ6Save",
    "0_SettlerOnlineContinentsDuel.Civ6Save",
    "1_base.Civ6Save",
    "2_base.Civ6Save",
    "3_base.Civ6Save",
    "4_base.Civ6Save",
    "5_base.Civ6Save",
    "6_base.Civ6Save",
    "7_base.Civ6Save",
    "8_mods.Civ6Save",
    "9_mods.Civ6Save",
    "10_mods.Civ6Save",
    "11_mods.Civ6Save",
    "pure_duel_exp.Civ6Save", // 44 x 26 - 1144
    "start0.Civ6Save",
    "start1.Civ6Save",
    "start2.Civ6Save",
    "start0_a.Civ6Save",
    "start3.Civ6Save",
    "start4.Civ6Save",
    "start5.Civ6Save",
    "start6.Civ6Save",
    "hot0.Civ6Save",
    "hot1.Civ6Save",
};

int main(int argc, char* argv[])
{
    InitConstants();

    SaveData data;
    UnpackSave(saves[SAVE], &data);
    ParseHeader(data.header, data.headerEnd);
    //ParseGameData(data.gamedata, data.gamedataEnd);
    //ParseTail(data.tail, data.tailEnd);

    ReleaseSaveData(&data);

    //DumpTags();
    //DumpMissingTags();

    return 0;
}
