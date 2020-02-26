#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    std::string cmd = argv[1];
    std::cout << "command name: " << cmd << std::endl;

    int pipe1[2];
    pid_t pid;

    //create a pipe
    if (pipe(pipe1))
    {
        printf("pipe had failed");
        return EXIT_FAILURE;
    }

    //fork a child process, use switch case with rang low ... high
    pid = fork();

    if (pid == (pid_t)0)
    {
        /* This is the child process.
          Close other end first. */
        printf("fork successful \n");
        close(pipe1[1]);
        // read_from_pipe(mypipe[0]);

        return EXIT_SUCCESS;
    }
    else if (pid < (pid_t)0)
    {
        /* The fork failed. */
        fprintf(stderr, "Fork failed.\n");
        return EXIT_FAILURE;
    }
    else
    {
        /* This is the parent process.
          Close other end first. */
        close(pipe1[0]);
        // write_to_pipe(mypipe[1]);
        return EXIT_SUCCESS;
    }

    return 0;
}
