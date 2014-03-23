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
#define PORTNUM 80

int main(int argc, char **argv)
{

   char buffer[MAXRCVLEN + 1]; /* +1 so we can add null terminator */
   int len, mysocket;
   struct sockaddr_in dest;

   struct hostent *hostinfo;

   hostinfo = gethostbyname ("google.pl");

	if (hostinfo == 0)
	{
	  std::cerr << "Couldn't find google";
	  exit (1);
	}else{
		std::cout << "Found google" << std::endl;
	}

   mysocket = socket(AF_INET, SOCK_STREAM, 0);

   memset(&dest, 0, sizeof(dest));                /* zero the struct */
   dest.sin_family = AF_INET;
   dest.sin_addr = *(struct in_addr *) hostinfo->h_addr; /* set destination IP number - localhost, 127.0.0.1*/
   dest.sin_port = htons(PORTNUM);                /* set destination port number */

   connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr));

   std::string get = "GET / HTTP/1.0\n\n";

   send(mysocket, get.c_str(), get.size(), 0);

   len = recv(mysocket, buffer, MAXRCVLEN, 0);

   /* We have to null terminate the received data ourselves */
   buffer[len] = '\0';

   std::cout << buffer << std::endl;
   std::cout << "We have reclieved " << len << " bytes"<< std::endl;
   close(mysocket);
   return 0;
}


