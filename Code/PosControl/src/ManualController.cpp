
#include <iostream>
#include <ros/ros.h>

#include <std_msgs/Char.h>

#include "parrot/parrotTransmitter.h"









parrotStatus* StateController_;
ros::Time SmoothTime;
double Roll = 0.0;
double Pitch = 0.0;
double Yarn = 0.0;
double Thrust = 0.0;
double Height = 0.0;
bool dirty = false;


void callbackKeys(const std_msgs::Char::ConstPtr& msg)
{
	char Key = msg->data;



	/* 
	 * https://ardrone-autonomy.readthedocs.io/en/latest/commands.html
	 */

	switch (Key)
	{
	case 'w':
		Pitch += 0.1;
		break;

	case 's':
		Pitch -= 0.1;
		dirty = true;
		break;

	case 'a':
		Roll += 0.1;
		break;

	case 'd':
		Roll -= 0.1;
		break;

	case 'i':
		Height += 0.025;
		break;

	case 'k':
		Height -= 0.1;
		break;

	case 'j':
		Yarn += 0.1;
		break;

	case 'l':
		Yarn -= 0.1;
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



	Roll = (Roll > 1) ? 1 : ((Roll < -1) ? -1 : Roll);
	Pitch = (Pitch > 1) ? 1 : ((Pitch < -1) ? -1 : Pitch);
	Yarn = (Yarn > 1) ? 1 : ((Yarn < -1) ? -1 : Yarn);
	Thrust = (Thrust > 1) ? 1 : ((Thrust < -1) ? -1 : Thrust);

	dirty = true;

	SmoothTime = ros::Time::now();
}







int main(int argc, char** argv)
{
	ROS_INFO("Started New Node: ManualController");

	ros::init(argc, argv, "ManualController");
	ros::NodeHandle nh_;
	ros::Subscriber Sub_(nh_.subscribe("KeyReader", 1, callbackKeys));

	parrotBattery Battery(20.0);
	parrotTransmitter Transmitter_;
	StateController_ = new parrotStatus();

	const double SmoothFactor = 0.875;
	ros::Duration SmoothDuration(0.1);
	ros::Time InfoTime = ros::Time::now();
	ros::Duration InfoDuration(1);
	ros::Rate SpinRate(200);

	while (ros::ok())
	{
		if (ros::Time::now() - SmoothTime > SmoothDuration)
		{
			Roll *= SmoothFactor;
			Pitch *= SmoothFactor;
			Yarn *= SmoothFactor;
			Thrust *= SmoothFactor;

			dirty = true;

			SmoothTime = ros::Time::now();
		}

		dirty = ros::Time::now() - InfoTime > InfoDuration;

		if (dirty)
		{
			ROS_INFO("Transmit: r %f, p %f, y %f, t %f.", Roll, Pitch, Yarn, Thrust);

			dirty = false;
			InfoTime = ros::Time::now();
		}

		Transmitter_.transmitAction(Roll, Pitch, Yarn, Thrust);
		ros::spinOnce();
		SpinRate.sleep();
	}



	StateController_->setArmState(false);

	delete StateController_;

	ROS_INFO("Terminated Node: ManualController");

	return 0;
}



