#ifndef ACTIONTRANSMITTER_H
#define ACTIONTRANSMITTER_H

#include <ros/ros.h>

#include <PosControl/Transmitable.h>


class ActionTransmitter : public Transmitable
{
public:
	ActionTransmitter();
	
	void transmitAction(double pitch, double roll, double thrust, double yarn);	// from Transmitable
	
private:
	bool connect();
	void loop();
	bool isArmed(bool autoArm = false);
	bool isUpdated();
	
	ros::NodeHandle nh_;
	ros::Publisher PubMavRos_;		// Publisher to mavros
	ros::Subscriber SubState_;
	
	static ros::Duration ControlTimeout_;
};

#endif // ACTIONTRANSMITTER_H
