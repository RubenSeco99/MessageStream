#include "uteisFeed.h"

int CommandHandlerUserKey(const char *command){
    char *commands[]= {"topics","msg","subscribe","unsubscribe","exit"};
    int NumCommands = sizeof(commands) / sizeof(commands[0]);
    for(int i=0; i < NumCommands;i++)
        if(strcmp(commands[i],command) == 0)
            return (i+1);
    return 0;
}

int commandHandlerUser(const char *firstArg,const int numArgs) {
    const int key=CommandHandlerUserKey(firstArg);
    if(key>0) {
        if(numArgs==1 && (key==1 || key==5)){
            printf("Command %s valid!\n",firstArg);
            return key;
        }
        if(numArgs==2 && (key==3 || key==4)) {
            printf("Command %s valid!\n",firstArg);
            return key;
        }if(numArgs==4 && (key==2)) {
            printf("Command %s valid!\n",firstArg);
            return key;
        }
        printf("Command invalid\n");
        return 0;
    }
    printf("command invalid\n");
    return 0;
}