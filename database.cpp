#include <iostream>
#include <stdexcept>
#include <sqlite3.h>
#include "Book.h"

static sqlite3 *db;

void loadDB() {
    int exit;
    exit = sqlite3_open("bookInfo.db", &db);
    if (exit) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }
    return;
}

void loadTable() {
    std::string sql = "CREATE TABLE IF NOT EXISTS book("
                      "ISBN TEXT PRIMARY KEY NOT NULL,"
                      "Title TEXT NOT NULL,"
                      "Author TEXT NOT NULL,"
                      "Publisher TEXT NOT NULL,"
                      "Year INT NOT NULL,"
                      "Price REAL NOT NULL);";
    int exit;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, NULL);
    if (exit) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }
    return;
}

void closeDB() {
    int exit;
    exit = sqlite3_close(db);
    if (exit) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }
    return;
}
