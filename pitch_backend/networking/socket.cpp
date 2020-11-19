#include "socket.h"

#include <Windows.h>

class SocketImpl
{
public:

private:

};

Socket::Socket()
{
    MessageBox(NULL, "Socket created", "Info", 0);
}

Socket::~Socket()
{
    MessageBox(NULL, "Socket destroyed", "Info", 0);
}

