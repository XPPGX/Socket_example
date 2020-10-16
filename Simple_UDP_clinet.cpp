#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "127.0.0.1"

int main(void){
	//Initialise winsock
	WSADATA wsa;
	printf("\nInitialising winsock2\n");
	if(WSAStartup(MAKEWORD(2,2),&wsa)!=0){
		printf("Failed. Error Code : %d",WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");
	
	//create socket
	int s;
	if((s=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) == SOCKET_ERROR){
		printf("socket() failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	
	//setup address structrue
	struct sockaddr_in si_other;
	int slen = sizeof(si_other);
	memset((char*)&si_other,0,slen);
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(8888);
	si_other.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	
	//start communication
	char buf[512],message[512];
	while(1){
		printf("Enter message : ");
		gets(message);
		//send the message
		if(sendto(s,message,strlen(message),0,(struct sockaddr*)&si_other,slen)==SOCKET_ERROR){
			printf("sendto() failed with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		//receive a reply and print it
		//clear the buffer
		memset(buf,'\0',512);
		if(recvfrom(s,buf,512,0,(struct sockaddr*)&si_other,&slen) == SOCKET_ERROR){
			printf("recvfrom() failed with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		puts(buf);
	}
	closesocket(s);
	WSACleanup();

	return 0;
}
