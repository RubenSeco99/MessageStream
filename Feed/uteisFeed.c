#include "uteisFeed.h";
int CommandHandlerUserKey(char *command){
    char *commands[]= {"topics","msg","subscribe","unsubscribe","exit"};
    int NumCommands = sizeof(commands) / sizeof(commands[0]);
    for(int i=0; i < NumCommands;i++)
        if(strcmp(commands[i],command) == 0)
            return (i+1);
    return 0;
}