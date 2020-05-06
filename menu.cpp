#include "menu.h"

int menu() {
    std::cout << "Would you like to: <1> Search and browse book information <2> Add a new book <3> Edit or delete existing books <4> Quit?" << std::endl << "-->";
    int choice;
    std::cin >> choice;
    std::cin.ignore(1000, '\n');
    while (choice < 1 || choice > 4) {
        std::cerr << "Please input a valid choice" << std::endl << "-->";
        std::cin >> choice;
        std::cin.ignore(1000, '\n');

    }
    switch (choice) {
    case 1:
        
        break;
    case 2:
        while (add_book() == 1);
        break;
    case 3:
        break;
    case 4:
        return quit();
    default:
        break;
    }
    return 0;
}

int quit() {
    std::cout << "Quit the system?<y/n>" << std::endl;
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
        return 0;
    }
}