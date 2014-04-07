
/*
 * server.cpp


 *
 *  Created on: Apr 7, 2014
 *      Author: jb
 */

#include<signal.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/types.h>
#include<stdlib.h>
#include <unistd.h>


#include <iostream>
#include <stdexcept>

#define BUFSIZE 2048
#define PORT    9000



int main(int argv, char **argc){
	struct sockaddr_in myaddr;
	struct sockaddr_in remoteaddr;
	socklen_t addr_len;
	int recvlen;
	int fd;
	unsigned char buf[BUFSIZE+1];
	const char* response = "OK";

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		perror("cannot create socket\n");
		return 1;
	}

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(PORT);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		return 2;
	}

	while(true){
		printf("waiting on port %d\n", PORT);
		memset((char *)&remoteaddr, 0, sizeof(remoteaddr));
		addr_len = sizeof(remoteaddr);
		recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *)&remoteaddr, &addr_len);
		if (recvlen < 0){
		 perror("Error while receiving data");
		}
		printf("received %d bytes\n", recvlen);
		if (recvlen > 0) {
		 buf[recvlen] = 0;
		 printf("received message: \"%s\"\n", buf);
		}
		printf("remote host: %d\n", remoteaddr.sin_addr);
		printf("Sending response\n");
		sendto(fd, "OK", sizeof("OK"), 0, (struct sockaddr *)&remoteaddr, addr_len);
	}

}


