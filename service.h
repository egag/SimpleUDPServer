#ifndef _SERVICE_H_
#define _SERVICE_H_

#include "point.h"

#define MAX_PACKET_SIZE 100

enum Operation : int { MP , DIST};
enum Result : int { FAILURE = -1, SUCCESS = 0};

typedef struct s_Packet {
	int transId;
	} Packet;

typedef struct s_ClientPacket : public Packet {
	Operation op;
	Point p1;
	Point p2;
} ClientPacket;

typedef struct s_ServerPacket : public Packet {
	Result res;
} ServerPacket;

typedef struct s_ServerMPPacket : public ServerPacket {
	Point mp;
} MPPacket;

typedef struct s_ServerDistPacket : public ServerPacket {
	double dist;
	} DistPacket;

#endif // _SERVICE_H_
