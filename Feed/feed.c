#include "feed.h"
void *processServerResponses(void* pdata) {
    sleep(1);
    printf("Processing server responses\n");
    return 0;
}
int main(int argc, char**argv, char **envp){
    if(access(SRV_FIFO,F_OK) != 0){
        printf("Server is Resting! \n");
        return 1;
    }
    printf("Main\n");
    pthread_mutex_t lock;
    pthread_t tid[NTHREADSCLIENTS];//Guarda o id das threads para depois fazer o create e o join
    pthread_mutex_init(&lock,NULL);
    pthread_create(&tid[0],NULL,processServerResponses,&lock);//que info é preciso para a thread
    //uma vez que ela so vai imprimir coisas no ecra??
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
        int numArgs= sscanf(command,"%19s %19s %19s %19s [%99]s", firstArg, secondArg, thirdArg, fourthArg, fifthArg);
        printf("%s\n",firstArg);
        printf("numArgs:%d\n",numArgs);
        int key=commandHandlerUser(firstArg,numArgs);
        fflush(stdin);
        if(key==7 && numArgs==1) {
            break;
        }
    }

    pthread_join(tid[0], NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}
