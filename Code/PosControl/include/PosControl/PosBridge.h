#ifndef POSBRIDGE_H
#define POSBRIDGE_H

#include <ros/ros.h>

#include "coex/coexControl.h"

#include "Adapter/ActionAdapter_Mock.h"
//#include "Adapter/ActionAdapter.h"
#include "StateBuilder.h"


class PosBridge
{
public:
	PosBridge();
	~PosBridge();
	
	void receiveKey(char Key);
	
private:
	ros::NodeHandle nh_;
	ros::Subscriber SubKeys_;
	ros::Subscriber SubPower_;
	
	coexControl coexController_;
	ActionAdapter *ActionAdapter_;
	StateBuilder *StateBuilder_;
};

#endif // POSBRIDGE_H