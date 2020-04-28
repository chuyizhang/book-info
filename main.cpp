#include "main.h"

int main(int argc, char const *argv[]) {
    //load database and table
    try {
        loadDB();
        loadTable();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    //print welcome info
    puts("============ Book Information Management System ============");

    //main loop
    while (!menu()) {
        ;
    }
    
    //close database
    try {
        closeDB();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}
