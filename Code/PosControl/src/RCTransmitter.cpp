#include <PosControl/RCTransmitter.h>

#include <mavros_msgs/State.h>
#include <mavros_msgs/ManualControl.h>
#include <mavros_msgs/OverrideRCIn.h>
#include <mavros_msgs/CommandBool.h>


/* mavros_msgs::State
 * Subscriber Callback
 * used in ActionTransmitter::connect()
 * used in ActionTransmitter::isArmed()
*/
mavros_msgs::State current_state;

void callbackConnect(const mavros_msgs::State::ConstPtr& msg)
{
	current_state = *msg;
}



/* mavros_msgs::ManualControl
 * Publisher Message
 * minimum Frequency: 
*/
mavros_msgs::ManualControl ControlMsg;




/* ros::Time
 * Timestamp
 * reset ControlMsg, when no recent Update.
 * 
*/
ros::Time lastUpdate;





ros::Duration RCTransmitter::ControlTimeout_ = ros::Duration(5.0);

RCTransmitter::RCTransmitter()
{
	ROS_INFO("Started ActionTransmitter");
	
	this->PubMavRos_ = this->nh_.advertise<mavros_msgs::OverrideRCIn>("mavros/rc/override", 10);
	this->SubState_ = this->nh_.subscribe<mavros_msgs::State>("mavros/state", 10, callbackConnect);	
}



void RCTransmitter::transmitAction(double pitch, double roll, double thrust, double yarn)
{
	mavros_msgs::ManualControl MsgUpdate;
	/* https://mavlink.io/en/services/manual_control.html
	 * x	pitch	forward/nose-down	backward/nose-up
	 * y	roll	right-down			left-down
	 * z	thrust	positive			negative
	 * r	yaw		counter-clockwise	clockwise
	 */
	
	MsgUpdate.x = pitch;
	MsgUpdate.y = roll;
	MsgUpdate.z = (thrust >= 0 ? thrust : 0);
	MsgUpdate.r = yarn;
	
	lastUpdate = ros::Time::now();
	
	ROS_INFO("Thrust=%f, Pitch=%f, Roll=%f, Yarn=%f", MsgUpdate.z, MsgUpdate.x, MsgUpdate.y, MsgUpdate.r);
	
	ControlMsg = MsgUpdate;
}

void RCTransmitter::transmitDifference(double pitch, double roll, double thrust, double yarn)
{
	this->transmitAction(ControlMsg.x + pitch,
		ControlMsg.y + roll,
		ControlMsg.z + thrust,
		ControlMsg.r + yarn);
}


bool RCTransmitter::connect()
{
	ros::Rate rate(20.0);
	
	
	while(ros::ok() && !current_state.connected)
	{
        ros::spinOnce();
        rate.sleep();
    }
	
	return ros::ok();
}


void RCTransmitter::spin()
{
	ros::spinOnce();
	
	this->isArmed();
	this->isUpdated();
	
	{
		mavros_msgs::OverrideRCIn RCMsg;
		/* https://mavlink.io/en/messages/common.html#RC_CHANNELS_OVERRIDE
		 * 0%	=> 1000
		 * 100%	=> 2000
		 */
		
		/* Channel	Function	ManualControl
		 * Ch1		Roll		y
		 * Ch2		Pitch		x
		 * Ch3		Trottle		z
		 * Ch4		Yarn		r
		 * Ch5		VRA
		 * Ch6		VRB
		 */
		
		RCMsg.channels[0] = ControlMsg.y/2 + 1500;  // *500/1000 => /2	// 1500 => Mitte Intervall
		RCMsg.channels[1] = ControlMsg.x/2 + 1500;  // *500/1000 => /2	// 1500 => Mitte Intervall
		RCMsg.channels[2] = ControlMsg.z + 1000;
		RCMsg.channels[3] = ControlMsg.r/2 + 1500;  // *500/1000 => /2	// 1500 => Mitte Intervall
		
		this->PubMavRos_.publish(RCMsg);
	}
	
	ros::spinOnce();
}


bool RCTransmitter::isArmed(bool autoArm)
{
	bool armed = current_state.armed;
	
	
	if (!armed && autoArm)
	{
		ros::ServiceClient arming_client = this->nh_.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
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
	}
	
	ros::spinOnce();
	
	return current_state.armed;
}



bool RCTransmitter::isUpdated()
{
	bool recentUpdate = (ros::Time::now() - lastUpdate) <= RCTransmitter::ControlTimeout_;
	
	
	if (!recentUpdate)
	{
		this->transmitAction(0, 0, ControlMsg.z - 10, 0);
	}
	
	return recentUpdate;
}


