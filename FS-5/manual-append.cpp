#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


void proverka(bool arg) 
{
    if (arg  )  {
        std::cerr << "Wrong args, try agan";
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char** argv)
{
    proverka(argc != 2);  

    int fd = open(argv[1], O_WRONLY | O_CREAT, 0664);
    proverka(fd == -1);  

    char str[]  = "first line\n";

    int fd2 = dup(fd);
    proverka(fd2 == -1);  

    write(fd, str, 12);

      char str2[] = "second line";
    write(fd2, str2, 11); // или strlen(str) ? 

    close(fd2 );
    close(fd);

    return 0; 
}

