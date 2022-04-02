#include "parrot/parrotIMU.h"

#include "Domain/Vector3D.h"
#include "std_srvs/Empty.h"

#include "geometry_msgs/Twist.h"


parrotIMU::parrotIMU(PoseBuildable* PoseBuilder, PoseControlable* PoseController)
	: IMUable(PoseBuilder, PoseController),
	PubPose_(this->nh_.advertise<geometry_msgs::Twist>("Controller/Pose", 1)),
	SubIMU_(this->nh_.subscribe("ardrone/imu", 1, &parrotIMU::callbackIMU, this)),
	SubNav_(this->nh_.subscribe("ardrone/navdata", 1, &parrotIMU::callbackNavdata, this))
{
	ROS_INFO("Starting parrotIMU...");
	ros::spinOnce();

	ROS_INFO("Started parrotIMU");
}

parrotIMU::~parrotIMU()
{
	ROS_INFO("Termintated parrotIMU");
	ros::spinOnce();
}





bool parrotIMU::calibrate()
{
	bool ReturnBool = false;
	ros::ServiceClient ClientIMUCalib = this->nh_.serviceClient<std_srvs::Empty>("ardrone/imu_recalib");
	std_srvs::Empty Cmd;


	ReturnBool = ClientIMUCalib.call(Cmd);

	return ReturnBool;
}



void parrotIMU::callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr)
{
	Timestamp Time(navdataPtr->header.stamp.toSec());
	Vector3D LinearAcceleration(Unit_Acceleration, navdataPtr->ax, navdataPtr->ay, navdataPtr->az);
	Vector3D RotationalVelocity(Unit_AngleDeg, navdataPtr->rotX, navdataPtr->rotY, navdataPtr->rotZ);
	Value GroundClearance(Unit_Length, FixedPoint<Accuracy_Value>(static_cast<int>(navdataPtr->altd)));
	
	// maybe trigger new Thread??
	IMUState State = this->StateBuilder_.createState(Time, LinearAcceleration * Value_GravitationConstant.getValue(), RotationalVelocity, GroundClearance);

	this->calcPose(State);
	this->triggerController();

	this->publishPose();
}

void parrotIMU::callbackIMU(const sensor_msgs::Imu::ConstPtr& IMUPtr)
{



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
