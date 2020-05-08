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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Please input title" << std::endl << "-->";
    std::getline(std::cin, title);
    std::cout << "Please input author" << std::endl << "-->";
    std::getline(std::cin, author);
    std::cout << "Please input publisher" << std::endl << "-->";
    std::getline(std::cin, publisher);
    std::cout << "Please input publication year" << std::endl << "-->";
    while (!(std::cin >> year)) {
        std::cerr << "Please input a number!" << std::endl << "-->";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Please input price" << std::endl << "-->";
    while (!(std::cin >> price)) {
        std::cerr << "Please input a number!" << std::endl << "-->";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while ((s != "Y") && (s!= "y") && (s!= "N") && (s!= "n")) {
            std::cerr << "Please input a valid choice" << std::endl << "-->";
            std::cin >> s;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (s == "Y" || s == "y") {
            int insert_status = insert(new_book);
            if (insert_status) {
                if (insert_status == 1) {
                    std::cout << "Cannot add this book. Already have a book with same ISBN. Would you like to replace it?<y/n>" << std::endl << "-->";
                    std::string s;
                    std::cin >> s;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    while ((s != "Y") && (s!= "y") && (s!= "N") && (s!= "n")) {
                        std::cerr << "Please input a valid choice" << std::endl << "-->";
                        std::cin >> s;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    if (s == "Y" || s == "y") {
                        if (!delete_record(new_book.book_isbn())) {
                            if (!insert(new_book)) {
                                std::cout << "Book information successfully updated" << std::endl;
                            } else {
                                std::cerr << "Failed update book information!" << std::endl;
                                return -1;
                            }
                        } else {
                            std::cerr << "Failed update book information!" << std::endl;
                            return -1;
                        }
                    }
                    return 0;
                } else {
                    std::cerr << "Failed to add book!" << std::endl;
                    return -1;
                }
            } else {
                std::cout << "Book successfully added" << std::endl;
                return 0;
            }
        } else {
            return -1;
        }
    } else {
        std::cout << "Failed to add new book. Try again?<y/n>" << std::endl << "-->";
        std::string s;
        std::cin >> s;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while ((s != "Y") && (s!= "y") && (s!= "N") && (s!= "n")) {
            std::cerr << "Please input a valid choice" << std::endl << "-->";
            std::cin >> s;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (s == "Y" || s == "y") {
            return TRY_AGAIN;
        } else {
            return -1;
        }
    }
}

int browse_book() {
        std::cout << "Would you like to: <1> Browse all book information <2> Search book by title or ISBN <3> Filter books <4> Go back to main menu?" << std::endl << "-->";
        int choice = 0;
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (choice < 1 || choice > 4) {
            std::cerr << "Please input a valid choice" << std::endl << "-->";
            std::cin >> choice;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (choice == 1) {
            std::cout << "Would you like to order books by: <1> ISBN <2> Title <3> Author <4> Publisher <5> Publication year <6> Price?" << std::endl << "-->";
            int element_num = 0;
            std::cin >> element_num;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while (element_num < 1 || element_num > 6) {
                std::cerr << "Please input a valid choice" << std::endl << "-->";
                std::cin >> element_num;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << "Would you like to order books in: <1> Ascending order <2> Descending order?" << std::endl << "-->";
            int direction_num = 0;
            std::cin >> direction_num;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while (direction_num < 1 || direction_num > 2) {
                std::cerr << "Please input a valid choice" << std::endl << "-->";
                std::cin >> direction_num;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            return order(element_num - 1, direction_num - 1);
        }
    return 0;
}
