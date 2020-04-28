#include "main.h"

int main(int argc, char const *argv[]) {
    try {
        loadDB();
        loadTable();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    try {
        closeDB();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}
