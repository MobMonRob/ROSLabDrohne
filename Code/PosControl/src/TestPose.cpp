#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

#include "coex/coexState.h"
#include "coex/coexBattery.h"
#include "coex/coexOrientation.h"


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
    coexOrientation Locator(&StateHandler, 3.5);

    ros::Publisher local_thurst_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);
    ros::Rate rate(20.0);
    ros::Duration TestTime(10.0);
    const double Height = .1;


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


    ros::Time last_request = ros::Time::now();
    ros::Time Start = ros::Time::now();
    ros::Time UpdateState = ros::Time::now();
	
	
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
        
        if (ros::Time::now() - UpdateState > ros::Duration(1))
        {
        	ROS_INFO("TestPoseControl");
            ROS_INFO("Ground = %f", Locator.getGroundClearance());
            ROS_INFO(StateHandler.getState().c_str());

            UpdateState = ros::Time::now();
        }



		local_thurst_pub.publish(Msg);

        ros::spinOnce();
        rate.sleep();
    }

    // RESET
    StateHandler.setArmState(false);
    StateHandler.setMode("MANUAL");
    StateHandler.waitNextState();

    return 0;
}


