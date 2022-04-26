
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include <ros/ros.h>
#include <std_msgs/Char.h>
#include <ardrone_autonomy/Navdata.h>
#include <geometry_msgs/Twist.h>


#include "BagPlotter/DataCollector.h"
#include "BagPlotter/DataLoader.h"

/*
 * https://ardrone-autonomy.readthedocs.io/en/latest/reading.html
 */


int Counter;
ros::Time Time_Offset;
ros::Time UpdateMessage;
DataCollector Datas;


void callbackKeys(const std_msgs::Char::ConstPtr& CharPtr)
{
	Datas.addEntry("UserKey", std::to_string(CharPtr->data));
}

void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& NavdataPtr)
{
	if (Time_Offset == ros::Time())
	{
		Time_Offset = NavdataPtr->header.stamp;
	}
	
	if (!Datas.addEntry("Time", std::to_string(NavdataPtr->header.stamp.toSec())))
	{
		Datas.addDataset();
		Datas.addEntry("Time", std::to_string(NavdataPtr->header.stamp.toSec()));
		Datas.addEntry("State", std::to_string(NavdataPtr->state));
		Datas.addEntry("ax", std::to_string(NavdataPtr->ax));
		Datas.addEntry("ay", std::to_string(NavdataPtr->ay));
		Datas.addEntry("az", std::to_string(NavdataPtr->az));
		Datas.addEntry("vx", std::to_string(NavdataPtr->vx));
		Datas.addEntry("vy", std::to_string(NavdataPtr->vy));
		Datas.addEntry("vz", std::to_string(NavdataPtr->vz));
		Datas.addEntry("rx", std::to_string(NavdataPtr->rotX));
		Datas.addEntry("ry", std::to_string(NavdataPtr->rotY));
		Datas.addEntry("rz", std::to_string(NavdataPtr->rotZ));
		Datas.addEntry("h", std::to_string(NavdataPtr->altd));
		Datas.addEntry("Rotors", std::to_string(NavdataPtr->motor1 + NavdataPtr->motor2 + NavdataPtr->motor3 + NavdataPtr->motor4));

		Counter++;
		UpdateMessage = ros::Time::now();
	}
}

void callbackCommands(const geometry_msgs::Twist::ConstPtr& CommandPtr)
{
	Datas.addEntry("Cmd_vx", std::to_string(CommandPtr->linear.x));
	Datas.addEntry("Cmd_vy", std::to_string(CommandPtr->linear.y));
	Datas.addEntry("Cmd_vz", std::to_string(CommandPtr->linear.z));
	Datas.addEntry("Cmd_rz", std::to_string(CommandPtr->angular.z));
}



int main(int argc, char** argv)
{
	ROS_INFO("Started New Node: Bagfile Plotter");
	
	std::fstream OutputFile;
	std::string FilePath = "Bag.txt";
	

	OutputFile.open(FilePath.c_str(), std::fstream::out);
	Counter = 0;

	Datas.addKey("Time");
	Datas.addKey("State");
	Datas.addKey("ax");
	Datas.addKey("ay");
	Datas.addKey("az");
	Datas.addKey("vx");
	Datas.addKey("vy");
	Datas.addKey("vz");
	Datas.addKey("rx");
	Datas.addKey("ry");
	Datas.addKey("rz");
	Datas.addKey("h");
	Datas.addKey("Rotors");
	Datas.addKey("UserKey");
	Datas.addKey("Cmd_vx");
	Datas.addKey("Cmd_vy");
	Datas.addKey("Cmd_vz");
	Datas.addKey("Cmd_rz");


	{
		ros::init(argc, argv, "BagPlotter_parrot");
		ros::NodeHandle nh_;
		ros::Subscriber SubIMU_;
		ros::Subscriber SubUser_ = nh_.subscribe("ardrone/navdata", 1, callbackNavdata);
		ros::Subscriber SubNav_ = nh_.subscribe("ardrone/navdata", 1, callbackNavdata);
		ros::Subscriber SubCmd_ = nh_.subscribe("cmd_vel", 1, callbackCommands);

		ros::Duration DurationTimeout(10);
		UpdateMessage = ros::Time::now();
		Time_Offset = ros::Time::now();

		while (ros::ok())
		{
			if (ros::Time::now() - UpdateMessage >= DurationTimeout)
			{
				break;
			}

			ros::spinOnce();
		}
	}

	if (OutputFile.is_open())
	{
		OutputFile << Datas.getString(0, Counter, true);

		OutputFile.close();

		std::cout << "Wrote into >" << FilePath.c_str() << "<" << std::endl;
	}
	else
	{
		const size_t Intervall = 300;
		size_t Offset = 0;
		
		std::cout << "File not opened. >" << FilePath.c_str() << "<" << std::endl;
		std::cout << std::endl;

		std::cout << Datas.getString_Header() << std::endl;

		for (; Offset < Counter; Offset += Intervall)
		{
			std::cin.get();

			std::cout << Datas.getString(Offset, Offset + Intervall - 1, false) << std::endl;
		}
	}

	
	ROS_INFO("Terminated Node: Bagfile Plotter");
	ros::spinOnce();

	return 0;
}

