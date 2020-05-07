#ifndef BOOK_H
#define BOOK_H
#include <iostream>
class Book {
    friend std::ostream &operator<<(std::ostream&, const Book&);
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
        std::string book_isbn() const {
            return isbn;
        }
        std::string book_title() const {
            return title;
        }
        std::string book_author() const {
            return author;
        }
        std::string book_publisher() const {
            return publisher;
        }
        int book_year() const {
            return year;
        }
        double book_price() const {
            return price;
        }
};

inline std::ostream& operator<<(std::ostream &os, const Book &book) {
    std::cout.precision(2);
    os << std::fixed
       << "ISBN: " << book.isbn << "\n"
       << "Title: " << book.title << "\n"
       << "Author: " << book.author << "\n"
       << "Publisher: " << book.publisher << "\n"
       << "Publication Year: " << book.year << "\n"
       << "Price: " << book.price;
    return os;
}
#endif
