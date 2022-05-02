#ifndef PARROTIMU_H
#define PARROTIMU_H

#include "DroneController/IMUable.h"

#include <ros/ros.h>
#include <ardrone_autonomy/Navdata.h>
#include <sensor_msgs/Imu.h>

#include "DroneController/PoseBuildable.h"
#include "DroneController/PoseControlable.h"
#include "Adapter/StateBuilder.h"

const int Magic_TakeoffRotorSpeed = 580;
const size_t Magic_Median = 50;
const size_t Magic_Average = 50;
const size_t Magic_OffsetBuffer = 75;

class parrotIMU : public IMUable
{
public:
	parrotIMU(PoseBuildable* PoseBuilder, PoseControlable* PoseController);
	~parrotIMU();
	
	void setFlightState(bool FlightState) override;
	
	IMUState getState() { return this->StateBuilder_.getState(); };

	bool calibrate();
	void safetyTriggered() override;

public:	// for Testing and Evaluation. Usually it's private
	void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr);
	void callbackIMU(const sensor_msgs::Imu::ConstPtr& IMUPtr);
	void publishState();
	void publishPose();

	IMUState getStateOffset() { return this->StateBuilder_.getOffsetState(); };
	Vector3D getPoseOffsetAcceleration() { return this->PoseBuilder_->getOffsetAcceleration(); };

	StateBuilder* getStatebuilder() { return &this->StateBuilder_; };		// delete after testing!!

private:
	ros::NodeHandle nh_;
	ros::Publisher PubStateRaw_;
	ros::Publisher PubState_;
	ros::Publisher PubPose_;
	ros::Subscriber SubIMU_;
	ros::Subscriber SubNav_;

	StateBuilder StateBuilder_;


	size_t MsgCount_;
};

#endif // PARROTIMU_H


