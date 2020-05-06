#include "operate.h"

int add_book() {
    std::string isbn;
    std::string title;
    std::string author;
    std::string publisher;
    int year;
    double price;
    std::cout << "Please input ISBN (10 or 13 digits)" << std::endl << "-->";
    std::cin >> isbn;
    std::cin.ignore(1000, '\n');
    std::cout << "Please input title" << std::endl << "-->";
    std::getline(std::cin, title);
    std::cout << "Please input author" << std::endl << "-->";
    std::getline(std::cin, author);
    std::cout << "Please input publisher" << std::endl << "-->";
    std::getline(std::cin, publisher);
    std::cout << "Please input publication year" << std::endl << "-->";
    std::cin >> year;
    std::cin.ignore(1000, '\n');
    std::cout << "Please input price" << std::endl << "-->";
    std::cin >> price;
    std::cin.ignore(1000, '\n');
    bool is_isbn_valid, is_year_valid, is_price_valid;
    //test isbn
    if (isbn.size() == 10 || isbn.size() == 13) {
        is_isbn_valid = true;
        for (auto c : isbn) {
            if (!isdigit(c)) {
                is_isbn_valid = false;
            }
        }
    } else {
        is_isbn_valid = false;
    }
    if (!is_isbn_valid) {
        std::cerr << "Error: The ISBN is invalid!" << std::endl;
    }
    //test year
    time_t now = time(0);
    tm *ltm = localtime(&now);
    if (year <= 1900 + ltm->tm_year) {
        is_year_valid = true;
    } else {
        is_year_valid = false;
        std::cerr << "Error: The publication year is invalid!" << std::endl;
    }
    //test price
    if ((price >= 0) && ((100 * price) == floor(100 * price))) {
        is_price_valid = true;
    } else {
        is_price_valid = false;
        std::cerr << "Error: The price is invalid!" << std::endl;
    }
    //user decision
    if (is_isbn_valid && is_year_valid && is_price_valid) {
        Book new_book = Book(isbn, title, author, publisher, year, price);
        std::cout << "Would you like to add the following book?<y/n>" << std::endl << new_book << std::endl << "-->";
        std::string s;
        std::cin >> s;
        std::cin.ignore(1000, '\n');
        while ((s != "Y") && (s!= "y") && (s!= "N") && (s!= "n")) {
            std::cerr << "Please input a valid choice" << std::endl << "-->";
            std::cin >> s;
            std::cin.ignore(1000, '\n');
        }
        if (s == "Y" || s == "y") {
            return 0;
        } else {
            return -1;
        }
    } else {
        std::cout << "Failed to add new book. Try again?<y/n>" << std::endl << "-->";
        std::string s;
        std::cin >> s;
        std::cin.ignore(1000, '\n');
        while ((s != "Y") && (s!= "y") && (s!= "N") && (s!= "n")) {
            std::cerr << "Please input a valid choice" << std::endl << "-->";
            std::cin >> s;
            std::cin.ignore(1000, '\n');
        }
        if (s == "Y" || s == "y") {
            return 1;
        } else {
            return -1;
        }
    }
}
