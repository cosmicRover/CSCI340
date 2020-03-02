#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

//a macro to help print text and var
#define print(e, f)                       \
    {                                     \
        std::cout << e << f << std::endl; \
    };

//returns time of day as microseconds
int getTimeOfDay()
{
    struct timeval current;
    gettimeofday(&current, NULL);
    // print("micro time: ", current.tv_usec);
    return current.tv_usec;
}

int main(int argc, char *argv[])
{
    std::string c = argv[1];
    std::string cmd = "/bin/" + c;
    print("command entered: ", cmd);

    char cmd_char[cmd.length()];
    for (int i = 0; i <= cmd.length(); i++)
    {
        cmd_char[i] = cmd[i];
    }

    int pipe1[2], pipe2[2];
    pid_t pid;
    char cmdOutput[4096];

    //create a pipe
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        printf("pipe had failed\n");
        return EXIT_FAILURE;
    }

    // print("pid start value ", getpid());

    int pStart = getTimeOfDay();
    print("parent start time in microseconds: ", pStart);

    //fork a child
    if ((pid = fork()) < 0)
    {
        perror("fork failed");
        return EXIT_FAILURE;
    }

    // print("current pid value ", pid);

    //excute code in the child process, dup2 duplciates file descriptor
    if (pid == 0)
    {
        // print("in child process ", getpid());

        //write timestamp to the write-end of pipe
        int cStart = getTimeOfDay();
        close(pipe2[0]);
        write(pipe2[1], &cStart, sizeof(cStart));
        close(pipe2[1]);

        //run execl() command and get the outputs on pipe
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[0]);
        close(pipe1[1]);
        execl(cmd_char, "", (char *)0);

        print("exiting child", "");
        exit(0);
    }

    //parent will now wait for child to complete
    // print("in parent process, waiting for child to end ", "");

    wait(NULL);

    //display the outputs from command
    int bytes = read(pipe1[0], cmdOutput, sizeof(cmdOutput));
    close(pipe1[0]);
    printf("command outputs are : \n%.*s", bytes, cmdOutput);

    //retrieve the passed value from the pipe and read it
    int passedVal;
    close(pipe2[1]);
    read(pipe2[0], &passedVal, sizeof(passedVal));
    close(pipe2[0]);
    print("child start time in microseconds: ", passedVal);

    //parent process is complete
    // printf("ended parent\n");

    int endTime = getTimeOfDay();
    print("parent end time in microseconds:: ", endTime);
    print("elapsed time: ", (double)(endTime - pStart) / 1000000);

    return 0;
}
