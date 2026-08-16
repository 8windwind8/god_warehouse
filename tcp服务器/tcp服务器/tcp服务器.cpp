#include<stdio.h>
#include<string.h>
#include<WinSock2.h>
#include<string>
#include<windows.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
SOCKET clients[50];
int clientcount = 0;
CRITICAL_SECTION cs;
string UTF8ToGBK(const char* strUTF8) {
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, (len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);

	std::string strTemp(szGBK);
	delete[] wszGBK;
	delete[] szGBK;
	return strTemp;
}
bool GBKToUTF8(std::string& strGBK) {
	int len = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	if (len <= 0) return false;

	wchar_t* wszUnicode = new wchar_t[len];
	memset(wszUnicode, 0, len * sizeof(wchar_t));

	if (MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, wszUnicode, len) <= 0) {
		delete[] wszUnicode;
		return false;
	}

	len = WideCharToMultiByte(CP_UTF8, 0, wszUnicode, -1, NULL, 0, NULL, NULL);
	if (len <= 0) {
		delete[] wszUnicode;
		return false;
	}

	char* szUTF8 = new char[len + 1];
	memset(szUTF8, 0, len + 1);

	if (WideCharToMultiByte(CP_UTF8, 0, wszUnicode, -1, szUTF8, len, NULL, NULL) <= 0) {
		delete[] wszUnicode;
		delete[] szUTF8;
		return false;
	}

	strGBK = szUTF8;
	delete[] wszUnicode;
	delete[] szUTF8;
	return true;
}
void addclient(SOCKET sock)
{
	EnterCriticalSection(&cs);
	if (clientcount < 50)
	{
		clients[clientcount++] = sock;
	}
	LeaveCriticalSection(&cs);

}
void removeclient(SOCKET sock)
{
	EnterCriticalSection(&cs);
	for (int i = 0; i < clientcount; i++)
	{
		if (clients[i] == sock)
		{
			clients[i] = clients[clientcount - 1];
			clientcount--;
			break;
		}
		continue;
	}
	LeaveCriticalSection(&cs);
}
void broadmessage(SOCKET sender, const char* message, int len)
{
	EnterCriticalSection(&cs);
	for (int i = 0; i < clientcount; i++)
	{
		if (clients[i] != sender)
		{
			send(clients[i], message, len, 0);
		}
	}
	LeaveCriticalSection(&cs);
}
DWORD WINAPI thread_func(LPVOID lpThreadParameter)
{
	SOCKET client_socket = *(SOCKET*)lpThreadParameter;
	free(lpThreadParameter);
	printf("%llu,connect", client_socket);
	string s = "new client connect";
	addclient(client_socket);
	EnterCriticalSection(&cs);
	for (int i = 0; i < clientcount; i++)
	{
		send(clients[i], s.c_str(), s.length(), 0);
	}
	LeaveCriticalSection(&cs);
	while (1)
	{
		char buffer[1024] = { 0 };

		int ret = recv(client_socket, buffer, sizeof(buffer)-1, 0);
		broadmessage(client_socket, buffer, ret);
		string mm = UTF8ToGBK(buffer);
		if (ret <= 0)
		{
			break;
		}
		buffer[ret] = '\0';
		printf("%s\n", buffer);
		
	
	}
	removeclient(client_socket);
	string ss = "one client disconnect";
	for (int i = 0; i < clientcount; i++)
	{
		send(clients[i], ss.c_str(), ss.length(), 0);
	}
	printf("%llu,disconnect", client_socket);
	closesocket(client_socket);
	return 0;

}
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	InitializeCriticalSection(&cs);
	if (-1 == listen_socket)
	{
		printf("create listen socket failed");
		return -1;
	}
	struct sockaddr_in local = { 0 };
	local.sin_family = AF_INET;
	local.sin_port = htons(8080);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(listen_socket, (struct sockaddr*)&local, sizeof(local)) == -1)
	{
		printf("bind socket failed!");
		return -1;
	}

	if (listen(listen_socket, 10) == -1)
	{
		printf("listen socket falied!");
			return -1;
	}
	while (1)
	{
		SOCKET client_socket = accept(listen_socket, NULL, NULL);
		if (-1 == client_socket)
		{
			continue;
		}
		

	
		SOCKET* sockfd = (SOCKET*)malloc(sizeof(SOCKET));
		if (sockfd == NULL) {
		
			return -1;
		}

		*sockfd = client_socket;

		HANDLE hThread = CreateThread(NULL, 0, thread_func, sockfd, 0, NULL);
		if (hThread == NULL) {
			
			free(sockfd);
		
			return -1;
		}
		CloseHandle(hThread);
		
		
		
		
	}
	closesocket(listen_socket);
	EnterCriticalSection(&cs);
	for (int i = 0; i < clientcount; i++) {
		closesocket(clients[i]);
	}
	LeaveCriticalSection(&cs);


	DeleteCriticalSection(&cs);
	
	WSACleanup();
	



	return 0;
}

