#include <iostream>
#include <pthread.h>
#include <ctime>
#include <cstdlib>

struct TData {
    pthread_t tid;
    int* arr;
    int left;
    int right;
    long sum;
};

void* part_sum(void* arg) {
    TData* d = (TData*) arg;
    long s = 0;

    for (int i = d->left; i < d->right; i++) {
        s += d->arr[i];
    }

    d->sum = s;
    return NULL;
}

void sumArray(int n, int m) {
    int* arr = new int[n];

    //рандом
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10 + 1;   // числа от 1 до 10
    }


    TData* info = new TData[m];
    int step = n / m;

    std::clock_t t1 = std::clock();

    for (int i = 0; i < m; i++) {
        info[i].arr = arr;
        info[i].left = i * step;

        if (i == m - 1) {
            info[i].right = n;  
        } else {
            info[i].right = (i + 1) * step;
        }

        pthread_create(&info[i].tid, NULL, part_sum, &info[i]);
    }

    long total = 0;
    for (int i = 0; i < m; i++) {
        pthread_join(info[i].tid, NULL);
        total += info[i].sum;
    }

    std::clock_t t2 = std::clock();

    std::cout << "Time spent with " << m << " threads: "
              << 1000.0 * (t2 - t1) / CLOCKS_PER_SEC << " ms\n";
    std::cout << total << "\n";

    //суммируемм
    t1 = std::clock();
    long simple = 0;

    for (int i = 0; i < n; i++) {
        simple += arr[i];
    }

    t2 = std::clock();

    std::cout << "Time spent without threads: "
              << 1000.0 * (t2 - t1) / CLOCKS_PER_SEC << " ms\n";
    std::cout << simple << "\n";

    delete[] arr;
    delete[] info;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "wrong args\n";
        return 1;
    }

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    sumArray(n, m);
    return 0;
}

