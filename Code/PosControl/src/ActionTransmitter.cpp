#include <PosControl/ActionTransmitter.h>

#include <mavros_msgs/State.h>
#include <mavros_msgs/ManualControl.h>


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
ros::Time lastUpdate = ros::Time::now();





ros::Duration ActionTransmitter::ControlTimeout_ = ros::Duration(5.0);

ActionTransmitter::ActionTransmitter()
{
	this->PubMavRos_ = this->nh_.advertise<mavros_msgs::ManualControl>("manual_control/send", 10);
	this->SubState_ = this->nh_.subscribe<mavros_msgs::State>("mavros/state", 10, callbackConnect);	
	
	if (this->connect())
	{
		this->loop();
	}
}



void ActionTransmitter::transmitAction(double pitch, double roll, double thrust, double yarn)
{
	mavros_msgs::ManualControl MsgUpdate;
	/*
	https://mavlink.io/en/services/manual_control.html
	x	pitch	forward/nose-down	backward/nose-up
	y	roll	right-down			left-down
	z	thrust	positive			negative
	r	yaw		counter-clockwise	clockwise
	*/
	
	MsgUpdate.x = pitch;
	MsgUpdate.y = roll;
	MsgUpdate.z = thrust;
	MsgUpdate.r = yarn;
	
	lastUpdate = ros::Time::now();
	ControlMsg = MsgUpdate;
}


bool ActionTransmitter::connect()
{
	ros::Rate rate(20.0);
	
	
	while(ros::ok() && !current_state.connected)
	{
        ros::spinOnce();
        rate.sleep();
    }
	
	return ros::ok();
}


void ActionTransmitter::loop()
{
	ros::Rate rate(50.0);
	
	while(ros::ok())
	{
		this->isArmed();
		this->isUpdated();
		
		this->PubMavRos_.publish(ControlMsg);
		
		ros::spinOnce();
        rate.sleep();
	}
}


bool ActionTransmitter::isArmed(bool autoArm)
{
	bool armed = current_state.armed;
	
	
	if (!armed && autoArm)
	{
		// Call COEX ArmNode
	}
	
	return isArmed(false);
}


bool ActionTransmitter::isUpdated()
{
	bool recentUpdate = (ros::Time::now() - lastUpdate) > ActionTransmitter::ControlTimeout_;
	
	
	if (!recentUpdate)
	{
		mavros_msgs::ManualControl NullMsg;
		
		
		ControlMsg = NullMsg;
	}
	
	return recentUpdate;
}


