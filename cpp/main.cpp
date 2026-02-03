#include <iostream>
#include "rust_api.h"

int main() {
    std::cout << "3 + 4 = " << rust_add(3, 4) << std::endl;
}