#include "feed.h"
void *processServerResponses(void* pdata) {
    //int fd = *((int*)pdata);
    //char response[1024];
    sleep(1);
    printf("Processing server responses\n");
    return 0;
}
int main(int argc, char**argv, char **envp){
    if(access(SRV_FIFO,F_OK) != 0){
        printf("Server is Resting! \n");
        return 1;
    }
    char nome[20];
    char comando[5];
    char nomeFifo[20];
    printf("Indique o seu userName: ");
    scanf("%s",nome);
    //tentar por isto numa função >
    strncpy (comando,"login",sizeof(comando));
    fflush(stdin);
    COMUNICACAO p,r;
    strcpy(p.user.name,nome);
    strcpy(p.command,comando);
    sprintf(nomeFifo, "FIFO_USER_%d", getpid());
    mkfifo(nomeFifo, 0640);

    int fd = open(SRV_FIFO,O_WRONLY);
    if(fd == -1) {
        printf("Error opening file\n");
        return 2;
    }
    strncpy(p.fd_user, nomeFifo, sizeof(p.fd_user) - 1);
    p.fd_user[sizeof(p.fd_user) - 1] = '\0';
    if (write(fd, &p, sizeof(p)) == -1) {
        printf("Erro ao enviar dados para o servidor.\n");
        close(fd);
        return 3;
    }
    close(fd);
    int fd_resposta = open(nomeFifo, O_RDONLY);
    if (fd_resposta == -1) {
        printf("Erro ao abrir FIFO de resposta do cliente.\n");
        return 4;
    }
    if (read(fd_resposta, &r, sizeof(r)) == -1) {
        printf("Erro ao ler resposta do servidor.\n");
        close(fd_resposta);
        return 5;
    }

    close(fd_resposta);
    printf("Recebi a mensagem: %s",r.message);

    //< ate aqui!

    pthread_mutex_t lock;
    pthread_t tid[NTHREADSCLIENTS];//Guarda o id das threads para depois fazer o create e o join
    pthread_mutex_init(&lock,NULL);
    pthread_create(&tid[0],NULL,processServerResponses,nomeFifo);//que info é preciso para a thread
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
        int numArgs= sscanf(command,"%19s %19s %19s %19s %99s", firstArg, secondArg, thirdArg, fourthArg, fifthArg);
        int key=commandHandlerUser(firstArg,numArgs);
        fflush(stdin);
        if(key>=1 && key<=6) {

        }
        if(key==7 && numArgs==1) {
            break;
        }
    }
    close(fd);
    pthread_join(tid[0], NULL);
    pthread_mutex_destroy(&lock);
    unlink(nome);
    return 0;
}
