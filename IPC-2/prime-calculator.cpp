#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>

#define BUFSIZE 100

bool isPrime(int x) {
    if (x < 2) return false;
    if (x == 2 || x == 3) return true;
    if (x % 2 == 0 || x % 3 == 0) return false;

    for (int i = 5; i * i <= x; i += 6) {
        if (x % i == 0 || x % (i + 2) == 0)
            return false;
    }
    return true;
}

void generateMore(std::vector<int> &list, int need) {
    int start = list.back() + 1;
    while ((int)list.size() < need) {
        if (isPrime(start)) {
            list.push_back(start);
        }
        start++;
    }
}

int main() {

    int parentToChild[2];
    int childToParent[2];

    if (pipe(parentToChild) < 0 || pipe(childToParent) < 0) {
        std::cerr << "Pipe creation error\n";
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork error\n";
        return 1;
    }

    //child
    if (pid == 0) {

        close(parentToChild[1]);
        close(childToParent[0]);

        std::vector<int> primes;
        primes.push_back(2);
        primes.push_back(3);
        primes.push_back(5);
        primes.push_back(7);

        char buffer[BUFSIZE];

        while (true) {

            int r = read(parentToChild[0], buffer, BUFSIZE);
            if (r <= 0) {
                break;
            }

            buffer[r] = '\0';

            int n = std::atoi(buffer);

            std::cout << "[Child] Calculating " << n << "-th prime number..." << std::endl;

            if (n > (int)primes.size()) {
                generateMore(primes, n);
            }

            std::cout << "[Child] Sending calculation result of prime(" << n << ")..." << std::endl;

            std::string out = std::to_string(primes[n - 1]);
            write(childToParent[1], out.c_str(), out.size());
        }

        close(parentToChild[0]);
        close(childToParent[1]);
        return 0;
    }

    // paren t
    else {

        close(parentToChild[0]);
        close(childToParent[1]);

        while (true) {

            std::string txt;
            std::cout << "[Parent] Please enter the number: ";
            std::cin >> txt;

            if (txt == "exit") {
                close(parentToChild[1]);
                close(childToParent[0]);
                wait(NULL);
                break;
            }

            int number = std::atoi(txt.c_str());
            if (number <= 0) {
                std::cout << "Invalid num" << std::endl;
                continue;
            }

            std::cout << "[Parent] Sending " << txt << " to the child process..." << std::endl;
            std::cout << "[Parent] Waiting for the response from the child process..." << std::endl;

            write(parentToChild[1], txt.c_str(), txt.size());

            char answer[BUFSIZE];
            int s = read(childToParent[0], answer, BUFSIZE);

            if (s > 0) {
                answer[s] = '\0';
                int result = std::atoi(answer);
                std::cout << "[Parent] Received calculation result of prime(" 
                          << txt << ") = " << result << "..." << std::endl << std::endl;
            }
        }
    }

    return 0;
}

