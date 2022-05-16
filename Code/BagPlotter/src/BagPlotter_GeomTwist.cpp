
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#include "BagPlotter/DataCollector.h"


/*
 * https://ardrone-autonomy.readthedocs.io/en/latest/reading.html
 */


int Counter;
ros::Time Time_Offset;
ros::Time UpdateMessage;
DataCollector Datas;


void callbackGeomTwist(const geometry_msgs::Twist::ConstPtr& TwistPtr)
{
	if (Time_Offset == ros::Time())
	{
		Time_Offset = ros::Time::now();
	}

	Datas.addDataset();

	Datas.addEntry("Time", std::to_string((ros::Time::now() - Time_Offset).toSec()));
	Datas.addEntry("lx", std::to_string(TwistPtr->linear.x));
	Datas.addEntry("ly", std::to_string(TwistPtr->linear.y));
	Datas.addEntry("lz", std::to_string(TwistPtr->linear.z));
	Datas.addEntry("ax", std::to_string(TwistPtr->angular.x));
	Datas.addEntry("ay", std::to_string(TwistPtr->angular.y));
	Datas.addEntry("az", std::to_string(TwistPtr->angular.z));
	
	Counter++;
	UpdateMessage = ros::Time::now();
}






int main(int argc, char** argv)
{
	ROS_INFO("Started New Node: Bagfile Plotter");
	
	std::fstream OutputFile;
	std::string FilePath = "/home/Documents/BagOutput_GeomTwist.txt";


	OutputFile.open(FilePath.c_str(), std::fstream::out);
	Counter = 0;
	
	Datas.addKey("Time");
	Datas.addKey("lx");
	Datas.addKey("ly");
	Datas.addKey("lz");
	Datas.addKey("ax");
	Datas.addKey("ay");
	Datas.addKey("az");


	{
		ros::init(argc, argv, "BagPlotter_GeometryTwist");
		ros::NodeHandle nh_;
		ros::Subscriber SubIMU_;
		ros::Subscriber SubCmd_ = nh_.subscribe("cmd_vel", 1, callbackGeomTwist);

		ros::Duration DurationTimeout(10);
		UpdateMessage = ros::Time::now();


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
		const size_t Intervall = 250;
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

