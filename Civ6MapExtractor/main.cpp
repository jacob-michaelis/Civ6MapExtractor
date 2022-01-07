
#include "Unpacker.h"
#include "ParseHeader.h"

#pragma comment(lib, "sqlite/sqlite3-static.lib")

#define SAVE 6

#if SAVE == 0
char const* save = "ghaz0.Civ6Save";
#elif SAVE == 1
char const* save = "long_test.Civ6Save";
#elif SAVE == 2
char const* save = "pw6.Civ6Save";
#elif SAVE == 3
char const* save = "ghaz1.Civ6Save";
#elif SAVE == 4
char const* save = "khmer0.Civ6Save";
#elif SAVE == 5
char const* save = "khmer1.Civ6Save";
#elif SAVE == 6
char const* save = "pure_duel.Civ6Save";
#endif

int main(int argc, char* argv[])
{
    SaveData data;
    UnpackSave(save, &data);
    ParseHeader(data.header, data.headerEnd);

    ReleaseSaveData(&data);

    return 0;
}
