#include "feed.h"
void *processServerResponses(void* pdata) {
    sleep(1);
    printf("Processing server responses\n");
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


    pthread_join(tid[0], NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}
