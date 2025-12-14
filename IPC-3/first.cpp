#include "shared.h"
#include <iostream>
#include <unistd.h>

int main() {
    shared_array arr("arr", 10);
    sem_t* sem = arr.get_semaphore();

    size_t pos = 0;
    int value = 0;

    while (true) {
        sem_wait(sem);
        arr[pos] = value;
        std::cout << "[first] " << pos << " -> " << value << "\n";
        sem_post(sem);

        pos = (pos + 1) % arr.size();
        value++;
        sleep(1);
    }
}

