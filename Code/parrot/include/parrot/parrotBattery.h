#ifndef PARROTBATTERY_H
#define PARROTBATTERY_H

#include "DroneController/Batteryable.h"

#include <ros/ros.h>

#include "ardrone_autonomy/Navdata.h"



class parrotBattery : public Batteryable
{
public:
	parrotBattery(double Perc_thershold, double Intervall_Info = 60.0);
	~parrotBattery();

	double getPercentage() override { return this->BatteryState_.batteryPercent; };
	double getTime() { return this->BatteryState_.header.stamp.toSec();};
	
private:
	void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr);

private:
	ros::NodeHandle nh_;
	ros::Subscriber Sub_;
	
	ardrone_autonomy::Navdata BatteryState_;
};

#endif // PARROTBATTERY_H

