#ifndef PARROTBATTERY_H
#define PARROTBATTERY_H

#include "DroneController/Batteryable.h"

#include <ros/ros.h>

#include <sensor_msgs/BatteryState.h>



class parrotBattery : public Batteryable
{
public:
	coexBattery(double Perc_thershold, double Intervall_Info = 60.0);
	coexBattery(double V_min, double V_max, double V_thershold, double Intervall_Info = 60.0);
	~coexBattery();

	double getVoltage() const;
	double getPercentage() const;
	bool getPercentageLow() const { return (this->getPercentage() <= this->Thershold_Warning_); };
	int getHealthID() const { return this->Battery_.power_supply_health; };
	std::string getHealth();
	std::string getHealth(int HealthID);
	double getTime() { return this->Battery_.header.stamp.toSec();};
	
	void cbBattery(const sensor_msgs::BatteryState::ConstPtr& Battery);
	
private:
	void initHealth();

private:
	ros::NodeHandle nh_;
	ros::Subscriber SubBattery_;
	
	double Thershold_Warning_;
	ros::Duration Intervall_Info_;
	
	sensor_msgs::BatteryState Battery_;
	std::map<int, std::string> Health_;
};

#endif // PARROTBATTERY_H

