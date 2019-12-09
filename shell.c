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


int main() {
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