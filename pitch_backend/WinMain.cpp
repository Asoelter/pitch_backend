#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include <string>

#include "networking/socket.h"
//#include "dependencies/covid/covid/covid.h"

void MsgBox(const char * title, const char * message)
{
    MessageBox(NULL, title, message, NULL);
}

void displayError()
{
    const auto error = WSAGetLastError();
    const auto msg = std::string("bind failed because: ") + std::to_string(error);
    MsgBox("error", msg.c_str());
}

INT WinMain(HINSTANCE hInstance, 
            HINSTANCE hPrevInstance,
            PSTR lpCmdLine, 
            INT nCmdShow)
{
    Socket socket;

#if 0
    MsgBox("test window", "test window");

    //Init Winsock
    WSADATA wsaData;

    auto iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    if (iResult != 0) {
        MsgBox("Error", "WSAStartup failed: %d\n");
        return 1;
    }

    //Get IP Address info

    constexpr auto defaultPort = "49152";

    addrinfo* result = nullptr;
    addrinfo hints = {};

    ZeroMemory(&hints, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the local address and port to be used by the server
    iResult = getaddrinfo(NULL, defaultPort, &hints, &result);
    if (iResult != 0) {
        MsgBox("error", "getaddrinfo failed");
        WSACleanup();
        return 1;
    }

    //initialize the socket and check for errors
    const auto listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (listenSocket == INVALID_SOCKET) {
        MsgBox("Error", "Could not initialize the socket");
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    int yes = 1;
    if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&yes), sizeof(int)) == -1)
    {
        displayError();
        freeaddrinfo(result);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    //bind the socket
    iResult = bind( listenSocket, result->ai_addr, static_cast<int>(result->ai_addrlen));

    // Setup the TCP listening socket
    if (iResult == SOCKET_ERROR) {
        MsgBox("error", "bind failed");
        freeaddrinfo(result);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result); //result is no longer needed

    iResult = listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        MsgBox("error", "listening failed");
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    const auto clientSocket = accept(listenSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        MsgBox("error", "accept failed");
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    char buffer[5];
    const auto bytesReceived = recv(clientSocket, buffer, 5 * sizeof(char), 0);

    if(bytesReceived == - 1)
    {
        displayError();
    }

    const auto msg = std::string("received ") + std::string(buffer);

    MsgBox("Success", msg.c_str());

#endif
    return 0;
}
