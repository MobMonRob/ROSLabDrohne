#ifndef COEXBATTERY_H
#define COEXBATTERY_H

#include <ros/ros.h>

#include <sensor_msgs/BatteryState.h>

#include "calling/Caller.h"


class coexBattery : public Caller
{
public:
	coexBattery(double Thershold_Warning = 15.0, double Intervall_Info = 60.0);
	~coexBattery();

	double getVoltage();
	double getPercentage();
	double getTime() { return this->Battery_.header.stamp.toSec();};
	
	void cbBattery(const sensor_msgs::BatteryState::ConstPtr& Battery);
	
private:
	ros::NodeHandle nh_;
	ros::Subscriber SubBattery_;
	
	double Thershold_Warning_;
	ros::Duration Intervall_Info_;
	
	sensor_msgs::BatteryState Battery_;
};

#endif // COEXBATTERY_H


