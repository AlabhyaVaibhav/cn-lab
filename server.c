//server send msg to client
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 3550   /* Server Port that will be opened */ 
#define BACKLOG 2   /* Number of allowed connections */

int main()
{
 
	int listen_fd, conn_fd; /* file descriptors that will refer to different sockets used in the program*/

	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in client; /* client's address information */

	socklen_t sin_size;

	if ((listen_fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
		printf("socket() error\n");
		exit(-1);
	}

	server.sin_family = AF_INET;         
	server.sin_port = htons(PORT);  
	server.sin_addr.s_addr = INADDR_ANY;     
	bzero(&(server.sin_zero),8);
  
	if(bind(listen_fd,(struct sockaddr*)&server,sizeof(struct sockaddr))==-1){ /* bind() the server address to the listen_fd */
		printf("bind() error\n");
		exit(-1);
	}     

	if(listen(listen_fd,BACKLOG) == -1){  
		printf("listen() error\n");
		exit(-1);
	}

	while(1){
		sin_size=sizeof(struct sockaddr_in);
	
		if ((conn_fd = accept(listen_fd,(struct sockaddr *)&client,&sin_size))==-1){ /* accept() the connection from client */
			printf("accept() error\n");
			exit(-1);
		}
		printf("You got a connection from %s\n",inet_ntoa(client.sin_addr) ); /* prints client's IP */

		send(conn_fd,"Welcome to my server.\n",22,0); /* send the welcome message to the client */
  
		close(conn_fd); /*  close the conn_fd */
	}
	return 0;
}
