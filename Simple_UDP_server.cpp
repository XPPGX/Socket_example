#include<stdio.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int main(int argc,char*argv[]){
	//Initialise winsock2
	WSADATA wsa;
	printf("\nInitialising winsock2...");
	if(WSAStartup(MAKEWORD(2,2),&wsa)!=0){
		printf("Failed. Error Code : %d",WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");
	//Create a socket
	SOCKET s;
	if((s = socket(AF_INET,SOCK_DGRAM,0))==INVALID_SOCKET){
		printf("Could not create socket : %d" , WSAGetLastError());
	}
	printf("Socket create.\n");
	//Bind
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);
	
	if(bind(s,(struct sockaddr*)&server,sizeof(server)) == SOCKET_ERROR){
		printf("Bind failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts("Bind done");
	//keep listening for data
	struct sockaddr_in si_other;
	int slen,recv_len;
	slen = sizeof(si_other);
	char buf[512];
	char str[] = "Hello";
	while(1){
		printf("waiting for data...");
		fflush(stdout);
		memset(buf,'\0',512);
		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, 512, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR){
			printf("recvfrom() failed with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		//print details of the client/peer and the data received
		printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		printf("Data: %s\n" , buf);
		//now reply the client with the same data
		if (sendto(s, str, strlen(str), 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}
	closesocket(s);
	WSACleanup();
	return 0;
}
