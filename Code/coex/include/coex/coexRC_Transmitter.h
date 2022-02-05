#ifndef COEXRC_TRANSMITTER_H
#define COEXRC_TRANSMITTER_H

#include <ros/ros.h>
#include <mavros_msgs/ManualControl.h>


#include "Joystick.h"
#include "coexTransmitable.h"
#include "coexState.h"
#include "coexBattery.h"


class coexRC_Transmitter : public coexTransmitable
{
public:
	coexRC_Transmitter(Joystick *Joystick, coexState *State, coexBattery *Battery);
	~coexRC_Transmitter();
	
private:
	void transmit(mavros_msgs::ManualControl Msg);			// from Transmitable
	
private:
	ros::NodeHandle nh_;
	ros::Publisher PubRC_;
	
	Joystick *Joystick_;	
};

#endif // COEXRC_TRANSMITTER_H


