/**
 * @file offb_node.cpp
 * @brief Offboard control example node, written with MAVROS version 0.19.x, PX4 Pro Flight
 * Stack and tested in Gazebo SITL
 */

#include <ros/ros.h>

#include <mavros_msgs/ManualControl.h>

#include "coex/coexState.h"
#include "coex/coexBattery.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;
    
    coexBattery Battery(15.6, 16.8, 15.7);
    coexState StateHandler(&Battery);
    
    ros::Publisher local_thurst_pub = nh.advertise<mavros_msgs::ManualControl>("mavros/manual_control/send", 10);
    ros::Publisher pub_ring = nh.advertise<mavros_msgs::ManualControl>("mavros/manual_control/control", 10);
	ros::Rate rate(20.0);

	mavros_msgs::ManualControl Msg;
	Msg.x = 0;
	Msg.y = 0;
	Msg.z = -900;
	Msg.r = 0;
	

    while(ros::ok() && !StateHandler.getConnected())
    {
        ros::spinOnce();
        rate.sleep();
    }

    for(int i = 100; ros::ok() && i > 0; --i)
    {
		local_thurst_pub.publish(Msg);
		pub_ring.publish(Msg);
        ros::spinOnce();
        rate.sleep();
    }

    ros::Time last_request = ros::Time::now();
    ros::Time Start = ros::Time::now();
    
    ROS_INFO("Battery at %f.", Battery.getPercentage());

    StateHandler.setMode(coexMode_Offboard);
    StateHandler.waitNextState();
    
    
    while(ros::ok() && ros::Time::now() - Start <= ros::Duration(10.0))
    {
        if (StateHandler.getMode() == coexMode_Offboard)
        {
            if (!StateHandler.getArmState() && ros::Time::now() - last_request > ros::Duration(0.5))
            {
                ROS_INFO("Try Arming...");


                StateHandler.setArmState(true);

                last_request = ros::Time::now();
            }
        }
        else if (ros::Time::now() - last_request > ros::Duration(1.0))
        {
            ROS_INFO("VehicleMode = %s", StateHandler.getMode().c_str());

            last_request = ros::Time::now();
        }


        local_thurst_pub.publish(Msg);
        pub_ring.publish(Msg);

        ros::spinOnce();
        rate.sleep();
    }
    

    // RESET
    StateHandler.setArmState(false);
    StateHandler.setMode("MANUAL");
	
    return 0;
}


