#include <iostream>
#include "lib_sch.h"

int a = 0;
int b = 0;
int c = 0;

void work1(int x) {
    for(int k = 0; k < x; k++) {
        a++;
    }
    std::cout << a << std::endl;
}

void work2(int x) {
    for(int k = 0; k < x; k++) {
        b++;
    }
    std::cout << b << std::endl;
}

void work3(int x) {
    for(int k = 0; k < x; k++) {
        c++;
    }
    std::cout << c << std::endl;
}

int main() {
    parallel_scheduler scheduler(2);

    scheduler.run(work1, 50000);
    scheduler.run(work2, 50000);
    scheduler.run(work3, 50000);

    return 0;
}

