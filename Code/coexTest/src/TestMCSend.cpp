#include <ros/ros.h>
#include <mavros_msgs/ManualControl.h>

#include "coex/coexState.h"
#include "coex/coexBattery.h"
#include "coex/coexOrientation.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;
    
    coexBattery Battery(15.6, 16.8, 15.7);
    coexState StateHandler(&Battery);
    coexOrientation Locator(&StateHandler, 3.5);
    
    ros::Publisher local_thurst_pub = nh.advertise<mavros_msgs::ManualControl>("mavros/manual_control/send", 10);
    ros::Rate rate(20.0);
    ros::Duration TestTime(10.0);
    const double Height = .1;

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
        ros::spinOnce();
        rate.sleep();
    }

    ros::Time last_request = ros::Time::now();
    ros::Time Start = ros::Time::now();
    ros::Time UpdateState = ros::Time::now();
    ros::Time ControlHeight = ros::Time::now();
    
    ROS_INFO("Battery at %f.", Battery.getPercentage());

    StateHandler.setMode(coexMode_Offboard);
    
    
    while(ros::ok() && ros::Time::now() - Start <= TestTime)
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

        if (ros::Time::now() - UpdateState >= ros::Duration(0.25))
        {
            ROS_INFO("TestMCSend");
            ROS_INFO("Ground = %f", Locator.getGroundClearance());
            ROS_INFO("Thrust = %f", Msg.z);
            ROS_INFO(StateHandler.getState().c_str());

            UpdateState = ros::Time::now();
        }

        if (ros::Time::now() - ControlHeight >= ros::Duration(0.1))
        {   // basic controller
            Msg.z += (Height - Locator.getGroundClearance()) / 100;

            ControlHeight = ros::Time::now();
        }


        local_thurst_pub.publish(Msg);

        ros::spinOnce();
        rate.sleep();
    }
    

    // Landing
    while (ros::ok() && Locator.getGroundClearance() > 0)
    {
        if (ros::Time::now() - ControlHeight > ros::Duration(0.25))
        {
            ROS_INFO("Ground = %f", Locator.getGroundClearance());
            Msg.z = 0.99 * Msg.z;

            ControlHeight = ros::Time::now();
        }

        local_thurst_pub.publish(Msg);

        ros::spinOnce();
        rate.sleep();
    }

    // RESET
    StateHandler.setArmState(false);
    StateHandler.setMode("MANUAL");
	
    return 0;
}


