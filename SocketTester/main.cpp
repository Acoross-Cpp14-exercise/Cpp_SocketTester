#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <Windows.h>
#include <ws2tcpip.h>

#include <iostream>

// initialize Winsock
bool Init()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
	{
		printf("error!");
		WSACleanup();
		return false;
	}
	return true;
}

void Cleanup()
{
	WSACleanup();
}

int main(int argc, int argv)
{
	Init();

	//////////////////////////////
	// dummy send socket
	SOCKET cliDummy = NULL;
	cliDummy = socket(PF_INET, SOCK_STREAM, 0);
	sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(7777);
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (-1 == connect(cliDummy, (sockaddr*)&server_addr, sizeof(server_addr)))
	{
		printf("dummy client fail.\n");
		exit(1);
	}

	///////////////////////////////
	// send tester
	while (true)
	{
		char sendbuff[100]{ 10, 0, };
		scanf_s("%10s", &sendbuff[2], 98);
		int len = strlen(&sendbuff[2]) + 2;
		sendbuff[0] = len;
		send(cliDummy, sendbuff, len, 0);
	}

	Cleanup();
}