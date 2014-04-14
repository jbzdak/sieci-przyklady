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
	struct sockaddr_in listenaddr;
	struct sockaddr_in remoteaddr;
	struct  ip_mreq group_addr;
	socklen_t addr_len;


	memset((char *)&listenaddr, 0, sizeof(listenaddr));
	listenaddr.sin_family = AF_INET;
	listenaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	listenaddr.sin_port = htons(PORT);

	int recvlen;
	int fd;
	unsigned char buf[BUFSIZE+1];
	const char* response = "OK";

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		perror("cannot create socket\n");
		return 1;
	}

	if(bind(fd, (const sockaddr*)&listenaddr, sizeof(listenaddr))<0){
		perror("Error while listening to group.");
		exit(8);
	}

	group_addr.imr_multiaddr.s_addr = inet_addr("224.3.29.71");
	group_addr.imr_interface.s_addr = htonl(INADDR_ANY);

	if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group_addr, sizeof(group_addr))<0){
		perror("Couldn't listen to group");
		exit(1);
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


