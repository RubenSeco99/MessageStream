#include "manager.h"
void *processClientsRequests(void* pdata) {//unica instância
    TDATA *ptd = (TDATA *) pdata;
    COMUNICACAO p,r;
    int nbytes,fd_cliente;
    while(ptd->running) {
        read(ptd->fd,&p,sizeof(p));
        printf("\nRecebi commando: %s   \n",p.command);
        strcpy(p.message,"Commando enviado com sucesso");
        fd_cliente=open(p.fd_user,O_WRONLY);
        if(fd_cliente==-1) {
            printf("Erro ao abrir o cliente");
            continue;
        }
        write(fd_cliente,&p,sizeof(p));
        close(fd_cliente);
    }
    return 0;
}

void *processMessageTimes(void* pdata) {
    //TDATA *ptd = (TDATA *) pdata;//cast because the thread receive generic pointer
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
    int fd=open(SRV_FIFO, O_RDWR);//rdwr evita deadlocks
    if(fd==-1) {
        printf("[ERRO] Erro ao abrir o pipe para escrita\n");
        return 2;
    }
    USER users[MAXUSERS];
    TOPIC topics[MAXTOPICS];
    fillTopics(topics);
    fillUsers(users);
    pthread_mutex_t lock;

    pthread_t tid[NTHREADSSERVER];//Guarda o id das threads para depois fazer o create e o join
    pthread_mutex_init(&lock,NULL);

    TDATA td[NTHREADSSERVER];
    fillThreadsInfo(td,users,topics,&lock,fd);
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
        int numArgs= sscanf(command,"%19s %19s %99s",firstArg,secondArg,thirdArg);
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

    close(fd);
    printf("\nManager going off");
    pthread_mutex_destroy(&lock);
    unlink(SRV_FIFO);
    return 0;
}
