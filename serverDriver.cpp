#include "RPCServer.cpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	if(argc < 2) {
		cerr << "Must include a port number. Use \"./RPCServer port#\"" << endl;
		return -1;
	}
	RPCServer server(atoi(argv[1]));
	while(true) {
		int sizeIn = server.waitRecv();
		cout << "Recieved " << sizeIn << " bytes." << endl;
		int sizeOut = server.process(sizeIn);
		if(server.reply(sizeOut) != sizeOut)
			cerr << "Incorrect number of bytes sent." << endl;
	}
	return 0;
}