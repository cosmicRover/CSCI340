#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//a macro to help print text and var
#define print(e, f)                       \
    {                                     \
        std::cout << e << f << std::endl; \
    };

void executeCmd(std::string s)
{
    print("execute command ", s);
    return;
}

int main(int argc, char *argv[])
{
    std::string c = argv[1]; 
    std::string cmd = "/bin/" + c ;
    print("command entered: ", cmd);

    // char cmd_char[cmd.length() + 1];
    // for (size_t i = 0; i < cmd.length(); i++)
    // {
    //     cmd_char[i] = cmd[i];
    // }
    

    int pipes[2];
    pid_t pid;
    char cmdOutput[4096];

    //create a pipe
    if (pipe(pipes) == -1)
    {
        printf("pipe had failed\n");
        return EXIT_FAILURE;
    }

    //fork a child
    if ((pid = fork()) == -1)
    {
        print("fork had failed", "")
    }

    //check for child/parent process. Read on 0 and print on else
    if (pid == 0)
    {
        print("child process was created ", getppid());
        dup2(pipes[1], STDOUT_FILENO);
        close(pipes[0]);
        close(pipes[1]);
        execl("/bin/ls", (char *)0);
    }
    else
    {
        print("parent process ", getpid());
        close(pipes[1]);
        int bytes = read(pipes[0], cmdOutput, sizeof(cmdOutput));
        printf("outputs are --> (%.*s)\n", bytes, cmdOutput);
        wait(NULL);
    }

    return 0;
}
