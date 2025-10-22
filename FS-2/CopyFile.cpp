#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Wrong arguments, try again";
        exit(EXIT_FAILURE);
    }

    //destination
    int fd2 = open(argv[2], O_WRONLY | O_CREAT, 0664);
    if (fd2 == -1) {
        std::cerr << "Failure in opening destination fil";
        exit(EXIT_FAILURE);
    }

    //source
    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        std::cerr << "Failure in opening source file";
        close(fd2);
        exit(EXIT_FAILURE);
    }

    const int size = 4096;
    char bf[size];

    //copy
    ssize_t read_b;
    while ((read_b = read(fd1, bf, size)) > 0) {
        write(fd2, bf, read_b);
    }

    close(fd1);
    close(fd2);
    return 0;
}

