#include "uteisManager.h"
void fillUsers(USER users[]) {
    for(int i=0;i<MAXUSERS;i++) {
        users[i].pid=-1;
        strcpy(users[i].name,"");
    }
}
void displayUsers(USER users[]) {
    for(int i=0;i<MAXUSERS;i++) {
        if(users[i].pid==-1) {
            printf("Pid: %i\n",users[i].pid);
            printf("Name: %s\n",users[i].name);
        }
    }
}
void fillMessages(MESSAGE messages[]) {
    for(int i=0;i<MAXMSGPERTOPIC;i++){
        messages[i].duration=-1;
        strcpy(messages[i].body,"\0");
        strcpy(messages[i].topicName,"\0");
    }
}
void fillTopics(TOPIC topics[]) {
    for(int i=0;i<MAXTOPICS;i++) {
        fillMessages(topics[i].mensagens);
        strcpy(topics[i].topicName,"\0");
        topics[i].state='u';
        topics[i].persistenceMessages=0;
    }
}
void fillThreadsInfo(TDATA threads[],USER users[],TOPIC topics[],pthread_mutex_t *lock) {
    for(int i=0;i<NTHREADSSERVER;i++) {
        threads[i].mutex=lock;
        threads[i].running=1;
        threads[i].users=users;
        threads[i].topics=topics;
    }
}
int commandHandlerAdminKey(const char *command){
    char *commands[]= {"users","remove","topics","show","lock","unlock","close"};
    int NumCommands = sizeof(commands) / sizeof(commands[0]);
    for(int i=0; i < NumCommands;i++)
        if(strcmp(commands[i],command) == 0)
            return (i+1);
    return 0;
}
int commandHandlerAdmin(const char *command) {
    char firstArg[20];
    char secondArg[20];
    firstArg[0]='\0';
    secondArg[0]='\0';
    int numArgs= snprintf(command,sizeof(command),"%s %s",firstArg,secondArg);
    if(commandHandlerAdminKey(firstArg)>0) {
        if(strcmp(firstArg,"users")==0 && numArgs==1){
            printf("Command users valid");
            return 1;
        }else if(strcmp(firstArg,"remove")==0 && numArgs==2) {
            printf("Command remove valid");
            return 2;
        }else if(strcmp(firstArg,"topics")==0 && numArgs==1) {
            printf("Command topics valid");
            return 3;
        }else if(strcmp(firstArg,"show")==0 && numArgs==2) {
            printf("Command show valid");
            return 4;
        }else if(strcmp(firstArg,"lock")==0 && numArgs==2) {
            printf("Command lock valid");
            return 5;
        }else if(strcmp(firstArg,"unlock")==0 && numArgs==2) {
            printf("Command unlock valid");
            return 6;
        }else if(strcmp(firstArg,"close")==0 && numArgs==1) {
            printf("Command close valid");
            return 7;
        }else {
            printf("Command not found\n");
            return 0;
        }
    }else {
        printf("command invalid\n");
        return 0;
    }

}