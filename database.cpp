#include <iostream>
#include <stdexcept>
#include <sqlite3.h>
#include "Book.h"

static sqlite3 *db;

void loadDB() {
    int exit;
    exit = sqlite3_open("bookInfo.db", &db);
    if (exit != SQLITE_OK) {
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
    char *messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cout << messageError << std::endl;
        sqlite3_free(messageError);
        throw std::runtime_error(sqlite3_errmsg(db));
    }
    return;
}

void closeDB() {
    int exit;
    exit = sqlite3_close(db);
    if (exit != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }
    return;
}

int insert(Book book) {
    std::string sql = "INSERT INTO book VALUES('" + book.book_isbn() + "', '" + book.book_title() + "', '" + book.book_author() + "', '" + book.book_publisher() + "', " + std::to_string(book.book_year()) + ", " + std::to_string(book.book_price()) + ");";
    int exit;
    char *messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        if (sqlite3_extended_errcode(db) == SQLITE_CONSTRAINT_PRIMARYKEY) {
            sqlite3_free(messageError);
            return 1;
        } else {
            std::cout << messageError << std::endl;
            sqlite3_free(messageError);
            return -1;
        }
    }
    return 0;
}

int delete_record(std::string isbn) {
    std::string sql = "DELETE FROM book WHERE ISBN = '" + isbn + "';";
    int exit;
    char *messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cout << messageError << std::endl;
        sqlite3_free(messageError);
        return -1;
    }
    return 0;
}
