#include <ros/ros.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandBool.h>









mavros_msgs::State current_state;


void state_cb(const mavros_msgs::State::ConstPtr& msg)
{
	current_state = *msg;
}




int main(int argc, char** argv)
{
	ros::init(argc, argv, "ArmClover");
	ros::NodeHandle nh;

	ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, state_cb);
	ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");

	ros::Rate rate(20.0);

	// wait for FCU connection
	while(ros::ok() && !current_state.connected)
	{
		ros::spinOnce();
		rate.sleep();
	}





	mavros_msgs::CommandBool arm_cmd;
	arm_cmd.request.value = true;
	arm_cmd.response.success = false;


	if(arming_client.call(arm_cmd))
	{
		if (arm_cmd.response.success)
		{
			ROS_INFO("Vehicle armed");
		}
		else
		{
			ROS_ERROR("Arming denied!");
		}
	}
	else
	{
		ROS_ERROR("Call denied!");
	}


	return 0;
}


