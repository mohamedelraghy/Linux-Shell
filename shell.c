#include<stdio.h>
#include "in-out.h"
#include "parse.h"
#include "exec.h"

#define MAXCOM 1000 
#define MAXLIST 100 

int main() {
    
    char inputString[MAXCOM], *parsedArgs[MAXLIST];
    char *parsedArgsPiped[MAXLIST];
    int execFlag = 0;

    init_shell();

    while (1) {
        pwd();
        
        if (takeInput(inputString)) continue;
        
        execFlag = processString(inputString, parsedArgs, parsedArgsPiped);
           
        // processString returns zero if there is no command
        // or it is a builtin command,
        // 1 if it is a simple command
        // 2 if it is including a pipe.

        if (execFlag == 1) execArgs(parsedArgs);
        
        if (execFlag == 2) execArgsPiped(parsedArgs, parsedArgsPiped);
    }

    return 0;
}
