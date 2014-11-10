#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUFER 512

int main(int argc, char **argv)
{
	int port;

	if(argc < 2)
		port = 7500;
	else
		port = atoi(argv[1]);

	fprintf(stdout,"port: %d\n", port);

	if(port<=0)
	{
		fprintf(stderr,"port должен быть числом");
		exit(2);
	}

	int listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(listenSocket < 0)
	{
		fprintf(stderr,"ошибка вызова функции socket\n");
		exit(1);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	int status;
	status = bind(listenSocket, (struct sockaddr *) &local, sizeof(local));
	if(status < 0)
	{
		fprintf(stderr,"ошибка вызова функции bind\n");
		exit(1);
	}

	status = listen(listenSocket, 5);
	if(status)
	{
		fprintf(stderr,"ошибка вызова функции listen\n");
		exit(1);
	}

	int theSocket = accept(listenSocket, NULL, NULL);
	if(theSocket < 0)
	{
		fprintf(stderr,"ошибка вызова функции accept\n");
		exit(1);
	}
	fprintf (stdout, "соединение установлено\n");

	char bufer[MAX_BUFER];
	do{
		status = read(theSocket, bufer, MAX_BUFER);
		if(status <= 0)
		{
			fprintf(stderr, "ошибка вызова read");
			exit(1);
		}
		fprintf(stdout,"> %s\n",bufer);

		fprintf(stdout,"< ");
		fgets(bufer, MAX_BUFER, stdin);
		status = write(theSocket, bufer, MAX_BUFER);
		if(status <= 0)
		{
			fprintf(stderr, "ошибка вызова write");
			exit(1);
		}
	}while(strcmp("/exit\n", bufer)!=0);
	return 0;
}
