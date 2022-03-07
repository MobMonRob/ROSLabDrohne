#include "coex/coexTransmitable.h"


coexTransmitable::coexTransmitable(coexState *State, coexBattery *Battery)
{
	this->State_ = State;
	this->Battery_ = Battery;
}


bool coexTransmitable::transmitAction(FixedPoint<Accuracy_Value> pitch, FixedPoint<Accuracy_Value> roll, FixedPoint<Accuracy_Value> thrust, FixedPoint<Accuracy_Value> yarn)
{
	mavros_msgs::ManualControl Msg;
	/*
	https://mavlink.io/en/services/manual_control.html
	x	pitch	forward/nose-down	backward/nose-up
	y	roll	right-down			left-down
	z	thrust	positive			negative
	r	yaw		counter-clockwise	clockwise
	*/
	
	Msg.x = pitch.getValue();
	Msg.y = roll.getValue();
	Msg.z = thrust.getValue();
	Msg.r = yarn.getValue();
	
	return this->transmitAction(Msg);
}

bool coexTransmitable::transmitAction(mavros_msgs::ManualControl Msg)
{
	// check for Battery & State
	
	
	this->transmit(Msg);
	
	return true;
}
