#ifndef PARROTSTATUS_H
#define PARROTSTATUS_H

#include "DroneController/Statusable.h"

#include <ros/ros.h>

#include <string>
#include <map>

#include <mavros_msgs/State.h>
#include <mavros_msgs/SetMode.h>
#include "ardrone_autonomy/Navdata.h"

#include "parrot/parrotBattery.h"


class parrotStatus : public Statusable
{
public:
	parrotStatus(parrotBattery* Battery);
	~parrotStatus();
	


	Timestamp getTime() override { return Timestamp();};
	
	
private:
	void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr);


private:
	ros::NodeHandle nh_;
	ros::Subscriber Sub_;

	long Status_;
};

#endif // PARROTSTATUS_H

