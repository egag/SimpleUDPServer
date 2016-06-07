#include "RPCClient.cpp"
#include "point.h"
#include <iostream>

using namespace std;

ostream &operator<<(ostream &out, Point pt);

int main(int argc, char *argv[]) {
	if(argc < 3) {
		cerr << "Must include a port number. Use \"./RPCServer host_addr port#\"" << endl;
		return -1;
	}
	RPCClient client(argv[1], atoi(argv[2]));
	cout << "P1\t\tP2\t\tDistance\tMidpoint" << endl;
	double distResult;
	Point p1, p2, mpResult;
	while(true) {
		cin >> p1.x >> p1.y;
		cin >> p2.x >> p2.y;
		cout << p1 << "\t\t" << p2 << "\t\t" << flush;
		if(client.cartesianDistance(&p1, &p2, &distResult) == 0)
			cout << distResult << "\t\t";
		else
			cout << "ERR" << "\t\t";
		if(client.midpoint(&p1, &p2, &mpResult) == 0)
			cout << mpResult << endl;
		else
			cout << "ERR" << endl;
	}
	return 0;
}

ostream &operator<<(ostream &out, Point pt) {
	out << "(" << pt.x << "," << pt.y << ")";
	return out;
}
