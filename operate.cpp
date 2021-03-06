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
    std::cout << "Would you like to: <1> Browse all book information <2> Search book <3> Filter books <4> Go back to main menu?" << std::endl << "-->";
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
    } else if (choice == 2) {
        std::string text;
        do {
            std::cout << "Please input ISBN or book title" << std::endl << "-->";
            std::getline(std::cin, text);
        } while (text.empty());
        std::vector<std::string> result = {};
        return search(text, result);
    } else if (choice == 3) {
        std::string publisher;
        std::cout << "Please input publisher. Press ENTER for any publisher." <<std::endl << "-->";
        std::getline(std::cin, publisher);
        std::vector<std::string> conditions = {};
        //minimum year
        std::string min_year_str;
        std::cout << "Please input minimum year. Press ENTER for no limit." << std::endl << "-->";
        std::getline(std::cin, min_year_str);
        if (min_year_str != "") {
            int min_year;
            try {
                min_year = std::stoi(min_year_str);
                conditions.push_back("Year >= " + std::to_string(min_year));
            }
            catch(const std::exception& e) {
                std::cerr << "You did not enter a valid number. The condition is discarded." << std::endl;;
            }
        }
        //maximum year
        std::string max_year_str;
        std::cout << "Please input maximum year. Press ENTER for no limit." << std::endl << "-->";
        std::getline(std::cin, max_year_str);
        if (max_year_str != "") {
            int max_year;
            try {
                max_year = std::stod(max_year_str);
                conditions.push_back("Year <= " + std::to_string(max_year));
            }
            catch(const std::exception& e) {
                std::cerr << "You did not enter a valid number. The condition is discarded." << std::endl;
            }
        }
        //minimum price
        std::string min_price_str;
        std::cout << "Please input minimum price. Press ENTER for no limit." << std::endl << "-->";
        std::getline(std::cin, min_price_str);
        if (min_price_str != "") {
            double min_price;
            try {
                min_price = std::stod(min_price_str);
                conditions.push_back("Price >= " + std::to_string(min_price));
            }
            catch(const std::exception& e) {
                std::cerr << "You did not enter a valid number. The condition is discarded." << std::endl;
            }
        }
        //maximum price
        std::string max_price_str;
        std::cout << "Please input maximum price. Press ENTER for no limit." << std::endl << "-->";
        std::getline(std::cin, max_price_str);
        if (max_price_str != "") {
            double max_price;
            try {
                max_price = std::stod(max_price_str);
                conditions.push_back("Price <= " + std::to_string(max_price));
            }
            catch(const std::exception& e) {
                std::cerr << "You did not enter a valid number. The condition is discarded." << std::endl;
            }
        }
        return filter(publisher, conditions);
    }
    return 0;
}

int edit_book() {
    std::string text;
    do {
        std::cout << "Please input ISBN or book title" << std::endl << "-->";
        std::getline(std::cin, text);
    } while (text.empty());
    std::vector<std::string> result = {};
    search(text, result);
    int selected = 0;
    if (result.size() == 0) {
        selected = 0;
    } else if (result.size() == 1) {
        selected = 1;
    } else {
        std::cout << "Please input a number to select a book to modify. Input 0 to cancel." << std::endl <<"-->";
        std::cin >> selected;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (selected < 0 || selected > result.size()) {
            std::cerr << "Please input a valid number" << std::endl << "-->";
            std::cin >> selected;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    if (selected) {
        std::cout << "Would edit following book:" << std::endl;
        if (!select(result[selected - 1])) {
            std::cout << "Would you like to: <1> Edit book information <2> Delete book <3> Cancel" << std::endl << "-->";
            int choice = 0;
            std::cin >> choice;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while (choice < 1 || choice > 3) {
                std::cerr << "Please input a valid choice" << std::endl << "-->";
                std::cin >> choice;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            if (choice == 1) {
                std::vector<std::string> changes = {};
                //ISBN
                std::cout << "Please input new ISBN (10 or 13 digits). Press ENTER to keep original information." << std::endl << "-->";
                std::string new_isbn;
                std::getline(std::cin, new_isbn);
                if (new_isbn != "") {
                    bool is_isbn_valid;
                    if (new_isbn.size() == 10 || new_isbn.size() == 13) {
                        is_isbn_valid = true;
                        for (auto c : new_isbn) {
                            if (!isdigit(c)) {
                                is_isbn_valid = false;
                            }
                        }
                    } else {
                        is_isbn_valid = false;
                    }
                    if (is_isbn_valid) {
                        changes.push_back("ISBN = '" + new_isbn + "'");
                    } else {
                        std::cout << "You did not input a valid ISBN. The change is discarded." << std::endl;
                    }
                }
                //title
                std::cout << "Please input new title. Press ENTER to keep original information." << std::endl << "-->";
                std::string new_title;
                std::getline(std::cin, new_title);
                if (new_title != "") {
                    changes.push_back("Title = '" + format(new_title) + "'");
                }
                //author
                std::cout << "Please input new author. Press ENTER to keep original information." << std::endl << "-->";
                std::string new_author;
                std::getline(std::cin, new_author);
                if (new_author != "") {
                    changes.push_back("Author = '" + format(new_author) + "'");
                }
                //publisher
                std::cout << "Please input new publisher. Press ENTER to keep original information." << std::endl << "-->";
                std::string new_publisher;
                std::getline(std::cin, new_publisher);
                if (new_publisher != "") {
                    changes.push_back("Publisher = '" + format(new_publisher) + "'");
                }
                //year
                std::cout << "Please input new publication year. Press ENTER to keep original information." << std::endl << "-->";
                std::string new_year_str;
                std::getline(std::cin, new_year_str);
                if (new_year_str != "") {
                    int new_year;
                    try {
                        new_year = std::stoi(new_year_str);
                        time_t now = time(0);
                        tm *ltm = localtime(&now);
                        if (new_year <= 1900 + ltm->tm_year) {
                            changes.push_back("Year = " + std::to_string(new_year));
                        } else {
                            std::cout << "You did not enter a valid year. The change is discarded." << std::endl;
                        }
                    }
                    catch(const std::exception& e) {
                        std::cout << "You did not enter a valid year. The change is discarded." << std::endl;
                    }
                }
                //price
                std::cout << "Please input new price. Press ENTER to keep original information." << std::endl << "-->";
                std::string new_price_str;
                std::getline(std::cin, new_price_str);
                if (new_price_str != "") {
                    double new_price;
                    try {
                        new_price = std::stod(new_price_str);
                        if ((new_price >= 0) && ((100 * new_price) == floor(100 * new_price))) {
                            changes.push_back("Price = " + std::to_string(new_price));
                        } else {
                            std::cout << "You did not enter a valid price. The change is discarded." << std::endl;
                        }
                    }
                    catch(const std::exception& e) {
                        std::cout << "You did not enter a valid price. The change is discarded." << std::endl;
                    }
                }
                //make change
                if (changes.size() == 0) {
                    std::cout << "You did not make any changes." << std::endl;
                } else  {
                    std::cout << "Confirm changes?<y/n>" << std::endl << "-->";
                    std::string s;
                    std::cin >> s;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    while ((s != "Y") && (s!= "y") && (s!= "N") && (s!= "n")) {
                        std::cerr << "Please input a valid choice" << std::endl << "-->";
                        std::cin >> s;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    if (s == "Y" || s == "y") {
                        int status;
                        status = update_book(result[selected - 1], changes);
                        if (!status) {
                            std::cout << "Book successfully updated." <<std::endl;
                        }
                        return status;
                    }
                }
            } else if (choice == 2) {
                std::cout << "Would you like to delete the book?<y/n>" << std::endl << "-->";
                std::string s;
                std::cin >> s;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                while ((s != "Y") && (s!= "y") && (s!= "N") && (s!= "n")) {
                    std::cerr << "Please input a valid choice" << std::endl << "-->";
                    std::cin >> s;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                if (s == "Y" || s == "y") {
                    int status;
                    status = delete_record(result[selected - 1]);
                    if (!status) {
                        std::cout << "Book successfully deleted." <<std::endl;
                    }
                    return status;
                }
            }
        }
    }
    return 0;
}
