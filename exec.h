#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void execArgs(char **parsed) {
    pid_t pid = fork();

    if (pid < 0) {
        printf("\nFailed forking child...");
        return;
    }

    else if (pid == 0) {
        if (execvp(parsed[0], parsed) < 0)
            printf("\n Could not execute command...");
        exit(0);
    
    } else {
        wait(NULL);
        return;
    }
}

void execArgsPiped(char **parsed, char **parsedpipe) {

    int fd[2]; // file descriptor 0 for read 1 for write
    pid_t p1, p2;

    if (pipe(fd) < 0) {
        printf("\nPipe could not be initialized");
        return;
    }

    p1 = fork();

    if (p1 <  0) {
        printf("\nCould not fork1");
        return;
    }

    if (p1 == 0) {
        printf("\nin chlid 1");
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        if (execvp(parsed[0], parsed) < 0) {
            printf("\nCould not execute command 1..");
            exit(0);
        }
    }
    else {
        p2 = fork();
        if (p2 < 0) {
            printf("\nCould not fork2");
            return;
        }

        
        if (p2 == 0) {
            printf("in child 2");
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            if (execvp(parsedpipe[0], parsedpipe) < 0) {
                printf("\nCould not execute command 2..");
                exit(0);
            }
       
        } else {
            wait(NULL);
            wait(NULL);
        }
    }
}