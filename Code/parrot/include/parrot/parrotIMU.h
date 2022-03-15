#ifndef PARROTIMU_H
#define PARROTIMU_H

#include <ros/ros.h>

#include <ardrone_autonomy/Navdata.h>

#include "DroneController/IMUable.h"
#include "Abstraction/SafetyProvider.h"


class parrotIMU : public IMUable, protected SafetyProvider
{
public:
	parrotIMU(PoseBuildable* PoseBuilder, PoseControlable* PoseController);
	~parrotIMU();
	
private:
	void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr);

private:
	ros::NodeHandle nh_;
	ros::Subscriber Sub_;
};

#endif // PARROTIMU_H


