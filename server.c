#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 6000
#define BACKLOG 5
#define BUFFMAX 1024

#define CHECK_ERR(v, msg) \
	if(v){ perror(msg); exit(EXIT_FAILURE); } \
	else perror(msg);

#define handle_error(msg) \
	do{ perror(msg); exit(EXIT_FAILURE); }while(0);

#define success(msg) { perror(msg); }

int main(int argc, char** argv) {
	int sockfd, retval, connfd;
	struct sockaddr_in servAddr, clientAddr;
	socklen_t servLen, clientLen;
	char buff[BUFFMAX];
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	CHECK_ERR((sockfd < 0), "Socket");
	
	bzero(&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT);
	servAddr.sin_addr.s_addr = INADDR_ANY;
	servLen = sizeof(servAddr);

	retval = bind(sockfd, (struct sockaddr *)&servAddr, servLen);
	CHECK_ERR((retval < 0),"Bind");

	retval = listen(sockfd, BACKLOG);
	CHECK_ERR((retval < 0),"Listen");

	do {
		retval = accept(sockfd, (struct sockaddr *)&clientAddr, &clientLen);
		CHECK_ERR((retval < 0), "Accept");
		printf("Yey! +1 client connected\n");		
		do {
			memset(buff, '0', strlen(buff));
			printf("Me :: ");
			scanf(" %[^\n]", buff);
			retval = send(sockfd, buff, strlen(buff), 0);
			CHECK_ERR((retval < 0), "Write");
			
			memset(buff, '0', strlen(buff));
			printf("Server is waiting ...\n");
			retval = recv(sockfd, buff, BUFFMAX, 0);	
			CHECK_ERR((retval < 0),"Read");
			buff[retval] = '\0';
			printf("User :: %s", buff);
		} while(1);	

	} while(1);
	
	return 0;
}

