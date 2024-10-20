#include "manager.h"
int main(int argc, char** argv, char** envp) {
    char *msg_fich = getenv("MSG_FICH");

    // Verifica se a variável foi encontrada
    if (msg_fich != NULL) {
        printf("A variável MSG_FICH é: %s\n", msg_fich);
    } else {
        printf("Erro: Variável de ambiente MSG_FICH não está definida.\n");
    }

    return 0;
}
