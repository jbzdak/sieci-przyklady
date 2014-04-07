#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>

#include <iostream>

#define MAXRCVLEN 1000
#define PORTNUM 9000


int do_client(char * addr, int bcast){
	char buffer[MAXRCVLEN + 1]; /* +1 so we can add null terminator */
	int len, mysocket;
	struct sockaddr_in dest;

	struct hostent *hostinfo;

	hostinfo = gethostbyname ("192.168.1.70");

	if (hostinfo == 0)
	{
		perror("Couldn't find destination address\n");
		exit (1);
	}else{
		printf("Found destination address\n");
	}

	mysocket = socket(AF_INET, SOCK_DGRAM, 0);

	if (mysocket < 0){
	   perror("Socket creation failed");
	   exit(3);
	}

	struct timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	if (setsockopt (mysocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
			   sizeof(timeout)) < 0){
	   perror("setsockopt failed\n");
	   exit(2);
	}

	if(bcast){
		int optval = 1;
		int response = setsockopt(mysocket, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));
		if (response < 0){
		   perror("setsockopt failed (for broadcast)\n");
		   exit(2);
		}

	}

	memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr = *(struct in_addr *) hostinfo->h_addr;
	dest.sin_port = htons(PORTNUM);

	std::string message = "Hello World";

	sendto(mysocket, message.c_str(), message.size(), 0, (const sockaddr*) &dest, sizeof(dest));

	len = recv(mysocket, buffer, MAXRCVLEN, 0);

	/* We have to null terminate the received data ourselves */
	buffer[len] = '\0';

	if(len > 0){
	   printf("response:\n");
	   printf(buffer);
	}else{
	   printf("No response\n");
	}

	close(mysocket);
	return 0;
}


int main(int argc, char **argv)
{
	char* addr = "192.168.1.70";
	char* mulitcast_addr = "224.3.29.71";
	char* bcast_addr ="192.168.1.255";
//	do_client(addr, 0); // Bez broadcasta
	do_client(mulitcast_addr, 0); // Multicast
//	do_client(bcast_addr, 1); // Z broadcastem

}


