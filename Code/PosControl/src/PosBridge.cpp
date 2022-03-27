#include <PosControl/PosBridge.h>

#include <iostream>

#include "sensor_msgs/BatteryState.h"



PosBridge::PosBridge()
	: Sub_(nh_.subscribe("KeyReader", 1, &PosBridge::callbackKeys, this)),
	PoseController_(&this->Transmitter_),
	Controller_(&this->PoseBuilder_, &this->PoseController_, &this->Transmitter_)
{
	ROS_INFO("Starting PosBridge...");
	
	//std::cout << "new ActionAdapter" << std::endl;
	//this->ActionAdapter_ = new ActionAdapter(&this->coexController_);
	//std::cout << "new StateBuilder" << std::endl;
	//this->StateBuilder_ = new StateBuilder(&this->coexController_, this->ActionAdapter_);
	//this->coexController_.addCallable(this->StateBuilder_);

	ROS_INFO("Started PosBridge");
}


PosBridge::~PosBridge()
{
	ROS_INFO("Terminating PosBridge...");

	//this->coexController_.deleteCallable(this->StateBuilder_);
	//delete this->StateBuilder_;
	//delete this->ActionAdapter_;

	ROS_INFO("Terminated PosBridge");
}





void PosBridge::printPose()
{
	ROS_INFO(this->PoseBuilder_.getPose().getString().c_str());
}









void PosBridge::callbackKeys(const std_msgs::Char::ConstPtr& msg)
{
	char Key = msg->data;



	/* Key Controls (compare ActionTransmitter::transmitAction()-Methode):
	 * W/S	forward/backward
	 * A/D	left/right
	 * I/K	Up/Down
	 * J/L	Yard left/right
	 */
	
	switch (Key)
	{
	case 'w':
		//this->ActionAdapter_->setPos_Diff(0.01, 0, 0);
		break;
	
	case 's':
		//this->ActionAdapter_->setPos_Diff(-0.01, 0, 0);
		break;
		
	case 'a':
		//this->ActionAdapter_->setPos_Diff(0, 0.01, 0);
		break;
		
	case 'd':
		//this->ActionAdapter_->setPos_Diff(0, -0.01, 0);
		break;
		
	case 'i':
		//this->ActionAdapter_->setPos_Diff(0, 0, 0.01);
		break;
		
	case 'k':
		//this->ActionAdapter_->setPos_Diff(0, 0, -0.01);
		break;
		
	case 'j':
		//this->coexController_.transmitDifference(0, 0, 0, 0.01);		// Yarn is not implemented in ActionAdapter
		break;
		
	case 'l':
		//this->coexController_.transmitDifference(0, 0, 0, -0.01);		// Yarn is not implemented in ActionAdapter
		break;
		
	case 'o':	// Mode Change to "OFFBOARD" (Arm Vehicle)
		//this->coexController_.setMode("OFFBOARD");
		break;

	case 't':	// Takeoff (Arm Vehicle)
		//this->coexController_.setArmState(true);
		break;

	case 'g':	// Ground (Disrm Vehicle)
		//this->coexController_.setMode("MANUAL");
		//this->coexController_.setArmState(false);
		break;
		
	case 'p':	// Info
		//ROS_INFO("LinPos = %s", this->coexController_.getPosLinear().getString().c_str());
		//ROS_INFO("AngPos = %s", this->coexController_.getPosAngular().getString().c_str());
		break;

	case 'q':	// Destructor
		this->~PosBridge();
		break;

	default:
		ROS_INFO("unprocessable Key: %c", Key);
		break;
	}
}


