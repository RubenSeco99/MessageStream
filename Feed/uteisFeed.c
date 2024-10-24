#include "uteisFeed.h"

int CommandHandlerUserKey(const char *command){
    char *commands[]= {"topics","msg","subscribe","unsubscribe","exit"};
    int NumCommands = sizeof(commands) / sizeof(commands[0]);
    for(int i=0; i < NumCommands;i++)
        if(strcmp(commands[i],command) == 0)
            return (i+1);
    return 0;
}
int commandHandlerUser(const char *firstArg,const int numArgs) {
    const int key=CommandHandlerUserKey(firstArg);
    if(key>0) {
        if(numArgs==1 && (key==1 || key==5)){
            printf("Command %s valid!\n",firstArg);
            return key;
        }
        if(numArgs==2 && (key==3 || key==4)) {
            printf("Command %s valid!\n",firstArg);
            return key;
        }if(numArgs==4 && (key==2)) {
            printf("Command %s valid!\n",firstArg);
            return key;
        }
        printf("Command invalid\n");
        return 0;
    }
    printf("command invalid\n");
    return 0;
}
    bool verificaLogin(COMUNICACAO *p,COMUNICACAO *r,char *nomeFifo) {
        char nome[20],comando[6];
        strncpy(comando, "login", sizeof(comando) - 1);
        comando[sizeof(comando) - 1] = '\0';
        printf("Indique o seu username: ");
        scanf("%s",nome);
        fflush(stdin);
        strcpy(p->user.name,nome);
        strcpy(p->command,comando);

        sprintf(nomeFifo, "FIFO_USER_%d", getpid());
        if (mkfifo(nomeFifo, 0640) == -1) {
            printf("Erro ao criar FIFO do cliente");
            return false;
    }
        int fd = open(SRV_FIFO,O_WRONLY);
        if(fd == -1) {
            printf("Erro ao abrir o fifo para escrita\n");
            unlink(nomeFifo);
            return false;
        }
        strncpy(p->fd_user, nomeFifo, sizeof(p->fd_user) - 1);
        p->fd_user[sizeof(p->fd_user) - 1] = '\0';
        printf("comando para enviar: %s \n",p->command);
        if (write(fd, p, sizeof(COMUNICACAO)) == -1) {
            printf("Erro ao enviar dados para o servidor.\n");
            close(fd);
            return false;
        }
        close(fd);
        int fd_resposta = open(nomeFifo, O_RDONLY);
        if (fd_resposta == -1) {
            printf("Erro ao abrir FIFO de resposta do cliente.\n");
            return false;
        }
        if (read(fd_resposta, r, sizeof(COMUNICACAO)) == -1) {
            printf("Erro ao ler resposta do servidor.\n");
            close(fd_resposta);
            return false;
        }
        close(fd_resposta);
        if(strcmp(r->message,"login bem sucedido")==0) {
            return true;
        }
        if(strcmp(r->message,"login mal sucedido")==0) {
            printf("Username já em uso.\n");
            return false;
        }
        return true;
    }