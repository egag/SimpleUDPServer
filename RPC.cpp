#ifndef _RPC_CPP_
#define _RPC_CPP_

#include "RPC.h"

// using namespace std;

RPC::RPC(char host[], int port) {
	if(host == NULL) {
		// is server
		getSocket(port);
		bzero(&commAddr, sizeof(struct sockaddr_in));
	} else {
		// is client
		getSocket(0);
		setServer(host, port);
	}
}

RPC::~RPC() {
	if(socketD != NULL_SD)
		close(socketD);
}

int RPC::setServer(char host[], int port) {
	bzero(&commAddr, sizeof(struct sockaddr_in));
	commAddr.sin_family = AF_INET; 
	commAddr.sin_addr.s_addr = inet_addr(host);
	commAddr.sin_port = htons (port);
	return 0;
}

int RPC::getSocket(int port) {
	// binds the rpc instance to a specific port and address
	// pass port in as 0 to choose available port
	socketD = socket( PF_INET, SOCK_DGRAM, 0);
	if( socketD < 0) {
		perror("socket");
		return NULL_SD;
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET; 
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons (port);
	struct timeval tv;
	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;
	if(!port &&
		setsockopt(socketD, SOL_SOCKET, SO_RCVTIMEO, (void *) &tv, sizeof(struct timeval)) < 0) {
		// port == 0 means client socket so set timeout
		perror("setsockopt");
		close(socketD);
		return NULL_SD;
	}
	if(port && bind( socketD, ( struct sockaddr * )&addr, sizeof( addr )) < 0) {
			perror("bind");
			close(socketD);
			return NULL_SD;
	}
	return socketD;
}

int RPC::recv(void *buf, int size) {
	// called directly by server and through sendAndRecv by client
	bzero(buf, size);
	int sizeRecv;
	socklen_t commLen = sizeof(struct sockaddr);
	// sets commAddr to sender of packet
	if((sizeRecv  = recvfrom(socketD, buf, size, 0, (struct sockaddr*) &commAddr, &commLen)) < 0)
		perror("recvfrom");

	return sizeRecv;
}

int RPC::send(void *buf, int size) {
	// called directly by server and through sendAndRecv by client
	// sends to commAddr, server must call this after recv
	if(sendto(socketD, buf, size, 0, (struct sockaddr*) &commAddr, sizeof(struct sockaddr)) < 0)
		perror("sendto");
	return size;
}

int RPC::sendAndRecv(void *bufOut, void *bufIn, int *transId, int bufSize, int sizeExp) {
	// called directly by client, must have commAddr set
  int *bufInInt = (int *) bufIn, *id = (int *) bufOut, sizeRecv = 0; // easy access to returned values
	for(int tries = RETRY; tries > 0; tries--, (*id)++) {        // increment transaction each time
		if (send(bufOut, bufSize) != bufSize)
			continue;                                           // need to resend
		sizeRecv = recv(bufIn, bufSize);
		if(sizeRecv != sizeExp)
			continue;
		else if(bufInInt[0] == *id && bufInInt[1] == 0)
			return sizeRecv;
		else if(bufInInt[0] != *id)
			std::cerr << "Recieved incorrect transaction" << std::endl; 
		else
			std::cerr << "Server error" << std::endl;
	}
	std::cerr << "sendAndRecv: Timed out" << std::endl;
	return -1;
}

#endif // _RPC_CPP_
