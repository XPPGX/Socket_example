Socket_TCP_example
===
IDE：Dev-C++5.11
---
額外lib：<winsock2.h>
---
---
##   -----concept-----
## The following struct will be included in a SOCKET :
#### Address Family : AF_INET (this is IP version 4)
#### Type : SOCK_STREAM (this means connection oriented TCP protocol)
#### Protocol : 0 [ or IPPROTO_TCP , IPPROTO_UDP ]
## 
---

## 要寫的問題
```c
// Q1. WSAGetLastError() 與 WSAStartup()編譯不過
//////code//////
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")

int main(int argc,char *argv[]){
	WSADATA wsa;
	printf("\nInitialising Winsock...");
	if(WSAStartup(MAKEWORD(2,2),&wsa) != 0){
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
	printf("Initialised");
	return 0;
}

/*
Solution1:
=> Dev-C++ -> tool -> compiler options -> general
---
->click add the following commands when calling the compilers
---
->then you can add the above command ```-lwsock32 ``` -> compile again
*/
```
---
```c
//Q2.recv一次後，server的socket會關閉，可以用while()解決，要在while()裡面加入accept
//Solution2:

	//4.Accept connections
	int c = 0;
	SOCKET new_socket;
	struct sockaddr_in client;
	c = sizeof(struct sockaddr_in);
	char *message;
	///===============================
	while((new_socket = accept(s,(struct sockaddr*)&client,&c)) != INVALID_SOCKET){
		puts("connetion accepted");
		//5.read
		char buf[1024];
		int recv_size = 0;
		if(recv_size = recv(new_socket,buf,1024,0) == SOCKET_ERROR){
			puts("recv failed");
		}
		puts("Data received\n");
		puts(buf);	
		//Reply to the client
		
		message = "Hello Client, I have received your connection. But I have to go now, bye\n";
		send(new_socket,message,strlen(message),0);
	}
	//==============================
	if(new_socket == INVALID_SOCKET){
		printf("accept failed with error code: %d",WSAGetLastError());
		return 1;
	}
```
---
```c
//Q3.send一次後，client的socket會呈現被使用過的狀態，必須讓他初始化，所以要使用一個乾淨的socket指定給他
//Soulution3:
	SOCKET s,clean;
	//....the things you can do with socket s...........
	//after using socket s, we should assign clean to s like below
	s = clean;
	//reuse socket s to do what you want to do.
```
---
Reference：
---
1. <winsock2.h> from Windows Developer (https://docs.microsoft.com/en-us/windows/win32/api/winsock2/ns-winsock2-wsadata)
2. winsock2 tutorial(https://www.binarytides.com/udp-socket-programming-in-winsock/)