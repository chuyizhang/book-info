#ifndef BOOK_H
#define BOOK_H
#include <iostream>
class Book {
    private:
        std::string isbn;
        std::string title;
        std::string author;
        std::string publisher;
        int year;
        double price;
    public:
        Book(std::string isbn_str, std::string title_str, std::string author_str, std::string publisher_str, int y, double p): isbn(isbn_str), title(title_str), author(author_str), publisher(publisher_str), year(y), price(p) {
        }
        std::ostream &print(std::ostream &os, const Book book) {
            os << "ISBN: " << book.isbn << "\n"
               << "Title: " << book.title << "\n"
               << "Author: " << book.author << "\n"
               << "Publisher: " << book.publisher << "\n"
               << "Year of Publish: " << book.year << "\n"
               << "Price: " << book.price;
        }
};
#endif
