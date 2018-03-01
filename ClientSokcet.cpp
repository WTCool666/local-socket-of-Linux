#include "ClientSocket.h"
ClientSocket::ClientSocket():fd(-1){
}
virtual ClientSocket::~ClientSocket(){
}

int ClientSocket::requestConnectService(){
	int result=-1;
	struct sockaddr_un server_sockaddr;
	fd= socket(AF_UNIX,SOCK_SEQPACKET,0);
       if(fd < 0) {
	   	return -1;
      }
	server_sockaddr.sun_family=AF_UNIX;
      server_sockaddr.sun_path[0] = 0;
       strcpy(server_sockaddr.sun_path+1, SOCKET_PATH);
	socklen_t len_t=sizeof(server_sockaddr.sun_family) + sizeof(BLUETOOTH_LE_SCOKET_PATH);
	result=connect(fd,( struct sockaddr * )&server_sockaddr,len_t);
	if(result<0){
		close(fd);
		return -1;
	}
	return fd;
}

int ClientSocket::read(char* buf,unsigned int size){
	int ret = -1;
	ret = write(fd,buf,size);
	if(ret<0){
		return -1;
	}
	return ret;
}

int ClientSocket::write(char* buf,unsigned int size){
	int ret = -1;
	ret = write(fd,buf,size);
	if(ret<0){
		return -1;
	}
	return ret;
}


	