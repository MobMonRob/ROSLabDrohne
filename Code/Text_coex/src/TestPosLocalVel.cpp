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

int main(int argc, char** argv)
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
    const double Height = .15;

    // Values in m/s
    mavros_msgs::PositionTarget Msg;
    Msg.velocity.z = 0.02;


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


    ROS_INFO("Battery at %f%", Battery.getPercentage());

    StateHandler.setMode(coexMode_Offboard);
    StateHandler.setArmState(true);

    bool Shutdown = false;

    while (ros::ok() && ros::Time::now() - Start <= TestTime)
    {
        if (ros::Time::now() - Alive >= ros::Duration(0.25))
        {
            StateHandler.setMode(coexMode_Offboard);

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
            ROS_INFO("TestPosLocalVel");
            ROS_INFO("Ground = %f", Locator.getGroundClearance());
            ROS_INFO(StateHandler.getState().c_str());

            UpdateState = ros::Time::now();
        }

        if (ros::Time::now() - ControlHeight >= ros::Duration(0.1))
        {
            if (Locator.getGroundClearance() > Height)
            {
                Msg.velocity.z = 0;
            }

            ControlHeight = ros::Time::now();
        }

        if (Locator.getGroundClearance() > 2 * Height)
        {
            ROS_WARN("SECURITY SHUTDOWN - Height");
            Shutdown = true;

            break;
        }

        if (ros::Time::now() - Locator.getTime_Ground() > ros::Duration(0.5))
        {
            ROS_WARN("SECURITY SHUTDOWN - Locator Timeout");
            Shutdown = true;

            break;
        }

        local_thurst_pub.publish(Msg);

        ros::spinOnce();
        rate.sleep();
    }

    if (!Shutdown)
    {
        // Landing
        ControlHeight = ros::Time::now();
        Msg.velocity.z = -0.02;

        while (ros::ok() && Locator.getGroundClearance() > 0)
        {
            if (ros::Time::now() - ControlHeight >= ros::Duration(0.1))
            {   // basic controller
                ROS_INFO("Ground = %f", Locator.getGroundClearance());

                ControlHeight = ros::Time::now();
            }

            local_thurst_pub.publish(Msg);

            ros::spinOnce();
            rate.sleep();
        }
    }

    // RESET
    Msg.velocity.z = 0;
    local_thurst_pub.publish(Msg);

    StateHandler.setArmState(false);
    StateHandler.setMode(coexMode_Manual);
    StateHandler.waitNextState();

    return 0;
}


