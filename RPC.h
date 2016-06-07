#ifndef _RPC_H_
#define _RPC_H_

#include <iostream>          // cerr
#include <stdlib.h>          // exit
#include <unistd.h>          // close
#include <stdio.h>           // perror
#include <sys/types.h>       // socket
#include <sys/socket.h>      // socket
#include <netinet/in.h>      // inet_addr
#include <arpa/inet.h>       // inet_addr
#include <strings.h>         // bzero, strncpy
#include <string.h>          // strlen, strncpy

#define TIMEOUT 5
#define RETRY 3

#define NULL_SD -1

// using namespace std;

class RPC {
	public:
		RPC(char host[], int port);
		~RPC();
		int setServer(char host[], int port);
		int getSocket(int port);
		int send(void *buf, int size);
		int recv(void *buf, int size);
		int sendAndRecv(void *bufOut, void 	*bufIn, int *transId, int bufSize, int sizeExp);

	private:
		int socketD;
		sockaddr_in commAddr;
};

#endif // _RPC_H_
