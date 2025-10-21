#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Need a file path\n";
        return EXIT_FAILURE;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        std::cerr << "Can't open file\n";
        return EXIT_FAILURE;
    }
    int size = 4096;	
    char bf[size];
    ssize_t n_read = read(fd, bf, size);

    while (n_read  > 0) {
        std::cout.write(bf, n_read);
        n_read = read(fd, bf, size);
    }

    close(fd);
    return 0;
}

