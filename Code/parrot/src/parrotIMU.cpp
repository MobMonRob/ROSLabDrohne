#include "parrot/parrotIMU.h"

#include <iostream>

#include "Domain/Vector3D.h"
#include "std_srvs/Empty.h"

#include "geometry_msgs/Twist.h"


parrotIMU::parrotIMU(PoseBuildable* PoseBuilder, PoseControlable* PoseController)
	: IMUable(PoseBuilder, PoseController, FixedPoint<Accuracy_Value>(5)),
	StateBuilder_(25, 35, StateBuffer),
	PubStateRaw_(this->nh_.advertise<geometry_msgs::Twist>("Controller/StateRaw", 1)),
	PubState_(this->nh_.advertise<geometry_msgs::Twist>("Controller/State", 1)),
	PubPose_(this->nh_.advertise<geometry_msgs::Twist>("Controller/Pose", 1)),
	SubIMU_(this->nh_.subscribe("ardrone/imu", 1, &parrotIMU::callbackIMU, this)),
	SubNav_(this->nh_.subscribe("ardrone/navdata", 1, &parrotIMU::callbackNavdata, this)),
	MsgCount_(0)
{
	ROS_INFO("Starting parrotIMU...");
	ros::spinOnce();

	this->calibrate();

	ROS_INFO("Started parrotIMU");
}

parrotIMU::~parrotIMU()
{
	ROS_INFO("Termintated parrotIMU");
	ros::spinOnce();
}





void parrotIMU::setFlightState(bool FlightState)
{
	this->StateBuilder_.setOffsettingFlag(!FlightState);

	if (FlightState)
	{
		this->PoseBuilder_->setCalibrationFlag(false);
	}
}


bool parrotIMU::calibrate()
{
	bool ReturnBool = this->getValidFlag();


	if (!ReturnBool)
	{
		ros::ServiceClient ClientIMUCalib = this->nh_.serviceClient<std_srvs::Empty>("ardrone/imu_recalib");
		std_srvs::Empty Cmd;


		ReturnBool = ClientIMUCalib.call(Cmd);

		if (ReturnBool)
		{
			this->StateBuilder_.reset();
			this->StateBuilder_.setValidFlag(true);
			this->PoseBuilder_->reset();
			this->setValidFlag(true);
			this->MsgCount_ = 0;
		}
	}

	return ReturnBool;
}

void parrotIMU::safetyTriggered()
{
	std::cout << this->getTimeLocalString() << " parrotIMU::safetyTriggered" << std::endl;

	this->StateBuilder_.setValidFlag(false);

	this->PoseBuilder_->setValidFlag(false);
	this->PoseBuilder_->setCalibrationFlag(false);
	this->PoseBuilder_->setCalculationFlag(false);

	IMUable::safetyTriggered();
}



void parrotIMU::callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr)
{
	this->setTime(Timestamp(navdataPtr->header.stamp.toSec()));

	if (this->StateBuilder_.getValidFlag())
	{
		Vector3D Linear(Unit_Acceleration, navdataPtr->ax, navdataPtr->ay, navdataPtr->az);
		Vector3D Rotational(Unit_State_Angular,
			FixedPoint<Accuracy_Value>(navdataPtr->rotX),
			FixedPoint<Accuracy_Value>(navdataPtr->rotY),
			FixedPoint<Accuracy_Value>(navdataPtr->rotZ));
		Value GroundClearance(Unit_Length, FixedPoint<Accuracy_Value>(static_cast<int>(navdataPtr->altd)));

		// maybe trigger new Thread??
		IMUState State = this->StateBuilder_.createState(this->getTime(), Linear * Value_GravitationConstant.getValue(), Rotational, GroundClearance);

		this->ImpactRequirement_->updateAcceleration(State.getLinear());
		this->meetsRequirements();
		
		if (++MsgCount_ == 2* StateBuffer)
		{
			this->StateBuilder_.setOffsettingFlag(false);
			this->PoseBuilder_->setCalibrationFlag(true);
		}
		
		if (this->getValidFlag())
		{
			int MotorSpeed = navdataPtr->motor1 + navdataPtr->motor2 + navdataPtr->motor3 + navdataPtr->motor4;


			if (MotorSpeed == 0 && (navdataPtr->altd) == 0)
			{
				this->PoseBuilder_->setValidFlag(false);
			}
			if (MotorSpeed > 0 || (navdataPtr->altd) > 0)
			{
				//this->PoseBuilder_->setCalculationFlag(true);
			}
			if (MotorSpeed > TakeoffRotorSpeed || (navdataPtr->altd) > 0)
			{
				this->PoseBuilder_->setCalculationFlag(true);
				this->PoseBuilder_->setValidFlag(true);
			}
		}
		this->calcPose(State);
		this->triggerController();

		this->publishPose();
		
	}
}

void parrotIMU::callbackIMU(const sensor_msgs::Imu::ConstPtr& IMUPtr)
{



}





void parrotIMU::publishState()
{
	geometry_msgs::Twist Msg;
	IMUState State = this->StateBuilder_.getState();


	Msg.linear.x = State.getLinear().getX().getValue();
	Msg.linear.y = State.getLinear().getY().getValue();
	Msg.linear.z = State.getLinear().getZ().getValue();

	Msg.angular.x = State.getRotational().getX().getValue();
	Msg.angular.y = State.getRotational().getY().getValue();
	Msg.angular.z = State.getRotational().getZ().getValue();

	PubPose_.publish(Msg);
}

void parrotIMU::publishPose()
{
	geometry_msgs::Twist Msg;
	Pose Pose = this->getPose();


	Msg.linear.x = Pose.getPosition().getX().getValue();
	Msg.linear.y = Pose.getPosition().getY().getValue();
	Msg.linear.z = Pose.getPosition().getZ().getValue();

	Msg.angular.x = Pose.getOrientation().getX().getValue();
	Msg.angular.y = Pose.getOrientation().getY().getValue();
	Msg.angular.z = Pose.getOrientation().getZ().getValue();

	PubPose_.publish(Msg);
}
