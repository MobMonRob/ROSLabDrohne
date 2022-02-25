#ifndef MSG_H
#define MSG_H

#include "ros/ros.h"


class Header
{
public:
	ros::Time stamp;



};


class Msg
{
public:
	Msg() : header() {};
	Header header;
};

#endif // MSG_H
