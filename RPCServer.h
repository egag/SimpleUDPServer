#ifndef _RPC_SERVER_H_
#define _RPC_SERVER_H_

#include "service.h"
#include "RPC.cpp"
#include <math.h>

class RPCServer {
	public:
		RPCServer(int port);
		~RPCServer();

		int waitRecv();
		int process(int sizeRecv);
		int reply(int sizeOut);

	private:
		RPC *rpc;
		char bufferIn[MAX_PACKET_SIZE];
		char bufferOut[MAX_PACKET_SIZE];

		int calcMP();
		int calcDist();
};

#endif // _RPC_SERVER_H_
