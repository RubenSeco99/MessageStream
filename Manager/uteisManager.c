#include "uteisManager.h"
void fillUsers(USER users[]) {
    for(int i=0;i<MAXUSERS;i++) {
        users[i].pid=-1;
        strcpy(users[i].name,"");
        for(int j=0;j<MAXTOPICS;j++)
            users[i].topics[j]=NULL;

    }
}
void fillMessages(MESSAGE messages[],char topicName) {
    for(int i=0;i<MAXMSGPERTOPIC;i++){
        messages[i].duration=-1;
        strcpy(messages[i].body,"\0");
        strcpy(messages[i].topicName,"\0");
    }
}
void fillTopics(TOPIC topics[]) {
    for(int i=0;i<MAXTOPICS;i++) {
        strcpy(topics[i].topicName,"\0");
        fillMessages(topics[i].persistentMessages,topics[i].topicName);
        topics[i].state='u';
        topics[i].nPersistMessages=0;
    }
}
void fillThreadsInfo(TDATA threads[],USER users[],TOPIC topics[],pthread_mutex_t *lock) {
    for(int i=0;i<NTHREADSSERVER;i++) {
        threads[i].mutex=lock;
        threads[i].running=true;
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
void commandRemoveUser(USER users[],const char *userName) {//todo
    for(int i=0;i<MAXUSERS;i++) {
        if(strcmp(users[i].name,userName)==0) {
            users[i].pid=-1;
            strcpy(users[i].name,"");
            for(int j=0;j<MAXTOPICS;j++) {
                users[i].topics[j]=NULL;
            }
        }
    }
}
void commandTopics(TOPIC topics[]) {
    printf("Topicos:\n");
    for(int i=0;i<MAXTOPICS;i++)
        printf("%s com %d mensagens persistentes\n",topics[i].topicName,topics[i].nPersistMessages);
}
void commandShowTopic(TOPIC topics[],const char *topicName) {
    for(int i=0;i<MAXTOPICS;i++)
        if(strcmp(topics[i].topicName,topicName)==0)
            for(int j=0;j<topics[i].nPersistMessages;j++)
                printf("Mensagem [%d]: %s",j,topics[i].persistentMessages[j].body);
}
void commandChangeTopicState(TOPIC topics[],const char *topicName,const char *newState) {
    for(int i=0;i<MAXTOPICS;i++)
        if(strcmp(topics[i].topicName,topicName)==0){
            if(newState[0]==topics[i].state)
                printf("Topic %s already %s\n", topicName, topics[i].state=='u' ? "unblocked" : "blocked");
            else if(strcmp(newState,"u")==0)
                topics[i].state='u';
            else if(strcmp(newState,"b")==0)
                topics[i].state='b';
            return;
        }
}
void commandClose(TDATA td[]){
    for(int i=0;i<NTHREADSSERVER;i++)
        if(td[i].running)
            td[i].running=false;
    printf("Closing...\n");
}

