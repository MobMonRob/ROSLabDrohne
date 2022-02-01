#ifndef COEXSTATE_H
#define COEXSTATE_H

#include <ros/ros.h>

#include <string>
#include <map>

#include <mavros_msgs/State.h>

#include "Caller.h"


class coexState : public Caller
{
public:
	coexState();
	
	bool setMode(std::string Mode);
	bool setArmState(bool arming);
	
	bool getConnected();
	bool getArmed();
	std::string getSystemStatus();
	double getTime() { return this->State_.header.stamp.toSec();};
	
	void cbState(const mavros_msgs::State::ConstPtr& State);	
	
private:
	void initSystemStatus();
	
private:
	ros::NodeHandle nh_;
	ros::Subscriber SubState_;
	
	mavros_msgs::State State_;
	std::map<int, std::string> SystemStatus_;
};

#endif // COEXSTATE_H


