#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int port;

	if(argc < 2)
		port = 7500;
	else
		port = atoi(argv[1]);

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
	local.sin_port = htons(7500);
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

	char buffer[1];
	status = read(theSocket, buffer, 1);
	if(status <= 0)
	{
		fprintf(stderr, "ошибка вызова read");
		exit(1);
	}
	fprintf(stdout,"%c\n",buffer[0]);
	
	status = write(theSocket, "b", 1);
	if(status <= 0)
	{
		fprintf(stderr, "ошибка вызова write");
		exit(1);
	}
	return 0;
}
