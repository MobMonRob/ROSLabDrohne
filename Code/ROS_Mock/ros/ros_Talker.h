#ifndef MOCK_ROSTALKER_H
#define MOCK_ROSTALKER_H

#include <string>

void ROS_INFO(std::string Msg);
void ROS_INFO(std::string Msg, double Value1);
void ROS_INFO(std::string Msg, int Value1, double Value2);
void ROS_INFO(std::string Msg, int Value1, std::string Value2);
void ROS_INFO(std::string Msg, double Value1, double Value2, double Value3);
void ROS_INFO(std::string Msg, double Value1, double Value2, double Value3, double Value4);
void ROS_INFO(std::string Msg, double Value1, double Value2, double Value3, double Value4, double Value5);
void ROS_INFO(std::string Msg, double Value1, double Value2, double Value3, double Value4, double Value5, double Value6);
void ROS_INFO(std::string Msg, std::string Str1);

void ROS_WARN(std::string Msg);
void ROS_WARN(std::string Msg, double Value1, double Value2);

void ROS_ERROR(std::string Msg);
void ROS_ERROR(std::string Msg, std::string Value1);

#endif // MOCK_ROSTALKER_H
