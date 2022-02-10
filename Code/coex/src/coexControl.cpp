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
	this->Battery_ = new coexBattery(15.6, 16.8, 15.7);
	this->Battery_->addCallable(this);

	this->State_ = new coexState(this->Battery_);
	this->State_->addCallable(this);
	
	this->Orientation_ = new coexOrientation(this->State_, 1.0);
	this->Orientation_->addCallable(this);
	
	this->RC_Receiver_ = new coexRC_Receiver(&this->Joystick_);
	this->RC_Receiver_->addCallable(this);
	this->RC_Soft_ = RC_Soft;
	
	if (OutRC)
	{
		this->xC_ = new coexRC_Transmitter(this->State_, &this->Joystick_);
	}
	else
	{
		this->xC_ = new coexMC(this->State_);
	}
}

coexControl::~coexControl()
{
	ROS_INFO("Terminating coexControl...");

	this->setArmState(false);
	this->setMode("MANUAL");

	delete this->xC_;
	this->xC_ = nullptr;
	delete this->Orientation_;
	this->Orientation_ = nullptr;
	delete this->Battery_;
	this->Battery_ = nullptr;
	delete this->State_;
	this->State_ = nullptr;
	
	ROS_INFO("Terminated coexControl");
}


mavros_msgs::ManualControl coexControl::getRC_normalized()
{
	mavros_msgs::ManualControl Msg;
	
	
	if (this->RC_Receiver_ != nullptr)
	{
		Msg = this->RC_Receiver_->getCtrMsg_normalized();
		
		Msg.x /= this->RC_Soft_;
		Msg.y /= this->RC_Soft_;
		Msg.z /= this->RC_Soft_;
		Msg.r /= this->RC_Soft_;
	}
	else
	{
		Msg.x = 0;
		Msg.y = 0;
		Msg.z = 0;
		Msg.r = 0;
	}
	
	return Msg;
};

// Callable
bool coexControl::call(Calling* Caller)
{
	bool ReturnBool = false;
	

	if (this->CounterIdle_ < this->CounterOverflow_)
	{
		this->CounterIdle_++;
	}
	else
	{
		if (Caller == this->Orientation_)
		{
			Caller::call();

			ReturnBool = true;
		}
		else if (Caller == this->RC_Receiver_)
		{
			mavros_msgs::ManualControl Msg = this->getRC_normalized();

			ROS_INFO("Thrust = %f.", Msg.z);

			ReturnBool = true;
		}
		else if (Caller == this->State_)
		{
		}
		else if (Caller == this->Battery_)
		{
		}
	}
	
	
	return ReturnBool;
}



void coexControl::transmit(mavros_msgs::ManualControl Msg)
{
	if (this->xC_ != nullptr)
	{
		this->xC_->transmitAction(Msg);
	}
}





void coexControl::landing()
{

}





