#ifndef PARROTIMU_H
#define PARROTIMU_H

#include "DroneController/IMUable.h"
#include "Abstraction/SafetyProvider.h"

#include <ros/ros.h>
#include <ardrone_autonomy/Navdata.h>
#include <sensor_msgs/Imu.h>

#include "DroneController/PoseControlable.h"
#include "Adapter/StateBuilder.h"
#include "Adapter/PoseBuilder.h"


class parrotIMU : public IMUable, protected SafetyProvider
{
public:
	parrotIMU(PoseControlable* PoseController);
	~parrotIMU();
	
	void takeoff() { this->StateBuilder_.setNullPoint(); };
	void touchdown() { this->reset(); };

private:
	void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr);
	void callbackIMU(const sensor_msgs::Imu::ConstPtr& IMUPtr);

private:
	ros::NodeHandle nh_;
	ros::Subscriber SubIMU_;
	ros::Subscriber SubNav_;

	StateBuilder StateBuilder_;
	PoseBuilder PoseBuilder_;
};

#endif // PARROTIMU_H


