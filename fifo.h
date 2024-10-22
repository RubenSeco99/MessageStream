#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
//fifo
#include <sys/stat.h>
#include <fcntl.h>
//read, write, close
#include <unistd.h>
//thread handling
#include <pthread.h>

#ifndef FIFO_H
#define FIFO_H
#define SRV_FIFO "server_fifo"
#define MAXUSERS 10
#define MAXTOPICS 10
#define MAXMSGPERTOPIC 10
#define NTHREADSSERVER 2
#define NTHREADSCLIENTS 1
typedef struct {
    char topicName[20];
    char body[300];
    int duration;
}MESSAGE;
typedef struct {
    char topicName[20];
    int persistenceMessages;
    char state;//block/unblock
    MESSAGE mensagens[5];//adicionar mensagnes nao persistentes e estas sao persistentes
}TOPIC;
typedef struct {
    char name[100];
    int pid;
    TOPIC topics[20];
}USER;
#endif //FIFO_H
