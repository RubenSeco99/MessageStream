#include "manager.h"
void *processClientsRequests(void* pdata) {
    sleep(1);
    printf("Processing requests\n");
}

void *processMessageTimes(void* pdata) {
    sleep(2);
    printf("Processing message times\n");
}

int main(int argc, char** argv, char** envp) {
    char *msg_fich = getenv("MSG_FICH");
    if (access(SRV_FIFO, F_OK) == 0) {
        printf("[ERRO] Ja existe um manager em funcionamento\n");
        return 1;
    }
    mkfifo(SRV_FIFO, 0640);

    USER users[10];
    TOPIC topics[10];
    fillUsers(users);
    fillTopics(topics);
    pthread_mutex_t lock;

    pthread_t tid[NTHREADSSERVER];//Guarda o id das threads para depois fazer o create e o join
    pthread_mutex_init(&lock,NULL);

    printf("Main\n");
    TDATA td[NTHREADSSERVER];
    fillThreadsInfo(tid,users,topics,&lock);
    pthread_create(&tid[0],NULL,processClientsRequests,&td[0]);
    pthread_create(&tid[1],NULL,processMessageTimes,&td[1]);

    char command[20];
    while (true) {

        printf("Insert command");
        scanf("%s",command);
        int key=commandHandlerAdmin(command);
        printf("%d",key);
        if(key==7) {
            break;
        }
    }
    printf("bye bye");
    for(int i=0; i<NTHREADSSERVER; i++){
        pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&lock);
    unlink(SRV_FIFO);
    return 0;
}
