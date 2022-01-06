
#include "Unpacker.h"

#pragma comment(lib, "sqlite/sqlite3-static.lib")


int main(int argc, char* argv[])
{
    SaveData data;
    UnpackSave("ghaz0.Civ6Save", &data);
    //UnpackSave("long_test.Civ6Save");

    return 0;
}
