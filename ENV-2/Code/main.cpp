#include "../myIncludes/MyComplex.h"
#include "../myIncludes/mergeSort.h"
#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    std::vector<MyComplex> arr = { MyComplex(3, 4), MyComplex(1, 1), MyComplex(2, -3) };

    std::cout << "Not sorted:\n";
    for (const auto& num : arr) {
        std::cout << num << " (the module is: " 
                  << std::fixed << std::setprecision(3) 
                  << num.modules() << ")\n";
    }

    mergeSortRec(arr, 0, arr.size() - 1);

    std::cout << "\nAfter sorting by magnitude:\n";
    for (const auto& num : arr) {
        std::cout << num << " (the module is: " 
                  << std::fixed << std::setprecision(3) 
                  << num.modules() << ")\n";
    }

    return 0;
}

