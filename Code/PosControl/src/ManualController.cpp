
#include <iostream>
#include <ros/ros.h>

#include <std_msgs/Char.h>

#include "parrot/parrotTransmitter.h"








parrotTransmitter* Transmitter_;
parrotStatus* StateController_;
double Roll = 0.0;
double Pitch = 0.0;
double Yarn = 0.0;
double Thrust = 0.0;


void callbackKeys(const std_msgs::Char::ConstPtr& msg)
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
		Pitch += 0.01;
		break;
	
	case 's':
		Pitch -= 0.01;
		break;
		
	case 'a':
		Roll += 0.01;
		break;
		
	case 'd':
		Roll -= 0.01;
		break;
		
	case 'i':
		Thrust += 0.01;
		break;
		
	case 'k':
		Thrust -= 0.01;
		break;
		
	case 'j':
		Yarn += 0.01;
		break;
		
	case 'l':
		Yarn -= 0.01;
		break;

	case 't':	// Takeoff (Arm Vehicle)
		StateController_->setArmState(true);
		break;

	case 'g':	// Ground (Disrm Vehicle)
		StateController_->setArmState(false);
		break;
		
	case 'p':	// Info
		//ROS_INFO("LinPos = %s", this->coexController_.getPosLinear().getString().c_str());
		//ROS_INFO("AngPos = %s", this->coexController_.getPosAngular().getString().c_str());
		break;


	case 'r':
		ROS_INFO("Reset Controller");
		StateController_->resetStatus();
		break;

	case 'q':	// Destructor
		break;

	default:
		ROS_INFO("unprocessable Key: %c", Key);
		break;
	}

	Transmitter_->transmitAction(Roll, Pitch, Yarn, Thrust);
}







int main(int argc, char** argv)
{
	ROS_INFO("Started New Node: ManualController");

	ros::init(argc, argv, "Bridge");
	ros::NodeHandle nh_;
	ros::Subscriber Sub_(nh_.subscribe("KeyReader", 1, callbackKeys));

	parrotBattery Battery(20.0);
	Transmitter_ = new parrotTransmitter();
	StateController_ = new parrotStatus(&Battery);


	while (ros::ok())
	{
		ros::spinOnce();
	}


	delete Transmitter_;
	delete StateController_;

	ROS_INFO("Terminated Node: ManualController");

	return 0;
}


