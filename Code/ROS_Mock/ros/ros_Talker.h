#ifndef MOCK_ROSTALKER_H
#define MOCK_ROSTALKER_H

#include <string>

void ROS_INFO(std::string Msg);
void ROS_INFO(std::string Msg, double Value1);
void ROS_INFO(std::string Msg, double Value1, double Value2, double Value3, double Value4);
void ROS_INFO(std::string Msg, std::string Str1);

void ROS_WARN(std::string Msg);
void ROS_WARN(std::string Msg, double Value1, double Value2);

void ROS_ERROR(std::string Msg);

#endif // MOCK_ROSTALKER_H
