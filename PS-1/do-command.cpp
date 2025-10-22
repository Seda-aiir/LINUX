#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <sys/wait.h>



void do_command(char** argv) 
{
     std::clock_t start = std::clock();

    pid_t pid  = fork(); 
    if (pid == -1 ) 
    { 
        std::cerr << "fork failed\n"; 
        exit( EXIT_FAILURE); 
    }

    if (pid ==0)
    {
        int res = execvp(argv[1], &argv[1]);  
        if (res == -1) 
        { 
            std::cerr << "execvp failed\n"; 
            exit(EXIT_FAILURE); 
        }
    } 
    else
    { 
        int status;
        waitpid(pid, &status, 0);  

        std::clock_t end = std::clock();
        double duration = 1000.0 * (end - start) / CLOCKS_PER_SEC; 

        std::cout << "Command completed with " << status << " exit code and took " 
                  << duration << " seconds" << std::endl; 
    }
}

int main(int argc, char** argv)
{
    if(argc < 2) 
    { 
        std::cerr << "Wrong args, please try agan\n"; 
        exit(EXIT_FAILURE); 
    }

    do_command(argv);  

    return 0;
}

