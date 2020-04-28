#include <iostream>
#include <stdexcept>
#include <sqlite3.h>

static sqlite3 *db;

void loadDB() {
    int exit;
    exit = sqlite3_open("bookInfo.db", &db);
    if (exit) {
        throw std::runtime_error(sqlite3_errmsg(db));
    } else {
        return;
    }
}

void closeDB() {
    int exit;
    exit = sqlite3_close(db);
    if (exit) {
        throw std::runtime_error(sqlite3_errmsg(db));
    } else {
        return;
    }
}
