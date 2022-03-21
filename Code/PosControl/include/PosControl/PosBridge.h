#ifndef POSBRIDGE_H
#define POSBRIDGE_H

#include <ros/ros.h>

#include "parrot/parrotControl.h"
#include "parrot/parrotTransmitter.h"
#include "PosControl/PoseBuilder.h"
#include "Controller/PoseController.h"

//#include "Adapter/ActionAdapter_Mock.h"
//#include "Adapter/ActionAdapter.h"
//#include "Application/StateBuilder.h"


class PosBridge
{
public:
	PosBridge();
	~PosBridge();
	


private:
	void callbackKeys(const std_msgs::Char::ConstPtr& msg);

private:
	ros::NodeHandle nh_;
	ros::Subscriber Sub_;
	
	PoseBuilder PoseBuilder_;
	PoseController PoseController_;
	parrotTransmitter Transmitter_;
	parrotControl Controller_;
};

#endif // POSBRIDGE_H
