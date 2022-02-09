/**
 * @file offb_node.cpp
 * @brief Offboard control example node, written with MAVROS version 0.19.x, PX4 Pro Flight
 * Stack and tested in Gazebo SITL
 */

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>

#include <mavros_msgs/ManualControl.h>
#include <mavros_msgs/OverrideRCIn.h>

#include "coex/coexState.h"
#include "coex/coexBattery.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;
    
    coexBattery Battery(15.6, 16.8, 15.7);
    coexState State(&Battery);
    
    
    ros::Publisher local_thurst_pub = nh.advertise<mavros_msgs::ManualControl>("mavros/manual_control/send", 10);
    ros::Publisher pub_ring = nh.advertise<mavros_msgs::ManualControl>("mavros/manual_control/control", 10);
	
	mavros_msgs::ManualControl Msg;
	Msg.x = 0;
	Msg.y = 0;
	Msg.z = -900;
	Msg.r = 0;
	
	
    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(20.0);

    // wait for FCU connection
    while(ros::ok() && !State.getConnected()){
        ros::spinOnce();
        rate.sleep();
    }

    //send a few setpoints before starting
    for(int i = 100; ros::ok() && i > 0; --i){
		local_thurst_pub.publish(Msg);
		pub_ring.publish(Msg);
        ros::spinOnce();
        rate.sleep();
    }

    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;

    ros::Time last_request = ros::Time::now();
    ros::Time Start = ros::Time::now();
    
    ROS_INFO("Battery at %f.", Battery.getPercentage());

    State.setMode("OFFBOARD");
    State.setModeAuto();
    
    State.waitNextState();
    
    
    while(ros::ok() && ros::Time::now() - Start <= ros::Duration(15.0))
    {
        ros::spinOnce();

        if (State.getMode() != "OFFBOARD" && ros::Time::now() - last_request > ros::Duration(0.25))
        {
            State.setMode("OFFBOARD");

            last_request = ros::Time::now();
        }
        else if (State.getMode() == "OFFBOARD" && !State.getArmState() && ros::Time::now() - last_request > ros::Duration(0.5))
        {
            ROS_INFO("Try Arming...");


            State.setArmState(true);

            last_request = ros::Time::now();
        }
        else if (ros::Time::now() - last_request > ros::Duration(1.0))
        {
            ROS_INFO("VehicleMode = %s", State.getMode().c_str());

            last_request = ros::Time::now();
        }


        local_thurst_pub.publish(Msg);
        pub_ring.publish(Msg);

        rate.sleep();
    }
    
    
    State.setArmState(false);
    State.setMode("MANUAL");
    State.setModeAuto(false);
	
    return 0;
}


