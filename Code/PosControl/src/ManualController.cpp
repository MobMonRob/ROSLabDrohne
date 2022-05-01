
#include <iostream>
#include <ros/ros.h>

#include <std_msgs/Char.h>

#include "parrot/parrotIMU.h"
#include "parrot/parrotTransmitter.h"


#include "Controller/PoseController.h"
#include "PosControl/PoseBuilder.h"








parrotStatus* StateController_;
ros::Time SmoothTime;
double Roll = 0.0;
double Pitch = 0.0;
double Yarn = 0.0;
double Thrust = 0.0;
double HeightSet = 0.5;
double HeightIs = 0.0;
bool dirty = false;


ros::Time NavData_Time;
double Thrust_kP = 1.0;
double Thrust_kI = 0.7;
double Thrust_SumI = 0.0;




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
		HeightSet += 0.01;
		break;

	case 'k':
		HeightSet -= 0.05;
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

void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr)
{
	ros::Time MessageTime = navdataPtr->header.stamp;


	HeightIs = static_cast<double>(navdataPtr->altd)/1000.0f;

	if (HeightIs > 0)
	{
		double HeightError = HeightSet - HeightIs;


		Thrust_SumI += Thrust_kI * HeightError * (MessageTime - NavData_Time).toSec();
		Thrust = Thrust_kP * HeightError + Thrust_SumI;
	}

	NavData_Time = MessageTime;
}





int main(int argc, char** argv)
{
	ROS_INFO("Started New Node: ManualController");

	ros::init(argc, argv, "ManualController");
	ros::NodeHandle nh_;
	ros::Subscriber Sub_(nh_.subscribe("KeyReader", 1, callbackKeys));
	ros::Subscriber SubIMU_(nh_.subscribe("ardrone/navdata", 1, &callbackNavdata));

	parrotBattery Battery(20.0);
	parrotTransmitter Transmitter_;
	StateController_ = new parrotStatus();
	PoseBuilder PoseBuild;
	PoseController PoseControl(nullptr);
	parrotIMU IMU(&PoseBuild, &PoseControl);
	{
		//Battery.addReceiver(StateController_);
		StateController_->addReceiver(&IMU);
		IMU.addReceiver(StateController_);
	}

	const double SmoothFactor = 0.9;
	ros::Duration SmoothDuration(0.25);
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

			dirty = true;

			SmoothTime = ros::Time::now();
		}

		dirty = ros::Time::now() - InfoTime > InfoDuration;

		if (dirty)
		{
			ROS_INFO("Transmit: r %f, p %f, y %f, t %f; H %f (%f).", Roll, Pitch, Yarn, Thrust, HeightSet, HeightIs);

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



