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
#define MAXTOPICS 20
#define MAXMSGPERTOPIC 15
#define NTHREADSSERVER 2
#define NTHREADSCLIENTS 1
typedef struct {
    char topicName[20];
    char body[300];
    int duration;
}MESSAGE;
typedef struct {
    char topicName[20];
    int nPersistMessages;
    char state;//block/unblock (b/u)
    MESSAGE persistentMessages[MAXMSGPERTOPIC];
    MESSAGE temporaryMessages[MAXUSERS];//existe tantas mensagens temporarias como users,
    //assumindo que as verificações demoram um segundo cada user so tem tempo de enviar uma mensagem
}TOPIC;
typedef struct {
    char name[100];
    int pid;
    TOPIC *topics[MAXTOPICS];
}USER;
typedef struct {
    USER user;
    char message[20];
    MESSAGE persistentMessages[MAXUSERS];
    char command[20];
    char fd_user[20];
}COMUNICACAO;
#endif //FIFO_H
