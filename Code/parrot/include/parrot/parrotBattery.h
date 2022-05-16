#ifndef PARROTBATTERY_H
#define PARROTBATTERY_H

#include "DroneController/Batteryable.h"

#include <ros/ros.h>

#include "ardrone_autonomy/Navdata.h"


class parrotBattery : public Batteryable
{
public:
	parrotBattery(double PercentageThershold, double InfoIntervall = 60.0);
	~parrotBattery();

	double getPercentage() override { return this->Percentage_; };
	
private:
	void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr);

private:
	ros::NodeHandle nh_;
	ros::Subscriber Sub_;
	
	ros::Time InfoTime_;
	ros::Duration InfoDuration_;
	double Percentage_;
};

#endif // PARROTBATTERY_H

