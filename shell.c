#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>  
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define clear() printf("\033[H\033[J")

void init_shell();
int takeInput(char * );
void pwd();
void execArgs(char **);
void execArgsPiped(char **, char **);
void openHelp();

int main()
{
}

void init_shell(){
    clear();
    printf("\n\n\n\n******************"
           "************************");
    printf("\n\n\n\t****MY SHELL****");
    printf("\n\n\t-USE AT YOUR OWN RISK-");
    printf("\n\n\n\n*******************"
           "***********************");
    char *username = getenv("USER");
    printf("\n\n\nUSER is: @%s", username);
    printf("\n");
    sleep(1);
    clear();
}

int takeInput(char *str){
    char *buf;
    buf = readline("\n>>> ");
    if(strlen(buf) != 0) {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    } else return 1;
}

void pwd(){
    char pwd[1024];
    getcwd(pwd, sizeof(pwd));
    printf("\nDir: %s", pwd);
}

void execArgs(char **parsed){
    pid_t pid = fork();
    
    if(pid == -1){
        printf("\nFailed forking child...");
        return;
    }else if (pid == 0){
        if(execvp(parsed[0], parsed) < 0) printf("\n Could not execute command...");
        exit(0);
    }else {
        wait(NULL);
        return;
    }
}

void execArgsPiped(char **parsed, char **parsedpipe){

    int fd[2]; // file descriptor 0 for read 1 for write
    pid_t p1, p2;

    if (pipe(fd) < 0){
        printf("\nPipe could not be initialized");
        return;
    }
    p1 = fork();
    if (p1 < 0){
        printf("\nCould not fork");
        return;
    }

    if (p1 == 0){
        // Child 1 executing..
        // It only needs to write at the write end
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        if (execvp(parsed[0], parsed) < 0){
            printf("\nCould not execute command 1..");
            exit(0);
        }
    }
    else{
        // Parent executing
        p2 = fork();

        if (p2 < 0) {
            printf("\nCould not fork");
            return;
        }

        // Child 2 executing..
        // It only needs to read at the read end
        if (p2 == 0){
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            if (execvp(parsedpipe[0], parsedpipe) < 0) {
                printf("\nCould not execute command 2..");
                exit(0);
            }
        }
        else{
            wait(NULL);
            wait(NULL);
        }
    }
}

void openHelp(){
    puts("\n***WELCOME TO MY SHELL HELP***"
         "\nCopyright @ Suprotik Dey"
         "\n-Use the shell at your own risk..."
         "\nList of Commands supported:"
         "\n>cd"
         "\n>ls"
         "\n>exit"
         "\n>all other general commands available in UNIX shell"
         "\n>pipe handling"
         "\n>improper space handling");

    return;
}

