#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 6789
#define BUFFMAX 1024
#define CHECK_ERR(v, msg) \
	if(v){ perror(msg); exit(EXIT_FAILURE); } \
	else perror(msg);

int main(int argc, char* argv[]) {

	int sockfd, retval;
	struct sockaddr_in servAddr;
	socklen_t servLen;
	char buff[BUFFMAX];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	CHECK_ERR((sockfd < 0), "Socket");
	
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT);
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servLen = sizeof(servAddr);

	retval = connect(sockfd, (struct sockaddr *)&servAddr, servLen);
	CHECK_ERR((retval < 0), "Connet");

	do {
		memset(buff, '\0', strlen(buff));
		retval = recv(sockfd, buff, BUFFMAX, 0);
		//CHECK_ERR((retval < 0),"Read");
		printf("CPU :: %s\n", buff);
		
		memset(buff, '\0', strlen(buff));
		printf("Me :: ");
		scanf(" %[^\n]", buff);
		retval = send(sockfd, buff, strlen(buff), 0);
		//CHECK_ERR((retval < 0), "Write");
	} while (1);

	return 0;
}
