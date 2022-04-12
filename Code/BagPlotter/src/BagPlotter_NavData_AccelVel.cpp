
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include <ros/ros.h>
#include <ardrone_autonomy/Navdata.h>

#include "BagPlotter/DataCollector.h"


/*
 * https://ardrone-autonomy.readthedocs.io/en/latest/reading.html
 */


int Counter;
ros::Time Time_Offset;
ros::Time UpdateMessage;
DataCollector Datas;


void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr)
{
	if (Time_Offset == ros::Time())
	{
		Time_Offset = navdataPtr->header.stamp;
	}
	
	Datas.addDataset();

	Datas.addEntry("Time", std::to_string((navdataPtr->header.stamp - Time_Offset).toSec()));
	Datas.addEntry("State", std::to_string(navdataPtr->state));
	Datas.addEntry("ax", std::to_string(navdataPtr->ax));
	Datas.addEntry("ay", std::to_string(navdataPtr->ay));
	Datas.addEntry("az", std::to_string(navdataPtr->az));
	Datas.addEntry("vx", std::to_string(navdataPtr->vx));
	Datas.addEntry("vy", std::to_string(navdataPtr->vy));
	Datas.addEntry("vz", std::to_string(navdataPtr->vz));
	Datas.addEntry("h", std::to_string(navdataPtr->altd));

	Counter++;
	UpdateMessage = ros::Time::now();
}






int main(int argc, char** argv)
{
	ROS_INFO("Started New Node: Bagfile Plotter");
	
	std::fstream OutputFile;
	std::string FilePath = "/home/Documents/BagOutput_NavData.txt";
	

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
	Datas.addKey("h");


	{
		ros::init(argc, argv, "BagPlotter_NavData");
		ros::NodeHandle nh_;
		ros::Subscriber SubIMU_;
		ros::Subscriber SubNav_ = nh_.subscribe("ardrone/navdata", 1, callbackNavdata);

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

