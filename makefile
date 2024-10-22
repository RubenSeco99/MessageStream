MSG_FICH = DataMensagens.txt

all: feed manager mensagem

feed: Feed/feed.o
	gcc -o feed Feed/feed.o

Feed/feed.o: Feed/feed.c
	gcc -c Feed/feed.c -o Feed/feed.o

manager: Manager/manager.o Manager/uteisManager.o
	MSG_FICH=$(MSG_FICH) gcc -o manager Manager/manager.o

Manager/manager.o: Manager/manager.c Manager/uteisManager.c
	gcc -c Manager/manager.c -o Manager/manager.o

Manager/uteisManager.o: Manager/uteisManager.c
	gcc -c Manager/uteisManager.c -o Manager/uteisManager.o

mensagem: Mensagem/mensagem.o
	gcc -o mensagem Mensagem/mensagem.o

Mensagem/mensagem.o: Mensagem/mensagem.c
	gcc -c Mensagem/mensagem.c -o Mensagem/mensagem.o

run_manager:
	export MSG_FICH
	MSG_FICH=$(MSG_FICH) ./manager

clean:
	rm -f Feed/*.o Mensagem/*.o Manager/*.o