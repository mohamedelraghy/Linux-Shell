#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>  
#include<string.h>

#define clear() printf("\033[H\033[J")

void init_shell();
int takeInput(char * );
int main(){

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