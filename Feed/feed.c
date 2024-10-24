#include "feed.h"
void *processServerResponses(void* pdata) {
    TDATAUSER *ptd = (TDATAUSER *) pdata;
    COMUNICACAO p;
    int fd_manager;
    while(ptd->running){
        read(ptd->fd,&p,sizeof(p));
        printf("Server response: %s\n",p.message);
        fd_manager=open(p.fd_user,O_WRONLY);
        if(fd_manager==-1) {
            printf("Erro ao abrir o manager");
            continue;
        }
    }
    sleep(1);
    printf("Processing server responses\n");
    return 0;
}
int main(int argc, char**argv, char **envp){
    if(access(SRV_FIFO,F_OK) != 0){
        printf("Server is Resting! \n");
        exit(1);
    }
    //posso criar a estrutura pedido e resposta e preencher as variaveis na funcao login
    COMUNICACAO p,r;
    char nomeFifo[20];
    if(!verificaLogin(&p,&r,nomeFifo)) {
        unlink(nomeFifo);
        exit(2);
    }

    pthread_mutex_t lock;
    pthread_t tid[NTHREADSCLIENTS];//Guarda o id das threads para depois fazer o create e o join
    pthread_mutex_init(&lock,NULL);
    pthread_create(&tid[0],NULL,processServerResponses,nomeFifo);
    //que info é preciso para a thread uma vez que ela so vai imprimir coisas no ecra??
    char command[60];
    while (true) {
        printf("Insert command: ");
        if (fgets(command, sizeof(command), stdin) == NULL)
            continue;
        command[strcspn(command, "\n")] = '\0';
        char firstArg[20];
        char secondArg[20];
        char thirdArg[20];
        char fourthArg[20];
        char fifthArg[20];
        firstArg[0]='\0';
        secondArg[0]='\0';
        thirdArg[0]='\0';
        fourthArg[0]='\0';
        fifthArg[0]='\0';
        int numArgs= sscanf(command,"%19s %19s %19s %19s %99s", firstArg, secondArg, thirdArg, fourthArg, fifthArg);
        int key=commandHandlerUser(firstArg,numArgs);
        fflush(stdin);
        if(key>=1 && key<=4) {

        }
        if(key==5 && numArgs==1) {
            break;
        }
    }
//    close(fd);
    pthread_join(tid[0], NULL);
    pthread_mutex_destroy(&lock);
    unlink(nomeFifo);
    return 0;
}
