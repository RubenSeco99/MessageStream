#ifndef UTEISFEED_H
#define UTEISFEED_H
#include "../fifo.h"
typedef struct {
    bool running;
    int fd;
    pthread_mutex_t *mutex;
}TDATAUSER;

int CommandHandlerUserKey(const char *command);

int commandHandlerUser(const char *firstArg,const int numArgs);

#endif //UTEISFEED_H
