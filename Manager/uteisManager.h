#ifndef UTEISMANAGER_H
#define UTEISMANAGER_H
#include "../fifo.h"
typedef struct {
    bool running;
    USER *users;
    TOPIC *topics;
    MESSAGE *msg;
    pthread_mutex_t *mutex;
}TDATA;
void fillUsers(USER users[]);
void fillMessages(MESSAGE messages[],char topicName);
void fillTopics(TOPIC topics[]);
void fillThreadsInfo(TDATA threads[],USER users[],TOPIC topics[],pthread_mutex_t *lock);
    // -- Comands -- //
int commandHandlerAdminKey(const char *command);
int commandHandlerAdmin(const char *firstArg, int numArgs);
void commandUsers(USER users[]);
void commandRemoveUser(USER users[],const char *userName);
void commandTopics(TOPIC topics[]);
void commandShowTopic(TOPIC topics[],const char *topicName);
void commandChangeTopicState(TOPIC topics[],const char *topicName,const char *newState);
void commandClose(TDATA td[]);
    // -- Server Request -- //

#endif //UTEISMANAGER_H
