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


mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;
	
    coexBattery Battery(15.6, 16.8, 15.7);
    coexState StateHandler(&Battery);

    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, state_cb);
    ros::Publisher local_thurst_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);
    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");
	
    const bool example = false;


	geometry_msgs::PoseStamped pose;
    pose.pose.position.x = 0;
    pose.pose.position.y = 0;
    pose.pose.position.z = 0.05;
    
    
    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(20.0);

    // wait for FCU connection
    /*
    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        rate.sleep();
    }
    */
    while (ros::ok() && !StateHandler.getConnected())
    {
        ros::spinOnce();
        rate.sleep();
    }

    //send a few setpoints before starting
    for(int i = 100; ros::ok() && i > 0; --i)
    {
		local_thurst_pub.publish(pose);
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
	
    if (!example)
    {
        StateHandler.setMode(coexMode_Offboard);
        //StateHandler.setModeAuto();
        StateHandler.waitNextState();
    }

    while(ros::ok() && ros::Time::now() - Start <= ros::Duration(7.0))
    {
        if (example)
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
        }
        else
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
        }
        
        if (ros::Time::now() - UpdateState > ros::Duration(1))
        {
        	ROS_INFO(example ? "example" : "coexHandler");
            ROS_INFO(StateHandler.getState().c_str());

            UpdateState = ros::Time::now();
        }



		local_thurst_pub.publish(pose);

        ros::spinOnce();
        rate.sleep();
    }


    // RESET
    if (example)
	{	
		ros::Rate rate(2.0);
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
    }
    else
    {
        StateHandler.setArmState(false);
        StateHandler.setMode("MANUAL");
    }

    return 0;
}


