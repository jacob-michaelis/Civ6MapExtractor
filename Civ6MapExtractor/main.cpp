
#include "Unpacker.h"
#include "ParseHeader.h"
#include "ParseGameData.h"
#include "ParseTail.h"
#include "SaveConstants.h"

#pragma comment(lib, "sqlite/sqlite3-static.lib")

#define SAVE 9

char const* saves[] =
{
    "ghaz0.Civ6Save",
    "long_test.Civ6Save",
    "pw6.Civ6Save",
    "ghaz1.Civ6Save", // 84 x 54
    "khmer0.Civ6Save", // 84 x 54
    // 5
    "khmer1.Civ6Save", // 84 x 54
    "pure_duel.Civ6Save", // 44 x 26 - 1144
    "First1.Civ6Save",
    "0_SettlerOnlineContinentsDuel.Civ6Save",
    "1_base.Civ6Save",
    // 10
    "2_base.Civ6Save",
    "3_base.Civ6Save",
    "4_base.Civ6Save",
    "5_base.Civ6Save",
    "6_base.Civ6Save",
    // 15
    "7_base.Civ6Save",
    "8_mods.Civ6Save",
    "9_mods.Civ6Save",
    "10_mods.Civ6Save",
    "11_mods.Civ6Save",
    // 20
    "pure_duel_exp.Civ6Save", // 44 x 26 - 1144
    "start0.Civ6Save",
    "start1.Civ6Save",
    "start2.Civ6Save",
    "start0_a.Civ6Save",
    // 25
    "start3.Civ6Save",
    "start4.Civ6Save",
    "start5.Civ6Save",
    "start6.Civ6Save",
    "hot0.Civ6Save",
    // 30
    "hot1.Civ6Save",
    "mp_spain_105.Civ6Save",
    "mp_spain_121.Civ6Save",
    "mp_spain_153.Civ6Save",
    "mp_spain_171.Civ6Save",
    // 35
    "mp_spain_226.Civ6Save",
    "mp_cree_35.Civ6Save",
    "mp_cree_67.Civ6Save",
    "mp_cree_83.Civ6Save",
    "mp_cree_85.Civ6Save",
    // 40
    "mp_cree_98.Civ6Save",
    "mp_cree_103.Civ6Save",
    "mp_cree_104.Civ6Save",
    "mp_cree_123.Civ6Save",
    "mp_cree_128.Civ6Save",
    // 45
    "mp_cree_128_2.Civ6Save",
    "mp_cree_136.Civ6Save",
    "raf_only.Civ6Save",
    "raf_w_modman.Civ6Save",
    "1_base_test_0.Civ6Save",
    // 50
};

int main(int argc, char* argv[])
{
    InitConstants();

    SaveData data;
    UnpackSave(saves[SAVE], &data);
    //ParseHeader(data.header, data.headerEnd);
    ParseGameData(data.gamedata, data.gamedataEnd);
    //ParseTail(data.tail, data.tailEnd);

    ReleaseSaveData(&data);

    //DumpTags();
    //DumpMissingTags();

    return 0;
}
