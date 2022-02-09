#ifndef COEXBATTERY_H
#define COEXBATTERY_H

#include <ros/ros.h>

#include <sensor_msgs/BatteryState.h>

#include "calling/Caller.h"


class coexBattery : public Caller
{
public:
	coexBattery(double Perc_thershold, double Intervall_Info = 60.0);
	coexBattery(double V_min, double V_max, double V_thershold, double Intervall_Info = 60.0);
	~coexBattery();

	const double getVoltage();
	const double getPercentage();
	const bool getPercentageLow() { return (this->Battery_.percentage <= this->Thershold_Warning_); };
	const double getTime() { return this->Battery_.header.stamp.toSec();};
	
	void cbBattery(const sensor_msgs::BatteryState::ConstPtr& Battery);
	
private:
	ros::NodeHandle nh_;
	ros::Subscriber SubBattery_;
	
	double Thershold_Warning_;
	ros::Duration Intervall_Info_;
	
	sensor_msgs::BatteryState Battery_;
};

#endif // COEXBATTERY_H


