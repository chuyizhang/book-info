#include <iostream>
#include <stdexcept>
#include <sqlite3.h>
#include <vector>
#include <cstdlib>
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

static std::string format(std::string origin) {
    std::string result;
    for (auto c : origin) {
        if (c != '\'') {
            result += c;
        } else {
            result += "\'\'";
        }
    }
    return result;
}

int insert(Book book) {
    std::string sql = "INSERT INTO book VALUES('" + book.book_isbn() + "', '" + format(book.book_title()) + "', '" + format(book.book_author()) + "', '" + format(book.book_publisher()) + "', " + std::to_string(book.book_year()) + ", " + std::to_string(book.book_price()) + ");";
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

static int callback(void* data, int argc, char** argv, char** col_name) {
    std::string isbn = std::string(argv[0]);
    std::string title = std::string(argv[1]);
    std::string author = std::string(argv[2]);
    std::string publisher = std::string(argv[3]);
    int year = atoi(argv[4]);
    double price = atof(argv[5]);
    Book book = Book(isbn, title, author, publisher, year, price);
    std::vector<std::string> *result = static_cast<std::vector<std::string>*>(data);
    result->push_back(isbn);
    std::cout << "<" << result->size() << ">" << std::endl << book <<std::endl;
    return 0;
}

int order(int element, int direction) {
    std::vector<std::string> order_elm{"ISBN", "Title", "Author", "Publisher", "Year", "Price"};
    std::vector<std::string> order_dir{"ASC", "DESC"};
    std::string query;
    if (order_elm[element] == "ISBN") {
        query = "SELECT * FROM book ORDER BY ISBN " + order_dir[direction] +";";
    } else {
        query = "SELECT * FROM book ORDER BY " + order_elm[element] + " " + order_dir[direction] + ", ISBN ASC;";
    }
    int exit;
    std::vector<std::string> result = {};
    char *messageError;
    exit = sqlite3_exec(db, query.c_str(), callback, &result, &messageError);
    if (exit != SQLITE_OK) {
        std::cout << messageError << std::endl;
        sqlite3_free(messageError);
        return -1;
    }
    std::cout << "Find " << result.size() << " results" << std::endl;
    return 0;
}
