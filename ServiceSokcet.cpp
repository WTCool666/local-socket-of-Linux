#include "ServiceSocket.h"
ServiceSocket::ServiceSocket():client_socket(-1){
}
virtual ServiceSocket::ServiceSocket(){
}

int ServiceSocket::createService(){
	int serverFd = -1;
	struct sockaddr_un serv_addr;
	struct sockaddr_un client_addr;
	int client_addr_len = sizeof(struct sockaddr_un);
	memset(&client_addr,0x00,sizeof(client_addr));
	char cmd[100] = "\0";
	serverFd = socket(AF_UNIX,SOCK_SEQPACKET,0);
	if(serverFd < 0) {
	return -1;
	}	
	memset(&serv_addr,0x00,sizeof(serv_addr));
	serv_addr.sun_family = AF_UNIX;
	serv_addr.sun_path[0] = 0;
       strcpy(serv_addr.sun_path+1,SOCKET_PATH);
	socklen_t addrlen = sizeof(serv_addr.sun_family) + sizeof(SOCKET_PATH);
       if(bind(serverFd,(struct sockaddr*)&serv_addr,addrlen) < 0) {
              close(serverFd);
              return -1;
       }
	 if(listen(serverFd,LISTEN_MAX_SOCKET_NUM) < 0) {
             close(serverFd);
             return -1;
        }
	  int flags = 0;
	  //获取文件的flags
	  fcntl(serverFd, F_GETFL, &flags);
	  //增加文件的某个flags，比如文件是阻塞的，想设置成非阻塞:
	  fcntl(serverFd, F_SETFL, O_NONBLOCK | flags);
	  client_socket = accept(serverFd,(struct sockaddr*)&client_addr,(socklen_t*)&client_addr_len);
	  if(client_socket > 0){
	   	int flags = 0;
		fcntl(client_socket, F_GETFL,flags);
		fcntl(client_socket, F_SETFL, O_NONBLOCK | flags);
		return client_socket;
	  }
	  return -1;
}

int ServiceSocket::read(char* buf,unsigned int size){
	int ret = -1;
	ret = write(client_socket,buf,size);
	if(ret<0){
		return -1;
	}
	return ret;
}

int ServiceSocket::write(char* buf,unsigned int size){
	int ret = -1;
	ret = write(client_socket,buf,size);
	if(ret<0){
		return -1;
	}
	return ret;
}


	