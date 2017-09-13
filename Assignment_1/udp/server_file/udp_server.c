#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
/* You will have to modify the program below */

#define MAXBUFSIZE 100

int main (int argc, char * argv[] )
{



// This is the general flow of the server... 
// socket() -> bind() -> recvfrom() -> sendto()


	int sock;                           //This will be our socket
	struct sockaddr_in server, remote;     //"Internet socket address structure"
	unsigned int remote_length;         //length of the sockaddr_in structure
	int nbytes;                        //number of bytes we receive in our message
	char buffer[MAXBUFSIZE];             //a buffer to store our received message

	if (argc != 2)
	{
		printf ("USAGE:  <port>\n");
		exit(1);
	}

	/******************
	  This code populates the sockaddr_in struct with
	  the information about our socket
	 ******************/
	bzero(&server,sizeof(server));                    //zero the struct
	server.sin_family = AF_INET;                   //address family
	server.sin_port = htons(atoi(argv[1]));        //htons() sets the port # to network byte order
	server.sin_addr.s_addr = INADDR_ANY;           //supplies the IP address of the local machine


	//Causes the system to create a generic socket of type UDP (datagram)
	printf("Creating Socket\n");
	sock = socket(server.sin_family, SOCK_DGRAM ,0 );
	if ( sock < 0)
	{
		printf("unable to create socket");
	}
	printf("\tSocket Created\n");


	/******************
	  Once we've created a socket, we must bind that socket to the 
	  local address and port we've supplied in the sockaddr_in struct
	 ******************/
	printf("Binding the socket to the port.\n");
	if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		printf("unable to bind socket\n");
	}
	printf("\tBinding complete!\n");
	printf("\tPort number = %d\n\n", ntohs(server.sin_port));



    // recv(socket_fd,data_buffer,sizeof(data_buffer),0);

	printf("Waiting for communication to happen\n");
	remote_length = sizeof(remote);

	//waits for an incoming message
	bzero(buffer,sizeof(buffer));
	while(1){

	// nbytes = nbytes = **** CALL RECVFROM() HERE ****;
      nbytes = recvfrom(sock, buffer, MAXBUFSIZE, 0, (struct sockaddr *)&remote, &remote_length);
      printf("POOP\n");
	  // printf("The client says %s\n", buffer);
	// char msg[] = "orange";
	// nbytes = **** CALL SENDTO() HERE ****;

	}
	close(sock);

}

