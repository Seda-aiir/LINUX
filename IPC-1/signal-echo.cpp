#include <iostream>
#include <signal.h>
#include <pwd.h>
#include <unistd.h>

void handler_usr1(int sig, siginfo_t* info, void* context) {
    ucontext_t *uc = (ucontext_t*)context;

    unsigned long rip_val = uc->uc_mcontext.gregs[REG_RIP];
    unsigned long rax_val = uc->uc_mcontext.gregs[REG_RAX];
    unsigned long rbx_val = uc->uc_mcontext.gregs[REG_RBX];

    struct passwd *user_info = getpwuid(info->si_uid);
    const char* username = user_info ? user_info->pw_name : "unknown";

    std::string output = "Received SIGUSR1 from process [" + std::to_string(info->si_pid) + "] by user ["
                         + std::to_string(info->si_uid) + "] (" + username + ").\n";

    output += "Context registers: RIP = [" + std::to_string(rip_val) + "], RAX = [" 
              + std::to_string(rax_val) + "], RBX = [" + std::to_string(rbx_val) + "].\n";

    write(1, output.c_str(), output.size());
}

int main() {
    struct sigaction sa {};
    sa.sa_sigaction = handler_usr1;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGUSR1, &sa, nullptr);

    raise(SIGUSR1);

    while (true) { sleep(10); }

    return 0;
}

