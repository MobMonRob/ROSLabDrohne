
#include <iostream>
#include <ros/ros.h>
#include <ardrone_autonomy/Navdata.h>

#include "Domain/Vector3D.h"



void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr)
{
	Vector3D Vector(Unit_Acceleration, navdataPtr->ax, navdataPtr->ay, navdataPtr->az);
	Vector3D Angles(Unit_AngleDeg, navdataPtr->rotX, navdataPtr->rotY, navdataPtr->rotZ);

	Angles = Angles * FixedPoint<Accuracy_Value>(3.14159) / FixedPoint<Accuracy_Value>(180);

	Vector3D Rotated_RPY = Vector.rotate_RollPitchYaw(Angles.getX(), Angles.getY(), Angles.getZ());
	Vector3D Rotated_Euler = Vector.rotate_Euler(Angles.getX(), Angles.getY(), Angles.getZ());


	std::cout << Rotated_Euler.getString() << "\t\t" << Rotated_RPY.getString() << std::endl;
}



int main(int argc, char** argv)
{
	ROS_INFO("Started New Node: Angles");

	ros::init(argc, argv, "Angles");
	ros::NodeHandle nh_;
	ros::Subscriber Sub_(nh_.subscribe("ardrone/navdata", 1, callbackNavdata));


	while (ros::ok())
	{
		ros::spinOnce();
	}

	ROS_INFO("Terminated Node: Angles");
	ros::spinOnce();

	return 0;
}



