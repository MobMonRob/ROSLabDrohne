#ifndef RCTRANSMITTER_H
#define RCTRANSMITTER_H

#include <ros/ros.h>

#include <PosControl/Transmitable.h>


class RCTransmitter : public Transmitable
{
public:
	RCTransmitter();
	
	void transmitAction(double pitch, double roll, double thrust, double yarn);	// from Transmitable
	void transmitDifference(double pitch, double roll, double thrust, double yarn);
	
	void spin();
	
private:
	bool connect();
	bool isArmed(bool autoArm = false);
	bool isUpdated();
	
	ros::NodeHandle nh_;
	ros::Publisher PubMavRos_;		// Publisher to mavros
	ros::Subscriber SubState_;
	
	static ros::Duration ControlTimeout_;
};

#endif // RCTRANSMITTER_H
