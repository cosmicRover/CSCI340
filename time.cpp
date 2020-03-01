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

long int getTimeOfDay(){
    struct timeval current;
    gettimeofday(&current, NULL);
    print("micro time: ", current.tv_usec);
    return current.tv_usec;
}

void executeCmd(std::string s)
{
    print("execute command ", s);
    return;
}

int main(int argc, char *argv[])
{
    std::string c = argv[1]; 
    std::string cmd = "/bin/"+c;
    print("command entered: ", cmd);

    char cmd_char[cmd.length()];
    for (int i = 0; i <= cmd.length(); i++)
    {
        cmd_char[i] = cmd[i];

    }

    //debug
    // print("cmd_char is: ", cmd_char);

    
    int pipe1[2], pipe2[2];
    pid_t pid;
    char cmdOutput[4096];

    //create a pipe
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        printf("pipe had failed\n");
        return EXIT_FAILURE;
    }

    print("pid start value ", getpid());

    //fork a child
    if((pid = fork()) < 0){
        perror("fork failed");
        return EXIT_FAILURE;
    }

    print("current pid value ", pid);

    //excute code in the child process, dup2 duplciates file descriptor
    if (pid == 0){
        print("in child process ", getpid());
        
        //run execl() command and get the outputs
        int cStart = getTimeOfDay();
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[0]);
        close(pipe1[1]);
        execl(cmd_char, "", (char *)0);

        printf("exiting child\n");
        exit(0);
    }

    //write timestamp to write end of pipe
    int pStart = getTimeOfDay();
    close(pipe2[0]); //close read end
    write(pipe2[1], &pStart, sizeof(pStart));
    close(pipe2[1]);

    //parent will now wait for child to complete
    print("in parent process, waiting for child to end ", "");
    wait(NULL);

    int bytes = read(pipe1[0], cmdOutput, sizeof(cmdOutput));
    printf("command outputs are : \n%.*s", bytes, cmdOutput);
    wait(NULL);

    //retrieve the passed value from the pipe and read it
    int passedVal;
    close(pipe2[1]);
    read(pipe2[0], &passedVal, sizeof(passedVal));
    close(pipe2[0]);
    print("passed time --->> ", passedVal);

    //parent process is complete
    printf("ended parent\n");

    int endTime = getTimeOfDay();
    print("elapsed time: ", (double)(endTime - passedVal) / 1000000);

    return 0;
}
