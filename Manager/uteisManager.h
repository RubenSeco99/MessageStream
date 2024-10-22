#ifndef UTEISMANAGER_H
#define UTEISMANAGER_H
#include "../fifo.h"
typedef struct {
    int running;
    USER *users;
    TOPIC *topics;
    MESSAGE *msg;
    pthread_mutex_t *mutex;
}TDATA;
void fillUsers(USER users[]);
void displayUsers(USER users[]);
void fillMessages(MESSAGE messages[]);
void fillTopics(TOPIC topics[]);
void fillThreadsInfo(TDATA threads[],USER users[],TOPIC topics[],pthread_mutex_t *lock);
int commandHandlerAdmin(const char *command);

#endif //UTEISMANAGER_H
