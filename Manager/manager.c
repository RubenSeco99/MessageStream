#include "manager.h"
void *processClientsRequests(void* pdata) {
    sleep(1);
   // printf("Processing requests\n");Comand
    return 0;
}

void *processMessageTimes(void* pdata) {
    TDATA *ptd = (TDATA *) pdata;//cast because the thread receive generic pointer
    sleep(2);
 //   printf("Processing message times\n");
    return 0;
}

int main(int argc, char** argv, char** envp) {
    char *msg_fich = getenv("MSG_FICH");
    if (access(SRV_FIFO, F_OK) == 0) {
        printf("[ERRO] Ja existe um manager em funcionamento\n");
        return 1;
    }
    mkfifo(SRV_FIFO, 0640);

    USER users[MAXUSERS];
    TOPIC topics[MAXTOPICS];
    fillTopics(topics);
    fillUsers(users);
    pthread_mutex_t lock;

    pthread_t tid[NTHREADSSERVER];//Guarda o id das threads para depois fazer o create e o join
    pthread_mutex_init(&lock,NULL);

    printf("Main\n");
    TDATA td[NTHREADSSERVER];
    fillThreadsInfo(td,users,topics,&lock);
    pthread_create(&tid[0],NULL,processClientsRequests,&td[0]);
    pthread_create(&tid[1],NULL,processMessageTimes,&td[1]);

    char firstArg[20];
    char secondArg[20];
    char thirdArg[20];
    char command[60];
    while (true) {
        printf("Insert command: ");
        if (fgets(command, sizeof(command), stdin) == NULL)
            continue;
        command[strcspn(command, "\n")] = '\0';
        firstArg[0]='\0';
        secondArg[0]='\0';
        thirdArg[0]='\0';
        int numArgs= sscanf(command,"%19s %19s [%99]s",firstArg,secondArg,thirdArg);
        printf("%s\n",firstArg);
        printf("numArgs:%d\n",numArgs);
        int key=commandHandlerAdmin(firstArg,numArgs);
        fflush(stdin);
        if(key==7 && numArgs==1) {
            break;
        }
    }
    for(int i=0;i<NTHREADSSERVER;i++)
        td[i].running=false;
    for(int i=0; i<NTHREADSSERVER; i++)
        pthread_join(tid[i],NULL);
    printf("\nManager going off");
    pthread_mutex_destroy(&lock);
    unlink(SRV_FIFO);
    return 0;
}
