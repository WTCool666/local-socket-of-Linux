#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdint.h>

#define SOCKET_PATH "clientSocket@com"
class ClientSocket{
public:
	ClientSocket();
	virtual ~ClientSocket();
	int requestConnectService();
	int read();
	int write();
private:
	int fd;
};
#endif