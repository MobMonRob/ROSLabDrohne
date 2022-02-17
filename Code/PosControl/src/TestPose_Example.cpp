/**
 * @file offb_node.cpp
 * @brief Offboard control example node, written with MAVROS version 0.19.x, PX4 Pro Flight
 * Stack and tested in Gazebo SITL
 */

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include "mavros_msgs/State.h"

#include <mavros_msgs/ManualControl.h>

#include "coex/coexState.h"
#include "coex/coexBattery.h"
#include "coex/coexOrientation.h"


mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg)
{
    current_state = *msg;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;
	
    coexBattery Battery(15.6, 16.8, 15.7);
    coexState StateHandler(&Battery);
    coexOrientation Locator(&StateHandler, 3.5);

    ros::Subscriber state_sub = nh.subscribe("mavros/state", 10, state_cb);
    ros::Publisher local_thurst_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);
    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");
    ros::Rate rate(20.0);
    ros::Duration TestTime(10.0);
    const double Height = .1;


    // Values in m
	geometry_msgs::PoseStamped Msg;
    Msg.pose.position.x = 0;
    Msg.pose.position.y = 0;
    Msg.pose.position.z = Height;
    

    // wait for FCU connection
    while (ros::ok() && !StateHandler.getConnected())
    {
        ros::spinOnce();
        rate.sleep();
    }

    //send a few setpoints before starting
    for(int i = 100; ros::ok() && i > 0; --i)
    {
		local_thurst_pub.publish(Msg);
        ros::spinOnce();
        rate.sleep();
    }

    mavros_msgs::SetMode offb_set_mode;
    offb_set_mode.request.custom_mode = coexMode_Offboard;

    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;

    ros::Time last_request = ros::Time::now();
    ros::Time Start = ros::Time::now();
    ros::Time UpdateState = ros::Time::now();
	
	
    ROS_INFO("Battery at %f.", Battery.getPercentage());

    while(ros::ok() && ros::Time::now() - Start <= TestTime)
    {
        if (current_state.mode != "OFFBOARD" &&
            (ros::Time::now() - last_request > ros::Duration(2.0))) {
            if (set_mode_client.call(offb_set_mode) &&
                offb_set_mode.response.mode_sent) {
                ROS_INFO("Offboard enabled");
            }
            last_request = ros::Time::now();
        }
        else {
            if (!current_state.armed &&
                (ros::Time::now() - last_request > ros::Duration(2.0))) {
                if (arming_client.call(arm_cmd) &&
                    arm_cmd.response.success) {
                    ROS_INFO("Vehicle armed");
                }
                last_request = ros::Time::now();
            }
        }
        
        if (ros::Time::now() - UpdateState > ros::Duration(1.0))
        {
        	ROS_INFO("TestPoseExamlpe");
            ROS_INFO("Ground = %f", Locator.getGroundClearance());
            ROS_INFO(StateHandler.getState().c_str());

            UpdateState = ros::Time::now();
        }

		local_thurst_pub.publish(Msg);

        ros::spinOnce();
        rate.sleep();
    }


    // RESET
	rate = ros::Rate(5.0);
	arm_cmd.request.value = false;
		
	while (current_state.armed)
	{
		arming_client.call(arm_cmd);
		ros::spinOnce();
		rate.sleep();
	}
	ROS_INFO("Vehicle disarmed");
		
	offb_set_mode.request.custom_mode = "MANUAL";
	while (current_state.mode != "MANUAL")
	{
		set_mode_client.call(offb_set_mode);
		ros::spinOnce();
		rate.sleep();
	}
	ROS_INFO("Offboard disabled");

    return 0;
}


