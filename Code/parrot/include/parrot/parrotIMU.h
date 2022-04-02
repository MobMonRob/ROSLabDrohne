#ifndef PARROTIMU_H
#define PARROTIMU_H

#include "DroneController/IMUable.h"
#include "Domain/SafetyProvider.h"

#include <ros/ros.h>
#include <ardrone_autonomy/Navdata.h>
#include <sensor_msgs/Imu.h>

#include "DroneController/PoseBuildable.h"
#include "DroneController/PoseControlable.h"
#include "Adapter/StateBuilder.h"


class parrotIMU : public IMUable, protected SafetyProvider
{
public:
	parrotIMU(PoseBuildable* PoseBuilder, PoseControlable* PoseController);
	~parrotIMU();
	
	void takeoff() { this->StateBuilder_.setOffsetting(false); };
	void touchdown() { this->StateBuilder_.setOffsetting(true); };

	bool calibrate();

private:
	void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr);
	void callbackIMU(const sensor_msgs::Imu::ConstPtr& IMUPtr);
	void publishPose();

private:
	ros::NodeHandle nh_;
	ros::Publisher PubPose_;
	ros::Subscriber SubIMU_;
	ros::Subscriber SubNav_;

	StateBuilder StateBuilder_;
};

#endif // PARROTIMU_H


