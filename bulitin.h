#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int CMD(char **parsed) {

    int NoOfCom = 4, i, ind = 0;
    char *Commands[NoOfCom];
    char *username;

    Commands[0] = "exit";
    Commands[1] = "cd";
    Commands[2] = "help";
    Commands[3] = "hello";

    for (i = 0; i < NoOfCom; i++) {
        if (strcmp(parsed[0], Commands[i]) == 0) {
            ind = i + 1;
            break;
        }
    }

    switch (ind) {
    case 1:
        printf("\n\tGoodbye 👋️\n");
        exit(0);
    case 2:
        chdir(parsed[1]);
        return 1;
    case 3:
        Help();
        return 1;
    case 4:
        username = getenv("USER");
        printf("\nHello🎼️🎙️  %s.\nSimple Linux Shell "
               "Use it when You loss the hope of your OS❌️⚠️."
               "\nUse help to know more..\n",
               username);
        return 1;
    default:
        break;
    }

    return 0;
}