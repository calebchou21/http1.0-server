#include <iostream>

#include "test_file_service.h"

int main() {
    int failed = 0;
    
    failed += runFileServiceTests();

    if (failed == 0) {
        std::cout << "All tests passed!" << std::endl;
        return 0;
    } else {
        std::cout << failed << " test(s) failed :(" << std::endl;
        return 1;
    }
}
