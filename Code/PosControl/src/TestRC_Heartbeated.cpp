/**
 * @file offb_node.cpp
 * @brief Offboard control example node, written with MAVROS version 0.19.x, PX4 Pro Flight
 * Stack and tested in Gazebo SITL
 */

#include <ros/ros.h>

#include <mavros_msgs/ManualControl.h>
#include <mavros_msgs/OverrideRCIn.h>
#include <mavros_msgs/PositionTarget.h>


#include "coex/coexState.h"
#include "coex/coexBattery.h"
#include "coex/Joystick.h"
#include "coex/coexRC_Receiver.h"
#include "coex/coexRC_Transmitter.h"
#include "coex/coexOrientation.h"



void PosCallback(const mavros_msgs::PositionTarget::ConstPtr& msg)
{
    geometry_msgs::Point Pos = msg->position;

    ROS_INFO("Drone is at [%f, %f, %f].", Pos.x, Pos.y, Pos.z);
}

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
	
    ros::Publisher local_thurst_pub = nh.advertise<mavros_msgs::PositionTarget>("mavros/setpoint_raw/local", 10);
    ros::Subscriber SubPos = nh.subscribe("mavros/setpoint_raw/target_local", 10, PosCallback);
    ros::Rate rate(250.0);
    const double Height = .1;

	mavros_msgs::PositionTarget Msg;	
    Msg.position.z = Height;

    mavros_msgs::ManualControl RCMsg;
    RCMsg.x = 0;
    RCMsg.y = 0;
    RCMsg.z = 0.05;
    RCMsg.r = 0;

    while (ros::ok() && !StateHandler.getConnected())
    {
        ros::spinOnce();
        rate.sleep();
    }

    for (int i = 100; ros::ok() && i > 0; --i)
    {
        local_thurst_pub.publish(Msg);
        ros::spinOnce();
        rate.sleep();
    }

    ros::Time Alive = ros::Time::now();
    ros::Time last_request = ros::Time::now();
    ros::Time Start = ros::Time::now();
    ros::Time UpdateState = ros::Time::now();
    ros::Time UpdateHeight = ros::Time::now();
    ros::Time ControlHeight = ros::Time::now();


    ROS_INFO("Battery at %f.", Battery.getPercentage());

    StateHandler.setMode(coexMode_Offboard);
    StateHandler.setArmState(true);

    while(ros::ok() && ros::Time::now() - Start <= ros::Duration(10.0))
    {
        if (ros::Time::now() - Alive >= ros::Duration(0.45))
        {
            StateHandler.setMode(coexMode_Offboard);
            local_thurst_pub.publish(Msg);

            Alive = ros::Time::now();
        }


        if (!StateHandler.getArmState() && ros::Time::now() - last_request >= ros::Duration(0.5))
        {
            ROS_INFO("Try arming...");

            StateHandler.setArmState(true);

            last_request = ros::Time::now();
        }

        if (ros::Time::now() - UpdateState >= ros::Duration(1))
        {
            ROS_INFO("TestRC_Heartbeat");
            ROS_INFO("Ground = %f", Locator.getGroundClearance());
            ROS_INFO(StateHandler.getState().c_str());

            UpdateState = ros::Time::now();
        }
        
        if (ros::Time::now() - ControlHeight >= ros::Duration(0.1))
        {   // basic controller
            RCMsg.z += (Height - Locator.getGroundClearance()) / 100;

            ControlHeight = ros::Time::now();
        }

        Transmitter.setPayload(RCMsg);

        ros::spinOnce();
        rate.sleep();
    }


    // Landing
    ControlHeight = ros::Time::now();

    while (ros::ok() && Locator.getGroundClearance() > 0)
    {
        if (ros::Time::now() - Alive >= ros::Duration(0.25))
        {
            StateHandler.setMode(coexMode_Offboard);

            Alive = ros::Time::now();
        }

        if (ros::Time::now() - UpdateHeight > ros::Duration(0.5))
        {
            ROS_INFO("Ground = %f", Locator.getGroundClearance());

            UpdateHeight = ros::Time::now();
        }

        if (ros::Time::now() - ControlHeight >= ros::Duration(0.1))
        {   // basic controller
            if (Msg.position.z >= 0.5)
            {
                Msg.position.z -= 0.1;
            }
            else
            {
                Msg.position.z = 0;
            }

            ControlHeight = ros::Time::now();
        }

        local_thurst_pub.publish(Msg);

        ros::spinOnce();
        rate.sleep();
    }


    // Shutdown
    StateHandler.setArmState(false);
    StateHandler.setMode(coexMode_Manual);
    StateHandler.waitNextState();

    return 0;
}


