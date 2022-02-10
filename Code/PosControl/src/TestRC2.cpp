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
#include "coex/coexOrientation.h"


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
    coexOrientation Locator(&StateHandler, 3.5);
	
    ros::Publisher local_thurst_pub = nh.advertise<mavros_msgs::OverrideRCIn>("mavros/rc/override", 10);
    ros::Rate rate(20.0);
    const double Height = .1;

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
    ros::Time UpdateHeight = ros::Time::now();
    ros::Time ControlHeight = ros::Time::now();

    ROS_INFO("Battery at %f.", Battery.getPercentage());

    Transmitter.setPayload(Msg);

    while(ros::ok() && ros::Time::now() - Start <= ros::Duration(10.0))
    {
        if (ros::Time::now() - UpdateState > ros::Duration(1))
        {
            ROS_INFO("TestRC2");
            ROS_INFO(StateHandler.getState().c_str());

            UpdateState = ros::Time::now();
        }
        
        if (ros::Time::now() - UpdateHeight > ros::Duration(0.25))
        {
            ROS_INFO("Ground = %f", Locator.getGroundClearance());
            ROS_INFO("Thrust = %f", Msg.z);

            UpdateHeight = ros::Time::now();
        }

        {   // basic controller
            Msg.z += (Height - Locator.getGroundClearance()) / 100;

            ControlHeight = ros::Time::now();
        }


        Transmitter.setPayload(Msg);

        ros::spinOnce();
        rate.sleep();
    }


    // Landing
    while (ros::ok() && Locator.getGroundClearance() > 0)
    {
        if (ros::Time::now() - UpdateHeight > ros::Duration(0.25))
        {
            ROS_INFO("Ground = %f", Locator.getGroundClearance());
            Msg.z = 0.99 * Msg.z;

            UpdateHeight = ros::Time::now();
        }

        Transmitter.setPayload(Msg);

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}


