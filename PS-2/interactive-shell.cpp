#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <sys/wait.h>
#include <regex>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

std::vector<std::string> split(const std::string& line, char delim) {
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, delim)) {
        if (!item.empty()) {
            parts.push_back(item);
        }
    }

    return parts;
}

std::vector<std::string> split_by_str(const std::string& text, const std::string& delim) {
    std::vector<std::string> parts;
    size_t pos = text.find(delim);

    if (pos == std::string::npos) {
        parts.push_back(text);
    } else {
        parts.push_back(text.substr(0, pos));
        parts.push_back(text.substr(pos + delim.size()));
    }

    return parts;
}

int run(const std::string& command, int output_fd = 1, bool silent = false) {
    int pid = fork();

    if (pid == 0) { // child
       
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));

        std::string old_path = getenv("PATH") ? getenv("PATH") : "";
        std::string new_path = std::string(cwd) + ":" + old_path;
        setenv("PATH", new_path.c_str(), 1);

        if (silent) {
            std::string log_file = std::to_string(getpid()) + ".log";
            int fd = open(log_file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (fd == -1) {
                std::cerr << "Error: cannot open log file\n";
                exit(EXIT_FAILURE);
            }

            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            close(fd);
        }
        else if (output_fd != 1) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        std::vector<std::string> args = split(command, ' ');
        std::vector<char*> argv;
        for (const auto& arg : args) {
            argv.push_back(const_cast<char*>(arg.c_str()));
        }
        argv.push_back(nullptr);

        execvp(argv[0], argv.data());

        std::cerr << "Failed to execute: " << command << std::endl;
        exit(EXIT_FAILURE);
    }
    else if (pid > 0) { // parent
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            std::cerr << "Waitpid error on " << command << std::endl;
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
    }
    else {
        std::cerr << "Fork failed for " << command << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}

int process_command(std::string cmd) {
    if (cmd.rfind("silent ", 0) == 0) {
        cmd = cmd.substr(7);
        return run(cmd, 1, true);
    }

    if (cmd.find("&&") != std::string::npos) {
        auto parts = split_by_str(cmd, " && ");
        if (process_command(parts[0]) == 0)
            process_command(parts[1]);
    }
    else if (cmd.find("||") != std::string::npos) {
        auto parts = split_by_str(cmd, " || ");
        if (process_command(parts[0]) != 0)
            process_command(parts[1]);
    }
    else if (cmd.find(';') != std::string::npos) {
        auto parts = split_by_str(cmd, "; ");
        process_command(parts[0]);
        process_command(parts[1]);
    }
    else if (cmd.find(">>") != std::string::npos) {
        auto parts = split_by_str(cmd, " >> ");
        int fd = open(parts[1].c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1) {
            std::cerr << "Error: cannot open file for append\n";
            exit(EXIT_FAILURE);
        }
        run(parts[0], fd);
        close(fd);
    }
    else if (cmd.find('>') != std::string::npos) {
        auto parts = split_by_str(cmd, " > ");
        int fd = open(parts[1].c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            std::cerr << "Error: cannot open file for write\n";
            exit(EXIT_FAILURE);
        }
        run(parts[0], fd);
        close(fd);
    }
    else {
        return run(cmd);
    }

    return 0;
}

int main() {
    std::string input;

    std::cout << "> ";
    while (std::getline(std::cin, input)) {
        if (input == "exit")
            break;

        if (input.empty()) {
            std::cout << "> ";
            continue;
        }

        process_command(input);

        std::cout << "> ";
    }

    return 0;
}
