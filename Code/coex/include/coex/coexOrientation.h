#ifndef COEXORIENTATION_H
#define COEXORIENTATION_H

#include <ros/ros.h>

#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Range.h>

#include <mavros_msgs/ManualControl.h>

#include "calling/Caller.h"


class coexOrientation : public Caller
{
public:
	coexOrientation(double Threshold_AccelZ = 0.2);
	
	double getGroundClearance();
	double getGroundClearance_deangled();
	mavros_msgs::ManualControl getPosition();
	double getTime_Imu() { return this->IMU_.header.stamp.toSec();};
	double getTime_Ground() { return this->GroundClearance_.header.stamp.toSec();};
	
	void cbIMU(const sensor_msgs::Imu::ConstPtr& IMU);
	void cbGroundClearance(const sensor_msgs::Range::ConstPtr& GroundClearance);
	
private:
	ros::NodeHandle nh_;
	ros::Subscriber SubIMU_;
	ros::Subscriber SubGroundClearance_;
	
	sensor_msgs::Imu IMU_;
	sensor_msgs::Range GroundClearance_;
	
	
	ros::Time TimeInit_;
	// include Accel->Vel, Vel->Pos, angleVel->Angle... Instead of IMU_
	double Threshold_AccelZ_;
};

#endif // COEXORIENTATION_H


