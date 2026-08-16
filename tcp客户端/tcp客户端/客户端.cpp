#include <stdio.h>
#include <WinSock2.h>
#include <string>
#include <conio.h>
#include <ws2tcpip.h> 
#include <windows.h>
using namespace std;
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define SERVER_IP  "192.168.1.81"
#define QUN_PORT  8080
#pragma comment(lib,"ws2_32.lib")

SOCKET severSocket;
sockaddr_in sockAddr;
char nickName[32];
char line1[111];
char line2[111];
HANDLE hmutex;

void gotoxy(int x, int y) {
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hout, pos);
}

void uiinit() {
    system("mode con lines=36 cols=110");
    system("cls");
    gotoxy(0, 28);

    for (int i = 0; i < 110; i++) {
        line1[i] = '-';
        line2[i] = ' ';
    }
    line1[110] = '\0';
    line2[110] = '\0';

    printf("%s", line1);
    printf("\n");
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

bool init() {
    WSADATA data;
    int ret = WSAStartup(MAKEWORD(2, 2), &data);
    if (ret != 0) {
        return false;
    }

    severSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (severSocket == INVALID_SOCKET) {
        return false;
    }

    sockAddr.sin_family = AF_INET;
    int re = InetPtonA(AF_INET, SERVER_IP, &sockAddr.sin_addr);
    if (re != 1) {
        printf("IP地址格式错误: %s\n", SERVER_IP);
        return false;
    }

    sockAddr.sin_port = htons(QUN_PORT);

    hmutex = CreateMutex(NULL, FALSE, "console");
    return true;
}

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

void login() {
    system("mode con lines=5 cols=30\n");
    printf("welcome to liao tian shi \n\n");
    printf("your name:");
    scanf_s("%s", nickName, (unsigned int)sizeof(nickName));
}

void printfmae(const char* msg) {
    WaitForSingleObject(hmutex, INFINITE);

    static POINT pos = { 0, 0 };
    gotoxy(pos.x, pos.y);

    static int color = 31;
    printf("\033[0;%d;40m%s\033[0m\n", color++, msg);

    if (color > 36) {
        color = 31;
    }

    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hout, &info);

    pos.x = info.dwCursorPosition.X;
    pos.y = info.dwCursorPosition.Y;

    if (pos.y >= 27) {
        gotoxy(0, 28);
        printf("%s\n", line2);
        printf("\n");
        gotoxy(0, 28);
        printf("%s\n", line1);
        pos.y -= 1;
    }

    gotoxy(1, 29);
    ReleaseMutex(hmutex);
}

DWORD WINAPI threadFuncRecv(LPVOID pram) {
    char buff[4096];

    while (1) {
        int ret = recv(severSocket, buff, sizeof(buff) - 1, 0);

        if (ret <= 0) {
            if (ret == 0) {
                printf("服务器已关闭连接\n");
            }
            else {
                printf("接收失败，错误码: %d\n", WSAGetLastError());
            }
            break;
        }

        buff[ret] = '\0';
        string msg = UTF8ToGBK(buff);
        printfmae(msg.c_str());
    }

    return 0;
}

void editprint(int col, char ch) {
    WaitForSingleObject(hmutex, INFINITE);
    gotoxy(col, 29);
    printf("%c", ch);
    ReleaseMutex(hmutex);
}

void editprint(int col, const char* ch) {
    WaitForSingleObject(hmutex, INFINITE);
    gotoxy(col, 29);
    printf("%s", ch);
    ReleaseMutex(hmutex);
}


int getDisplayWidth(const char* str, int len) {
    int width = 0;
    for (int i = 0; i < len; i++) {
        if ((unsigned char)str[i] > 0x80) {
            width += 2;
            i++;
        }
        else {
            width += 1;
        }
    }
    return width;
}


void refreshInputLine(const char* buff, int len) {
   
    gotoxy(0, 29);
    for (int i = 0; i < 110; i++) {
        printf(" ");
    }

    
    gotoxy(0, 29);
    printf(">");

    for (int i = 0; i < len; i++) {
        if ((unsigned char)buff[i] > 0x80) {
            printf("%c%c", buff[i], buff[i + 1]);
            i++;
        }
        else {
            printf("%c", buff[i]);
        }
    }
}

int main() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    if (!init()) {
        printf("初始化失败！\n");
        return -1;
    }

    int ret = connect(severSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr));
    if (ret != 0) {
        printf("连接服务器失败，请检查网络连接! 错误码: %d\n", WSAGetLastError());
        closesocket(severSocket);
        WSACleanup();
        return -2;
    }

    login();
    uiinit();

    HANDLE hThread = CreateThread(NULL, 0, threadFuncRecv, NULL, 0, NULL);
    if (hThread == NULL) {
        printf("创建线程失败\n");
        return -1;
    }

    CloseHandle(hThread);

  
    char buff[1024] = { 0 };
    int len = 0;

  
    editprint(0, '>');

    while (1) {
        char c = _getch();

       
        if (c == '\r') {
            if (len == 0) {
                continue;
            }

            
            WaitForSingleObject(hmutex, INFINITE);
            gotoxy(0, 29);
            for (int i = 0; i < 110; i++) {
                printf(" ");
            }
            ReleaseMutex(hmutex);

           
            char buff2[1024];
            sprintf_s(buff2, sizeof(buff2), "[client_socket@%s] %s", nickName, buff);
            printfmae(buff2);
            string mm = buff2;
            GBKToUTF8(mm);
            send(severSocket, mm.c_str(), mm.length(), 0);

           
            memset(buff, 0, sizeof(buff));
            len = 0;

            
            editprint(0, '>');
            continue;
        }

        
        if (c == 8) {
            if (len == 0) {
                continue;
            }

            WaitForSingleObject(hmutex, INFINITE);

          
            bool isChinese = false;
            if (len >= 2 && (unsigned char)buff[len - 2] > 0x80) {
                isChinese = true;
            }

          
            if (isChinese) {
                buff[len - 2] = 0;
                buff[len - 1] = 0;
                len -= 2;
            }
            else {
                buff[len - 1] = 0;
                len -= 1;
            }

            
            refreshInputLine(buff, len);

            
            int cursorPos = 1 + getDisplayWidth(buff, len);
            gotoxy(cursorPos, 29);

            ReleaseMutex(hmutex);
            continue;
        }

        
        WaitForSingleObject(hmutex, INFINITE);

        bool isChinese = ((unsigned char)c > 0x80);
        if (isChinese) {
            char c2 = _getch();
            if (len + 2 < sizeof(buff)) {
                buff[len++] = c;
                buff[len++] = c2;
                printf("%c%c", c, c2);
            }
        }
        else {
            if (len + 1 < sizeof(buff)) {
                buff[len++] = c;
                printf("%c", c);
            }
        }

        ReleaseMutex(hmutex);
    }

    closesocket(severSocket);
    WSACleanup();
    CloseHandle(hmutex);

    return 0;
}