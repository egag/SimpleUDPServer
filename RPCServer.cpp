#ifndef _RPC_SERVER_CPP_
#define _RPC_SERVER_CPP_

#include "RPCServer.h"

using namespace std;

RPCServer::RPCServer(int port) {
	rpc = new RPC(NULL, port);
}
RPCServer::~RPCServer() {
	delete rpc;
}

int RPCServer::waitRecv() {
	// return number of bytes received
	return rpc->recv((void *) bufferIn, MAX_PACKET_SIZE);
}

int RPCServer::process(int sizeRecv) {
	// returns num bytes written to bufferOut, -1 on ignore
        if(sizeRecv < (int) sizeof(int)) {
		cerr << "Server: Ignore request, no transaction id received." << endl;
		return -1;
	}
	ServerPacket *outPacket = (ServerPacket *) bufferOut;
	ClientPacket *inPacket = (ClientPacket *) bufferIn;
	outPacket->transId = inPacket->transId;
	if(sizeRecv != sizeof(struct s_ClientPacket)) {
		outPacket->res = FAILURE;
		cerr << "Server: Ignore request, bad packet size received." << endl;
		return sizeof(struct s_ServerPacket);
	}
	if((inPacket->p1).x < 0 || (inPacket->p2).x < 0) { // ignore request entirely
		cerr << "Server: Ignore request, invalid entries." << endl;
		return -1;
	}
	switch (inPacket->op) {
		case MP :
			return calcMP();
		case DIST :
			return calcDist();
		default :
			outPacket->res = FAILURE;
			cerr << "Server: Incorrect operation specified." << endl;
			return sizeof(struct s_ServerPacket);
	}
}

int RPCServer::reply(int sizeOut) {
	// returns number of bytes sent if over 0 bytes otherwise -1
	if(sizeOut <= 0)
		return -1;
	return rpc->send(bufferOut, sizeOut);
}

int RPCServer::calcMP() {
	ClientPacket *inPacket = (ClientPacket *) bufferIn;
	MPPacket *mpPacket = (MPPacket *) bufferOut;
	if((inPacket->p1).y < 0 || (inPacket->p2).y < 0) {
		mpPacket->res = FAILURE;
		cerr << "Server: Error occured while processing." << endl;
	} else {
		(mpPacket->mp).x = ((inPacket->p1).x + (inPacket->p2).x) / 2;
		(mpPacket->mp).y = ((inPacket->p1).y + (inPacket->p2).y) / 2;
		mpPacket->res = SUCCESS;
	}
	return sizeof(struct s_ServerMPPacket);
}
int RPCServer::calcDist() {
	ClientPacket *inPacket = (ClientPacket *) bufferIn;
	DistPacket *distPacket = (DistPacket *) bufferOut;
	if((inPacket->p1).y < 0 || (inPacket->p2).y < 0) {
		distPacket->res = FAILURE;
		cerr << "Server: Error occured while processing." << endl;
	} else {
		double dX = (inPacket->p1.x - inPacket->p2.x);
		double dY = (inPacket->p1.y - inPacket->p2.y);
		distPacket->dist = sqrt(dX * dX + dY * dY);
		distPacket->res = SUCCESS;
	}
	return sizeof(struct s_ServerDistPacket);
}


#endif // _RPC_SERVER_CPP_
