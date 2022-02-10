/**
 * @file offb_node.cpp
 * @brief Offboard control example node, written with MAVROS version 0.19.x, PX4 Pro Flight
 * Stack and tested in Gazebo SITL
 */

#include <ros/ros.h>

#include <mavros_msgs/ManualControl.h>
#include <mavros_msgs/OverrideRCIn.h>


#include "coex/coexState.h"
#include "coex/coexBattery.h"
#include "coex/Joystick.h"
#include "coex/coexRC_Receiver.h"
#include "coex/coexRC_Transmitter.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;
    
    Joystick Stick(1027, 2003, 1500,
        1024, 2003, 1500,
        1031, 2003, 1500,
        1024, 2003, 1500);
    coexBattery Battery(15.6, 16.8, 15.7);
    coexState StateHandler(&Battery);
    coexRC_Receiver Receiver(&Stick);
    coexRC_Transmitter Transmitter(&StateHandler, &Stick, &Receiver);
	
    ros::Publisher local_thurst_pub = nh.advertise<mavros_msgs::OverrideRCIn>("mavros/rc/override", 10);
    ros::Rate rate(20.0);

	mavros_msgs::ManualControl Msg;	
    Msg.x = 0;
    Msg.y = 0;
    Msg.z = 0.05;
    Msg.r = 0;
	

    while (ros::ok() && !StateHandler.getConnected())
    {
        ros::spinOnce();
        rate.sleep();
    }

    ros::Time last_request = ros::Time::now();
    ros::Time Start = ros::Time::now();
    ros::Time UpdateState = ros::Time::now();

    ROS_INFO("Battery at %f.", Battery.getPercentage());

    Transmitter.setPayload(Msg);
    Transmitter.start();

    while(ros::ok() && ros::Time::now() - Start <= ros::Duration(10.0))
    {
        if (ros::Time::now() - UpdateState > ros::Duration(1))
        {
            ROS_INFO("TestRC2");
            ROS_INFO(StateHandler.getState().c_str());

            UpdateState = ros::Time::now();
        }
        
        Transmitter.call(&Receiver);

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}


