#include <stdio.h>
#include <stdlib.h> // for getenv function
#include <unistd.h> // for sleep 
#include <string.h> // for string processing.
#include <readline/readline.h>
#include <readline/history.h>

#define clear() printf("\033[H\033[J")

void init_shell() {
    clear();
    printf("\n\n\n\n******************"
           "************************");
    printf("\n\n\n\t****Simple Shell****");
    printf("\n\n\t-USE AT EMERGENCIES ⛑️-");
    printf("\n\n\n\n*******************"
           "***********************");
    char *username = getenv("USER");
    printf("\n\n\nWelcom: %s😀️", username);
    printf("\n");
    sleep(2);
    clear();
}

void Help() {

    puts("\n***WELCOME TO MY SHELL HELP***"
         
         "\nList of Commands supported:"
         "\n>cd"
         "\n>ls"
         "\n>exit"
         "\n>all other general commands available in UNIX shell"
         
         "\n\n\tMade with ❤️ at FCI");

    return;
}

void pwd()
{
    char pwd[1024];
    getcwd(pwd, sizeof(pwd));
    char *username = getenv("USER");
    printf("\n%s:~%s", username, pwd);
}

int takeInput(char *str)
{
    char *buf;
    buf = readline("$ ");
    if (strlen(buf) != 0)
    {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    }
    else
        return 1;
}