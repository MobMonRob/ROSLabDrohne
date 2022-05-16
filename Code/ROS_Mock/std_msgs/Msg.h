#ifndef MSG_H
#define MSG_H

#include "../ros/rosTiming.h"


class Header
{
public:
	ros::Time stamp;
};


class Msg
{
public:
	Msg() {};
	Header header;
};

#endif // MSG_H
