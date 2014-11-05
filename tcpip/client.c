#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int theSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(theSocket < 0)
	{
		fprintf(stderr,"ошибка вызова функции socket\n");
		exit(1);
	}

	struct sockaddr_in host;
	host.sin_family = AF_INET;
	host.sin_port = htons(7500);
	host.sin_addr.s_addr = inet_addr("127.0.0.1");
	int status;
	status = connect(theSocket, (struct sockaddr *) &host, sizeof(host));
	if(status)
	{
		fprintf(stderr, "ошибка вызова функции connect");
		exit(1);
	}

	status = write(theSocket, "a", 1);
	if(status <= 0)
	{
		fprintf(stderr, "ошибка вызова write");
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
	return 0;
}
