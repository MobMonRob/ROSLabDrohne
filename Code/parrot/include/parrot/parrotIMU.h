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
	
	void setFlightState(bool FlightState) override { this->StateBuilder_.setOffsetting(!FlightState); };
	
	IMUState getState() { return this->StateBuilder_.getState(); };

	bool calibrate();

public:	// for Testing and Evaluation. Usually it's private
	void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr);
	void callbackIMU(const sensor_msgs::Imu::ConstPtr& IMUPtr);
	void publishState();
	void publishPose();

	
	IMUState getStateOffset() { return this->StateBuilder_.getOffsetState(); };

private:
	ros::NodeHandle nh_;
	ros::Publisher PubStateRaw_;
	ros::Publisher PubState_;
	ros::Publisher PubPose_;
	ros::Subscriber SubIMU_;
	ros::Subscriber SubNav_;

	StateBuilder StateBuilder_;
	bool ValidData_;
};

#endif // PARROTIMU_H


