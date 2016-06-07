#ifndef _RPC_CLIENT_CPP_
#define _RPC_CLIENT_CPP_

#include "RPCClient.h"

RPCClient::RPCClient(char host[], int port) {
	rpc = new RPC(host, port);
	serviceRequest = new ClientPacket;
}

RPCClient::~RPCClient() {
	delete rpc;
	delete serviceRequest;
}

int RPCClient::setServer(char host[], int port) {
	return rpc->setServer(host, port);
}

int RPCClient::cartesianDistance(Point *p1, Point *p2, double* result) {
	serviceRequest->transId = 35;
	serviceRequest->op = DIST;
	serviceRequest->p1 = *p1;
	serviceRequest->p2 = *p2;
	int sizeRecv = rpc->sendAndRecv((void *) serviceRequest, (void *) &distResult,
		&serviceRequest->transId, sizeof(s_ClientPacket), sizeof(s_ServerDistPacket));
	if(sizeRecv != sizeof(s_ServerDistPacket))
		return -1;
	*result = distResult.dist;
	return 0;
}
int RPCClient::midpoint(Point *p1, Point *p2, Point* result) {
	serviceRequest->transId = 49;
	serviceRequest->op = MP;
	serviceRequest->p1 = *p1;
	serviceRequest->p2 = *p2;
	int sizeRecv = rpc->sendAndRecv((void *) serviceRequest, (void *) &mpResult,
		&serviceRequest->transId, sizeof(s_ClientPacket), sizeof(s_ServerMPPacket));
	if(sizeRecv != sizeof(s_ServerMPPacket))
		return -1;
	*result = mpResult.mp;
	return 0;
}

#endif // _RPC_CLIENT_H_
