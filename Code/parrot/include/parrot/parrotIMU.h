#ifndef PARROTIMU_H
#define PARROTIMU_H

#include "DroneController/IMUable.h"
#include "Abstraction/SafetyProvider.h"

#include <ros/ros.h>

#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Range.h>
#include <mavros_msgs/ManualControl.h>

#include "Abstraction/Vector3D.h"

#include "parrot/parrotStatus.h"

class parrotIMU : public IMUable, protected SafetyProvider
{
public:
	parrotIMU(PoseBuildable* PoseBuilder, PoseControlable* PoseController, Statusable *Status);
	~parrotIMU();
	
private:
	void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr);

private:
	ros::NodeHandle nh_;
	ros::Subscriber Sub_;
};

#endif // PARROTIMU_H


