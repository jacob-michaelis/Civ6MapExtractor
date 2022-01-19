
#include "LoadSQLiteConstants.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <unordered_map>
#include <string>

#include "sqlite/sqlite3.h"

typedef std::unordered_map<uint32, std::string> HashMap;

struct Storage
{
    // +1 size for dkAll
    HashMap map[dkNUM + 1];
};


// --- Constants --------------------------------------------------------------

#define STATEMENT_BUF_SIZE 1024


// --- Globals ----------------------------------------------------------------

Storage* gs;

char const* hashKindStr[] =
{
#undef CONVERT
#define CONVERT(x) "KIND_"#x,
    HASH_KIND_LIST
#undef CONVERT
};

// --- Utility ----------------------------------------------------------------

static inline bool HandleSQLError(int32 error, sqlite3* db)
{
    if (error != SQLITE_OK)
    {
        printf("SQL error: %s\n", sqlite3_errmsg(db));
        assert(0);
        sqlite3_close(db);
        return true;
    }

    return false;
}

static sqlite3* OpenDB(char const* name)
{
    sqlite3* db = nullptr;
    int32 error = sqlite3_open(name, &db);
    if (HandleSQLError(error, db))
        return NULL;

    printf("%s successfully opened!\n", name);

    return db;
}

static void CloseDB(sqlite3* db)
{
    sqlite3_close(db);
}


// --- Queries ----------------------------------------------------------------

static void ListDistinctValues(sqlite3* db, char const* table, char const* column)
{
    char statement[STATEMENT_BUF_SIZE];
    sprintf(statement, "SELECT DISTINCT %s FROM %s ORDER BY %s ASC;", column, table, column);

    sqlite3_stmt* stmt;
    int32 error = sqlite3_prepare_v2(db, statement, -1, &stmt, NULL);
    if (HandleSQLError(error, db))
        return;

    for (; sqlite3_step(stmt) != SQLITE_DONE;)
    {
        // assuming text for now
        uint8 const* val = sqlite3_column_text(stmt, 0);

        printf("%s\n", val);
    }

    error = sqlite3_finalize(stmt);
    if (HandleSQLError(error, db))
        return;
}

static void LoadTypeHashes(sqlite3* db)
{
    char statement[STATEMENT_BUF_SIZE];
    sprintf(statement, "SELECT * FROM Types WHERE Kind = ?;");

    sqlite3_stmt* stmt;
    int32 error = sqlite3_prepare_v2(db, statement, -1, &stmt, NULL);
    if (HandleSQLError(error, db))
        return;

    HashMap* allMap = &gs->map[dkAll];
    
    for (uint32 i = 0; i < dkNUM; ++i)
    {
        HashMap* map = &gs->map[i];
        sqlite3_bind_text(stmt, 1, hashKindStr[i], -1, SQLITE_STATIC);

        for (; sqlite3_step(stmt) != SQLITE_DONE;)
        {
            uint8 const* typeStr = sqlite3_column_text(stmt, 0);
            uint32 hash = (uint32)sqlite3_column_int(stmt, 1);

            (*map)[hash] = (char const*)typeStr;
            (*allMap)[hash] = (char const*)typeStr;
        }

        sqlite3_clear_bindings(stmt);
        sqlite3_reset(stmt);
    }

    error = sqlite3_finalize(stmt);
    if (HandleSQLError(error, db))
        return;
}


// --- Interface --------------------------------------------------------------

void InitSQLiteConstantsTracker()
{
    gs = new Storage;
}

void ExitSQLiteConstantsTracker()
{
    delete gs;
}



void LoadDebugConfigurationConstants(char const* path)
{
    assert(gs);

    sqlite3* db = OpenDB(path);

    CloseDB(db);
}

void LoadDebugGameplayConstants(char const* path)
{
    assert(gs);

    sqlite3* db = OpenDB(path);

    LoadTypeHashes(db);

    CloseDB(db);

    return;
}

char const* LookupHash(uint32 hash, DataKind kind)
{
    assert(gs);

    if (kind < 0 || kind > dkAll)
        return NULL;

    HashMap::iterator it = gs->map[kind].find(hash);
    if (it == gs->map[kind].end())
        return NULL;

    return it->second.c_str();
}
