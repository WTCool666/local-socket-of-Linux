#ifndef SERVICE_SOCKET_H
#define SERVICE_SOCKET_H

#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdint.h>

#define SOCKET_PATH "clientSocket@com"
#define LISTEN_MAX_SOCKET_NUM  20
class ServiceSocket{
public:
	ServiceSocket();
	virtual ServiceSocket();
	int createService();
	int read();
	int write();
private:
	int client_socket;
};
#endif