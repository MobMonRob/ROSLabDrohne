#include <ros/ros.h>
#include <mavros_msgs/OverrideRCIn.h>

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
	
    ros::Publisher local_thurst_pub = nh.advertise<mavros_msgs::OverrideRCIn>("mavros/rc/override", 10);
    ros::Rate rate(20.0);
    ros::Duration TestTime(10.0);
    const double Height = .1;


    // https://mavlink.io/en/messages/common.html#RC_CHANNELS_OVERRIDE
	mavros_msgs::OverrideRCIn Msg;	
    Msg.channels[0] = 1500; //Msg.y
    Msg.channels[1] = 1500; //Msg.x
    Msg.channels[2] = 1100; //Msg.z // ~ 10% Thrust
    Msg.channels[3] = 1500; //Msg.r
	

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

    ros::Time last_request = ros::Time::now();
    ros::Time Start = ros::Time::now();
    ros::Time UpdateState = ros::Time::now();
    ros::Time UpdateOFFBOARD = ros::Time::now();
    ros::Time ControlHeight = ros::Time::now();

    ROS_INFO("Battery at %f.", Battery.getPercentage());

    StateHandler.setMode(coexMode_Offboard);
    StateHandler.waitNextState();

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

            StateHandler.setMode(coexMode_Offboard);

            last_request = ros::Time::now();
        }

        if (ros::Time::now() - UpdateOFFBOARD > ros::Duration(.25))
        {
            StateHandler.setMode(coexMode_Offboard);

            UpdateOFFBOARD = ros::Time::now();
        }

        if (ros::Time::now() - UpdateState > ros::Duration(1))
        {
            ROS_INFO("TestRCOverride");
            ROS_INFO(StateHandler.getState().c_str());

            UpdateState = ros::Time::now();
        }

        if (ros::Time::now() - ControlHeight >= ros::Duration(0.1))
        {   // basic controller
            Msg.channels[2] += (Height - Locator.getGroundClearance()) / 100;

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


