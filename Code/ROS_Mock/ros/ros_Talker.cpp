#include "ros_Talker.h"

#include <iostream>

void ROS_INFO(std::string Msg)
{
	std::cout << "ROS_INFO: " << Msg << std::endl;
}
void ROS_INFO(std::string Msg, double Value1)
{
	std::cout << "ROS_INFO: " << Msg << "; " << Value1 << std::endl;
}
void ROS_INFO(std::string Msg, int Value1, double Value2)
{
	std::cout << "ROS_INFO: " << Msg << "; " << Value1 << "; " << Value2 << std::endl;
}
void ROS_INFO(std::string Msg, int Value1, std::string Value2)
{
	std::cout << "ROS_INFO: " << Msg << "; " << Value1 << "; " << Value2 << std::endl;
}
void ROS_INFO(std::string Msg, double Value1, double Value2, double Value3)
{
	std::cout << "ROS_INFO: " << Msg << "; " << Value1 << "; " << Value2 << "; " << Value3 << std::endl;
}
void ROS_INFO(std::string Msg, double Value1, double Value2, double Value3, double Value4)
{
	std::cout << "ROS_INFO: " << Msg << "; " << Value1 << "; " << Value2 << "; " << Value3 << "; " << Value4 << std::endl;
}
void ROS_INFO(std::string Msg, std::string Str1)
{
	std::cout << "ROS_INFO: " << Msg << "; + " << Str1 << std::endl;
}

void ROS_WARN(std::string Msg)
{
	std::cout << "ROS_WARNING: " << Msg << std::endl;
}

void ROS_WARN(std::string Msg, double Value1, double Value2)
{
	std::cout << "ROS_WARNING: " << Msg << "; + " << Value1 << ", " << Value2 << std::endl;
}


void ROS_ERROR(std::string Msg)
{
	std::cout << "ROS_ERROR: " << Msg << std::endl;
}


void ROS_ERROR(std::string Msg, std::string Value1)
{
	std::cout << "ROS_ERROR: " << Msg << "; " << Value1 << std::endl;
}
