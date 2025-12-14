#include "shared.h"
#include <iostream>
#include <unistd.h>

int main() {
    shared_array arr("arr", 10);
    sem_t* sem = arr.get_semaphore();

    while (true) {
        sem_wait(sem);
        std::cout << "[second] ";
        for (size_t i = 0; i < arr.size(); ++i) {
            std::cout << arr[i] << " ";
            arr[i] += 14;
        }
        std::cout << "\n";
        sem_post(sem);
        sleep(2);
    }
}
