#ifndef COEXMC_H
#define COEXMC_H

#include <ros/ros.h>

#include <mavros_msgs/ManualControl.h>

#include "threading/AutoPublisher.h"

#include "coexTransmitable.h"
#include "coexState.h"
#include "coexBattery.h"

/*
 *	https://mavlink.io/en/services/manual_control.html 		this Intervall
 *	x	pitch	forward/nose-down	backward/nose-up		-1 ... 1
 *	y	roll	right-down			left-down				-1 ... 1
 *	z	thrust	positive			negative				 0 ... 1
 *	r	yaw		counter-clockwise	clockwise				-1 ... 1
 */


class coexMC : public coexTransmitable
{
public:
	coexMC(coexState *State, coexBattery *Battery);
	~coexMC();
	
private:
	void transmit(mavros_msgs::ManualControl Msg);			// from Transmitable
	
private:
	ros::Publisher PubMC_;									// Publisher to mavros
	
	AutoPublisher<mavros_msgs::ManualControl> Pub_;
};

#endif // COEXMC_H
