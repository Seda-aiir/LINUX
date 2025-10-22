#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>

int main(int argc, char** argv) {

    if (argc != 2) {
        std::perror("Wrong args");
        std::exit(EXIT_FAILURE);
    }

    //open
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        std::perror("Failure in opening file");
        std::exit(EXIT_FAILURE);
    }

    const int buffer_size = 4096;
    char read_buf[buffer_size];
    char write_buf[buffer_size];


    for (int i = 0; i < buffer_size; ++i) {
        write_buf[i] = '\0';
    }

    ssize_t bytes_read = read(fd, read_buf, buffer_size);
    ssize_t file_size = bytes_read;

    while (bytes_read > 0) {
        bytes_read = read(fd, read_buf, buffer_size);
        file_size += bytes_read;
    }

    lseek(fd, 0, SEEK_SET);

    //реврайт
    while (file_size > 0) {
        int chunk = (file_size < buffer_size) ? file_size : buffer_size;
        int bytes_written = write(fd, write_buf, chunk);
        file_size -= bytes_written;
    }

    close(fd);
    return 0;
}

