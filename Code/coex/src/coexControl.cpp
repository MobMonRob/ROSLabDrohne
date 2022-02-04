#include "coex/coexControl.h"

#include "coex/coexRC_Transmitter.h"
#include "coex/coexMC.h"


coexControl::coexControl(bool OutRC, int RC_Soft)
	: Joystick_(1027, 2003, 1500,
				1024, 2003, 1500,
				1031, 2003, 1500,
				1024, 2003, 1500),
	Pub_("mavros/setpoint_position/local", 20, 10, true)
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
	
	this->setArmState(false);
	this->setMode("MANUAL");
	
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
		Msg.x = 1500;
		Msg.y = 1500;
		Msg.z = 1000;
		Msg.r = 1500;
	}
	
	return Msg;
};

// Callable
bool coexControl::call(Calling* Caller)
{
	bool ReturnBool = false;
	
	
	if (Caller == this->RC_Receiver_)
	{
		//this->transmit(this->getRC_normalized());
		
		//ROS_INFO("Thrust = %f.", this->getRC_normalized().z);
		
		//Caller::call();
		
		
		//this->transmitAction(0.0, 0.0, 0.08, 0.0);
		
		
		
		// Test
		mavros_msgs::ManualControl ManMsg = this->getRC_normalized();
		geometry_msgs::PoseStamped pose;
		
		
		pose.pose.position.x = 0;
		pose.pose.position.y = 0;
		pose.pose.position.z = ManMsg.z;
		
		this->Pub_.runOnce(pose);
		// Test End
		
		
		
		
		ReturnBool = true;
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





