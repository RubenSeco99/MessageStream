#include "uteisManager.h"
void fillUsers(USER users[]) {
    for(int i=0;i<MAXUSERS;i++) {
        users[i].pid=-1;
        strcpy(users[i].name,"");
        fillTopics(users[i].topics);
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
        fillMessages(topics[i].mensagens);
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
int commandHandlerAdmin(const char *firstArg,const int numArgs) {
    const int key=commandHandlerAdminKey(firstArg);
    if(key>0) {
        if(numArgs==1 && (key==1 || key==3 ||key==7)){
            printf("Command %s valid!\n",firstArg);
            return key;
        }
        if(numArgs==2 && (key==2 || key==4 || key==5 || key==6)) {
            printf("Command %s valid!\n",firstArg);
            return key;
        }
            printf("Command invalid\n");
            return 0;
    }
        printf("command invalid\n");
        return 0;
}
void commandUsers(USER users[]){
    for(int i=0;i<MAXUSERS;i++) {
        if(users[i].pid==-1) {
            printf("Pid: %i\n",users[i].pid);
            printf("Name: %s\n",users[i].name);
        }
    }
}
void commandRemove(USER users[],char *userName) {//todo
    for(int i=0;i<MAXUSERS;i++) {
        if(strcmp(users[i].name,userName)==0) {
            users[i].pid=-1;
            strcpy(users[i].name,"");
            for(int j=0;j<MAXTOPICS;j++) {
                strcpy(users[i].topics[j].topicName,"");
            }
        }
    }
}