#ifndef POSBRIDGE_H
#define POSBRIDGE_H

#include <ros/ros.h>

#include <std_msgs/Char.h>

#include "parrot/parrotControl.h"
#include "parrot/parrotTransmitter.h"
#include "Controller/PoseController.h"

#include "PosControl/PoseBuilder.h"
#include "PosControl/Transmitter_Mock.h"

class PosBridge
{
public:
	PosBridge();
	~PosBridge();
	

	void printPose();




private:
	void callbackKeys(const std_msgs::Char::ConstPtr& msg);

private:
	ros::NodeHandle nh_;
	ros::Subscriber Sub_;
	
	PoseBuilder PoseBuilder_;
	PoseController PoseController_;
	Transmitter_Mock Transmitter_;
	parrotControl Controller_;
};

#endif // POSBRIDGE_H
