#include "coex/coexControl.h"

#include "coex/coexRC_Transmitter.h"
#include "coex/coexMC.h"


coexControl::coexControl(bool OutRC, int RC_Soft)
	: Joystick_(1027, 2003, 1500,
				1024, 2003, 1500,
				1031, 2003, 1500,
				1024, 2003, 1500)
{
	ROS_INFO("Started coexControl");
	
	/* Parameters:
	 * 
	 * 
	 */
	
	this->State_ = new coexState();
	this->State_->addCallable(this);
	
	this->Battery_ = new coexBattery();
	this->Battery_->addCallable(this);
	
	this->Orientation_ = new coexOrientation(1.0);
	this->Orientation_->addCallable(this);
	
	this->RC_Receiver_ = new coexRC_Receiver(&this->Joystick_);
	this->RC_Receiver_->addCallable(this);
	this->RC_Soft_ = RC_Soft;
	
	if (OutRC)
	{
		this->xC_ = new coexRC_Transmitter(&this->Joystick_, this->State_, this->Battery_);
	}
	else
	{
		this->xC_ = new coexMC(this->State_, this->Battery_);
	}
}

coexControl::~coexControl()
{
	delete this->xC_;
	delete this->Orientation_;
	delete this->Battery_;
	delete this->State_;
	
	ROS_INFO("Terminated coexControl");
}


mavros_msgs::ManualControl coexControl::getRC_normalized()
{
	mavros_msgs::ManualControl Msg = this->RC_Receiver_->getCtrMsg_normalized();
	
	
	Msg.x /= this->RC_Soft_;
	Msg.y /= this->RC_Soft_;
	Msg.z /= this->RC_Soft_;
	Msg.r /= this->RC_Soft_;
	
	return Msg;
};

// Callable
bool coexControl::call(Calling* Caller)
{
	bool ReturnBool = false;
	
	
	if (Caller == this->RC_Receiver_)
	{
		this->transmit(this->getRC_normalized());
		
		ROS_INFO("Thrust = %f.", this->getRC_normalized().z);
		
		ReturnBool = true;
	}
	
	return ReturnBool;
}




