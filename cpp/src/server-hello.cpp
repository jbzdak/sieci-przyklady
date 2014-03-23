#include<signal.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/types.h>
#include<stdlib.h>

#include <iostream>
#include <stdexcept>


int open_server_socket(std::string host, int port){

	struct sockaddr_in myaddr ,clientaddr;
	int sockid;
	sockid=socket(AF_INET,SOCK_STREAM,0);
	memset(&myaddr,'0',sizeof(myaddr));
	myaddr.sin_family=AF_INET;
	myaddr.sin_port=htons(5555);
	myaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(sockid==-1)
	{
		throw std::runtime_error("Couldnt socket socket");
	}
	int len=sizeof(myaddr);
	if(bind(sockid,( struct sockaddr*)&myaddr,len)==-1)
	{
		throw std::runtime_error("Couldnt bind socket");
	}
	if(listen(sockid,10)==-1)
	{
		throw std::runtime_error("Couldnt listen socket");
	}
	return sockid;
}

void handle_connection(int client_socket){

    std::string hello_world = "Hello world\n";

    send(client_socket, hello_world.c_str(), hello_world.size(), 0);
}

int main()
{

	int sockid = open_server_socket("localhost", 5555);

	int newsockid = accept(sockid,0,0);

	handle_connection(newsockid);

}
