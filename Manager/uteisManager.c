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
int CommandHandlerAdmin(const char *command){
    char *commands[]= {"users","remove","topics","show","lock","unlock","close"};
    int NumCommands = sizeof(commands) / sizeof(commands[0]);
    for(int i=0; i < NumCommands;i++)
        if(strcmp(commands[i],command) == 0)
            return (i+1);
    return 0;
}