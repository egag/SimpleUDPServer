#ifndef _RPC_CLIENT_H_
#define _RPC_CLIENT_H_

#include "RPC.cpp"
#include "service.h"

class RPCClient {
	public:
		RPCClient(char host[], int port);
		~RPCClient();

		int setServer(char host[], int port);

		int cartesianDistance(Point *p1, Point *p2, double *result);
		int midpoint(Point *p1, Point *p2, Point *result);


	private:
		RPC *rpc;
		ClientPacket *serviceRequest;
		MPPacket mpResult;
		DistPacket distResult;
};

#endif // _RPC_CLIENT_H_
