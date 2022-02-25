#include "coex/coexTransmitable.h"


coexTransmitable::coexTransmitable(coexState *State, coexBattery *Battery)
{
	this->State_ = State;
	this->Battery_ = Battery;
}


bool coexTransmitable::transmitAction(double Pitch, double Roll, double Thrust, double Yarn)
{
	mavros_msgs::ManualControl Msg;
	/*
	https://mavlink.io/en/services/manual_control.html
	x	pitch	forward/nose-down	backward/nose-up
	y	roll	right-down			left-down
	z	thrust	positive			negative
	r	yaw		counter-clockwise	clockwise
	*/
	
	Msg.x = Pitch;
	Msg.y = Roll;
	Msg.z = Thrust;
	Msg.r = Yarn;
	
	return this->transmitAction(Msg);
}

bool coexTransmitable::transmitAction(mavros_msgs::ManualControl Msg)
{
	// check for Battery & State
	
	
	this->transmit(Msg);
	
	return true;
}
