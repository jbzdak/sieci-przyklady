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

std::string read_message(int client_socket){
	char buffer = 0;
	std::string result;

	while(buffer!='\n'){
		int recv_result = recv(client_socket, &buffer, 1, 0);
		if (recv_result == 0){
			throw std::runtime_error("Client closed socket earlier");
		}
		if(recv_result == -1){
			throw std::runtime_error("Eroor reading from socket");
		}
		result+=buffer;
	}
	return result;
}

void handle_connection(int client_socket){

    std::string hello_world = "Wpisz coś\n";

    send(client_socket, hello_world.c_str(), hello_world.size(), 0);

    while (true){
		std::string message = read_message(client_socket);

		if (message.find("END") != std::string::npos){
			std::string msg = "Kończymy!\n";
			send(client_socket, msg.c_str(), msg.size(), 0);
			close(client_socket);
			return;
		}
		send(client_socket, message.c_str(), message.size(), 0);

    }
}

int main()
{

	int sockid = open_server_socket("localhost", 5555);

	while(true){

		int newsockid = accept(sockid,0,0);
		int pid = fork();
		if (pid == -1){
			throw std::runtime_error("Forking error");
		}
		if (pid == 0){
			handle_connection(newsockid);
			return 0;
		}

	}

}
