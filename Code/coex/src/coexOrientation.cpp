#include "coex/coexOrientation.h"


coexOrientation *coex_Orientation = nullptr;



void callbackIMU(const sensor_msgs::Imu::ConstPtr& msg)
{
	if (coex_Orientation != nullptr)
	{
		coex_Orientation->cbIMU(msg);
	}
}

void callbackGroundClearance(const sensor_msgs::Range::ConstPtr& msg)
{
	if (coex_Orientation != nullptr)
	{
		coex_Orientation->cbGroundClearance(msg);
	}
}



coexOrientation::coexOrientation(coexState* State, double Threshold_AccelZ)
	: Pos_(Unit_Acceleration, Unit_Length),
	Ang_(Unit_AngleVelDeg, Unit_AngleDeg),
	State_(State)
{
	ROS_INFO("Started coexOrientation");
	
	coex_Orientation = this;
	
	this->Threshold_AccelZ_ = Threshold_AccelZ;
	
	this->SubIMU_ = this->nh_.subscribe("mavros/imu/data", 100, callbackIMU);
	this->SubGroundClearance_ = this->nh_.subscribe("rangefinder/range", 10, callbackGroundClearance);
}

coexOrientation::~coexOrientation()
{
	ROS_INFO("Termintating coexOrientation...");
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
	this->Pos_.setLock(!this->State_->getArmState());
	this->Ang_.setLock(!this->State_->getArmState());

	this->Pos_.setInput(this->translate(IMU->linear_acceleration, Unit_Acceleration), IMU->header.stamp.toSec());
	this->Ang_.setInput(this->translate(IMU->angular_velocity, Unit_AngleVelDeg), IMU->header.stamp.toSec());

	this->call();
}

void coexOrientation::cbGroundClearance(const sensor_msgs::Range::ConstPtr& GroundClearance)
{
	this->GroundClearance_ = *GroundClearance;
	
	this->call();
}


