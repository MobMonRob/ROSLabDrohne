#include <ros/ros.h>

#include "PosControl/TestClass.h"





int main(int argc, char** argv)
{
  ROS_INFO("Started New Node: Tester");
  
  ros::init(argc, argv, "Tester");
  ros::NodeHandle nh;
  
    
  TestClass WHAT;
  
  
  
  ROS_INFO("TestClass said: %d!", WHAT.doSmth());
  
  
  
  return 0;
}



