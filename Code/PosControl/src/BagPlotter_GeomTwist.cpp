#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>


/*
 * https://ardrone-autonomy.readthedocs.io/en/latest/reading.html
 */


ros::Time TimeStamp;
ros::Time TimeMessage;
int Counter;
ros::Time UpdateMessage;
std::ofstream OutputFile;
std::vector<std::string> OutputContent;

geometry_msgs::Twist MsgPrev;








bool equals(geometry_msgs::Twist Msg, geometry_msgs::Twist MsgPrev)
{
	return Msg.linear.x == MsgPrev.linear.x &&
		Msg.linear.y == MsgPrev.linear.y &&
		Msg.linear.z == MsgPrev.linear.z &&
		Msg.angular.x == MsgPrev.angular.x &&
		Msg.angular.y == MsgPrev.angular.y &&
		Msg.angular.z == MsgPrev.angular.z;
}


void callbackGeomTwist(const geometry_msgs::Twist::ConstPtr& TwistPtr)
{
	std::string OutputLine;


	TimeMessage = ros::Time::now();

	if (TimeStamp == ros::Time())
	{
		TimeStamp = TimeMessage;
	}

	if (!equals(*TwistPtr, MsgPrev))
	{
		OutputLine.append(std::to_string((TimeMessage - TimeStamp).toSec())).append(";");

		OutputLine.append(std::to_string(TwistPtr->linear.x)).append(";");
		OutputLine.append(std::to_string(TwistPtr->linear.y)).append(";");
		OutputLine.append(std::to_string(TwistPtr->linear.z)).append(";");

		OutputLine.append(std::to_string(TwistPtr->angular.x)).append(";");
		OutputLine.append(std::to_string(TwistPtr->angular.y)).append(";");
		OutputLine.append(std::to_string(TwistPtr->angular.z)).append(";");

		OutputLine.append("\n");

		std::cout << OutputLine;
		OutputContent.append(OutputLine);
		Counter++;

		MsgPrev = *TwistPtr;
	}
	UpdateMessage = ros::Time::now();
}






int main(int argc, char** argv)
{
	ROS_INFO("Started New Node: Bagfile Plotter");
	
	std::string FilePath = "/home/Documents/BagOutput_GeomTwist.txt";
	std::string Header = "Time [s];lx;ly;lz;ax;ay;az\n";




	OutputFile.open(FilePath.c_str());
	Counter = 0;
	OutputContent.append(Header);
	std::cout << Header;


	{
		ros::init(argc, argv, "BagPlotter_GeometryTwist");
		ros::NodeHandle nh_;
		ros::Subscriber SubIMU_;
		ros::Subscriber SubCmd_ = nh_.subscribe("cmd_vel", 1, callbackGeomTwist);

		ros::Time Update = ros::Time::now();
		ros::Duration DurationUpdate(1);
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
		OutputFile << OutputContent;

		OutputFile.close();
		std::cout << "Wrote into >" << FilePath.c_str() << "<" << std::endl;
	}
	else
	{
		std::cout << "File not opened. >" << FilePath.c_str() << "<" << std::endl;
	}

	
	ROS_INFO("Terminated Node: Bagfile Plotter");
	ros::spinOnce();

	return 0;
}

