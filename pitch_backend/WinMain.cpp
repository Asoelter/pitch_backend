#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif


#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include <covid/socket.h>

#include <string>

void MsgBox(const char * title, const char * message)
{
    MessageBox(NULL, title, message, NULL);
}

INT WinMain(HINSTANCE hInstance, 
            HINSTANCE hPrevInstance,
            PSTR lpCmdLine, 
            INT nCmdShow)
{
    const auto port = Port("127.0.0.1", "49152");
    const auto socket = Socket::listenOn(port);
    const auto messageInBytes = socket.receive();
    const auto message = std::string(messageInBytes.begin(), messageInBytes.end());
    MsgBox("received stuff", message.c_str());

    socket.send({ 'b', 'a', 'c', 'k', '\0' });

    return 0;
}
