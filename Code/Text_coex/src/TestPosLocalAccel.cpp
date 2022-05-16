#include <ros/ros.h>
#include <mavros_msgs/PositionTarget.h>

#include "coex/coexState.h"
#include "coex/coexBattery.h"
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

    coexBattery Battery(15.6, 16.8, 15.7);
    coexState StateHandler(&Battery);
    coexOrientation Locator(&StateHandler, 3.5);
	
    ros::Publisher local_thurst_pub = nh.advertise<mavros_msgs::PositionTarget>("mavros/setpoint_raw/local", 10);
    ros::Subscriber SubPos = nh.subscribe("mavros/setpoint_raw/target_local", 10, PosCallback);
    ros::Rate rate(20.0);
    ros::Duration TestTime(10.0);
    const double Height = .2;

    // Values in m/s²
    mavros_msgs::PositionTarget Msg;
    Msg.acceleration_or_force.z = 0.1;


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

    while(ros::ok() && ros::Time::now() - Start <= TestTime)
    {
        if (ros::Time::now() - UpdateState >= ros::Duration(1))
        {
            ROS_INFO("TestRC2");
            ROS_INFO(StateHandler.getState().c_str());

            UpdateState = ros::Time::now();
        }
        
        if (ros::Time::now() - UpdateState >= ros::Duration(1))
        {
            ROS_INFO("TestPosLocalVel");
            ROS_INFO("Ground = %f", Locator.getGroundClearance());
            ROS_INFO(StateHandler.getState().c_str());

            UpdateState = ros::Time::now();
        }

        if (ros::Time::now() - ControlHeight >= ros::Duration(0.1))
        {   // basic controller
            if (Locator.getGroundClearance() > Height)
            {
                Msg.acceleration_or_force.z = 0;
            }

            ControlHeight = ros::Time::now();
        }


        local_thurst_pub.publish(Msg);

        ros::spinOnce();
        rate.sleep();
    }


    // Landing
    Msg = mavros_msgs::PositionTarget();
    Msg.position.z = Height;


    ControlHeight = ros::Time::now();

    while (ros::ok() && Locator.getGroundClearance() > 0)
    {
        if (ros::Time::now() - ControlHeight >= ros::Duration(0.1))
        {   // basic controller
            ROS_INFO("Ground = %f", Locator.getGroundClearance());

            if (Msg.position.z >= 0.5)
            {
                Msg.position.z -= 0.25;
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

    // RESET
    StateHandler.setArmState(false);
    StateHandler.setMode(coexMode_Manual);
    StateHandler.waitNextState();

    return 0;
}


