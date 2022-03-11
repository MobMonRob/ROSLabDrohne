#ifndef COEXTRANSMITABLE_H
#define COEXTRANSMITABLE_H

#include <mavros_msgs/ManualControl.h>

#include "Abstraction/FixedPoint.h"
#include "Application/Transmitable.h"

#include "coex/coexState.h"
#include "coex/coexBattery.h"


class coexTransmitable : public Transmitable
{
public:
	coexTransmitable() : coexTransmitable(nullptr, nullptr) {};
	coexTransmitable(coexState* State) : coexTransmitable(State, State->getBattery()) {};
	coexTransmitable(coexState *State, coexBattery *Battery);
	
	bool transmitAction(double pitch, double roll, double thrust, double yarn);
	bool transmitAction(mavros_msgs::ManualControl Msg);
	
protected:
	coexBattery* getBattery() const { return this->Battery_; };
	coexState* getState() const { return this->State_; };
	
	bool valid() const { return (this->State_ != nullptr && this->Battery_ != nullptr); };
	virtual void transmit(mavros_msgs::ManualControl Msg) = 0;
	
private:
	coexState *State_;
	coexBattery *Battery_;
};

#endif // COEXTRANSMITABLE_H
