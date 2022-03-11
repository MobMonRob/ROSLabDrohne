#ifndef PARROTIMU_H
#define PARROTIMU_H

#include "DroneController/IMUable.h"

#include <ros/ros.h>

#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Range.h>
#include <mavros_msgs/ManualControl.h>

#include "Abstraction/Vector3D.h"

#include "parrot/parrotStatus.h"

class parrotIMU : public IMUable
{
public:
	coexOrientation(coexState *State, double Threshold_AccelZ = 0.2);
	~coexOrientation();
	
	double getGroundClearance();
	double getGroundClearance_deangled();
	Vector3D getPosLinear() { return this->Pos_.getVector(); };
	Vector3D getPosAngular() { return this->Ang_.getVector(); };
	Vector3D getSuspentionLinear() { return this->Pos_.getVectorSuspention(); };
	Vector3D getSuspentionAngular() { return this->Ang_.getVectorSuspention(); };
	ros::Time getTime_Imu() const { return this->IMU_.header.stamp;};
	ros::Time getTime_Ground() const { return this->GroundClearance_.header.stamp;};
	
	void cbIMU(const sensor_msgs::Imu::ConstPtr& IMU);
	void cbGroundClearance(const sensor_msgs::Range::ConstPtr& GroundClearance);
	
private:
	Vector3D translate(geometry_msgs::Vector3 In, Unit UnitOut) { return Vector3D(UnitOut, In.x, In.y, In.x); };

private:
	ros::NodeHandle nh_;
	ros::Subscriber SubIMU_;
	ros::Subscriber SubGroundClearance_;
	coexState* State_;
	
	sensor_msgs::Imu IMU_;
	Wrapper3D<AccelToPos> Pos_;
	Wrapper3D<AngVelToAng> Ang_;
	sensor_msgs::Range GroundClearance_;
	
	ros::Time TimeInit_;
	double Threshold_AccelZ_;
};

#endif // PARROTIMU_H


