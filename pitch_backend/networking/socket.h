#ifndef SOCKET_H
#define SOCKET_H

#include <memory>

#include "packet.h"

class SocketImpl;

class Socket
{
public:
    Socket();
    virtual ~Socket();

    int send(char * buffer);
    char* received();


protected:
    std::unique_ptr<SocketImpl> impl_;
};

class ServerSocket final : public Socket
{
public:

private:
};

class ClientSocket final : public Socket
{
public:

private:
};


#endif //SOCKET_H
