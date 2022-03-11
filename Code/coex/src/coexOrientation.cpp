#include "coex/coexOrientation.h"


coexOrientation *coex_Orientation = nullptr;



void callbackIMU(const sensor_msgs::Imu::ConstPtr& msg)
{
	if (coex_Orientation != nullptr)
	{
		coex_Orientation->cbIMU(msg);
	}
}

void callbackGround(const sensor_msgs::Range::ConstPtr& msg)
{
	if (coex_Orientation != nullptr)
	{
		coex_Orientation->cbGroundClearance(msg);
	}
}



coexOrientation::coexOrientation(coexState* State, double Threshold_AccelZ)
	: Pos_(Unit_Acceleration, Unit_Velocity, Unit_Length),
	Ang_(Unit_AngleVelDeg, Unit_AngleDeg),
	State_(State),
	Threshold_AccelZ_(Threshold_AccelZ)
{
	ROS_INFO("Starting coexOrientation...");
	ros::spinOnce();
	
	coex_Orientation = this;
	
	this->SubIMU_ = this->nh_.subscribe("mavros/imu/data", 1, callbackIMU);
	this->SubGroundClearance_ = this->nh_.subscribe("rangefinder/range", 1, callbackGround);


	if (coex_Orientation != this)
	{
		ROS_WARN("Instance of coexOrientation is not set as global Instance!");
	}

	ROS_INFO("Started coexOrientation");
}

coexOrientation::~coexOrientation()
{
	ROS_INFO("Termintated coexOrientation");
}


double coexOrientation::getGroundClearance()
{
	double ReturnValue = this->GroundClearance_.range;
	
	
	if (ReturnValue < this->GroundClearance_.min_range)
	{
		ReturnValue = this->GroundClearance_.min_range;
	}
	
	if (ReturnValue > this->GroundClearance_.max_range)
	{
		ReturnValue = this->GroundClearance_.max_range;
	}
	
	return ReturnValue;
}

/* Calculates Ground Clearance according to the Angle of the Vehicle.
 * ATTENTION: There might be a Missassumption due to Dips.
 */
double coexOrientation::getGroundClearance_deangled()
{
	
	
	// TODO
	
	
	
	return this->getGroundClearance();
}


void coexOrientation::cbIMU(const sensor_msgs::Imu::ConstPtr& IMU)
{
	/*
	this->Pos_.setLock(!this->State_->getArmState());
	this->Ang_.setLock(!this->State_->getArmState());

	this->Pos_.setInput(this->translate(IMU->linear_acceleration, Unit_Acceleration), Timestamp(IMU->header.stamp.toSec()));
	this->Ang_.setInput(this->translate(IMU->angular_velocity, Unit_AngleVelDeg), Timestamp(IMU->header.stamp.toSec()));
	*/

	this->call();
}

void coexOrientation::cbGroundClearance(const sensor_msgs::Range::ConstPtr& GroundClearance)
{
	this->GroundClearance_ = *GroundClearance;
	
	this->call();
}


