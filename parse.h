#include <stdio.h>
#include <string.h>
#include "bulitin.h"

#define MAXLIST 100

int parsePipe(char *str, char **strpiped) {
    
    for (int i = 0; i < 2; i++) {

        strpiped[i] = strsep(&str, "|");
        if (strpiped[i] == NULL) break;
    }

    if (strpiped[1] == NULL) return 0;
    else return 1;
}

void parseSpace(char *str, char **parsed) {

    for (int i = 0; i < MAXLIST; i++) {
        parsed[i] = strsep(&str, " ");

        if (parsed[i] == NULL) break;
        if (strlen(parsed[i]) == 0) i--; // grundeted that parsed[i] != Empty string
    }
}
int processString(char *str, char **parsed, char **parsedpipe) {

    char *strpiped[2];
    int piped = 0;

    piped = parsePipe(str, strpiped);

    if (piped) {
        parseSpace(strpiped[0], parsed);
        parseSpace(strpiped[1], parsedpipe);
    
    } else {

        parseSpace(str, parsed);
    }

    if (CMD(parsed)) return 0;
    else return 1 + piped;
}