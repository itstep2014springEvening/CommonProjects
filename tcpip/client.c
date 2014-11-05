#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUFER_LENGTH 256

int main(int argc, char **argv)
{
	char ipAddress[16];
	int port;
	if(argc < 2)
		strcpy(ipAddress, "127.0.0.1");
	else
		strcpy(ipAddress, argv[1]);

	if(argc < 3)
		port = 7500;
	else
		port = atoi(argv[2]);

	if(port<=0)
	{
		fprintf(stderr,"port должен быть числом");
		exit(2);
	}

	int theSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(theSocket < 0)
	{
		fprintf(stderr,"ошибка вызова функции socket\n");
		exit(1);
	}

	struct sockaddr_in host;
	host.sin_family = AF_INET;
	host.sin_port = htons(port);
	host.sin_addr.s_addr = inet_addr(ipAddress);
	int status;
	status = connect(theSocket, (struct sockaddr *) &host, sizeof(host));
	if(status)
	{
		fprintf(stderr, "ошибка вызова функции connect");
		exit(1);
	}

	fprintf(stdout,"соединение установлено\n\n");
	char bufer[MAX_BUFER_LENGTH]={0};
	do{
		fprintf(stdout,"< ");
		fgets(bufer, MAX_BUFER_LENGTH, stdin);
		status = write(theSocket, bufer, MAX_BUFER_LENGTH-1);
		if(status <= 0)
		{
			fprintf(stderr, "ошибка вызова write");
			exit(1);
		}

		status = read(theSocket, bufer, MAX_BUFER_LENGTH - 1);
		bufer[MAX_BUFER_LENGTH - 1] = 0;
		if(status <= 0)
		{
			fprintf(stderr, "ошибка вызова read");
			exit(1);
		}
		fprintf(stdout,"> %-.255s",bufer);
	}while(strcmp(bufer, "/exit\n")!=0);

	fprintf(stdout,"связь прекращена\n");

	return 0;
}
