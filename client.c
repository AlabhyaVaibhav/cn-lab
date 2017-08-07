#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //defines Internet address family
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 3550	  	/* Server Port the client will connect */
#define MAXDATASIZE 100 /* Max number of bytes of data */

int main(int argc, char *argv[])
{
	int client_fd; /* file descriptor for client */
	int numbytes;	  
	char buf[MAXDATASIZE];  /* buf will store received text */
  
	struct sockaddr_in server;  /* server's address information */

	if (argc !=2) {	      /* used because the program will need one argument (IP) */
		printf("Usage: %s <IP Address>\n",argv[0]);
		exit(-1);
	}

	if ((client_fd=socket(AF_INET, SOCK_STREAM, 0))==-1){
		printf("socket() error\n");
		exit(-1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr =inet_addr(argv[1]); 
	bzero(&(server.sin_zero),8);

	if(connect(client_fd, (struct sockaddr *)&server,sizeof(struct sockaddr))==-1){ /* connect() to the server */
		printf("connect() error\n");
		exit(-1);
	}

	if((numbytes=recv(client_fd,buf,MAXDATASIZE,0)) == -1){  /* recv() data from the server */
		printf("recv() error\n");
		exit(-1);
	}

	buf[numbytes]='\0';

	printf("Server Message: %s\n",buf); /* prints server's welcome message =) */

	close(client_fd);   /* close the client_fd */

	return 0;
}
