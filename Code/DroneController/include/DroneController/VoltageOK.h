#ifndef VOLTAGEOK_H
#define VOLTAGEOK_H

#include "Abstraction/SafetyRequirement.h"

#include "DroneController/Batteryable.h"


class VoltageOK : public SafetyRequirement
{
public:
	VoltageOK(Batteryable* Battery, double Threshold) : Battery_(Battery), Threshold_(Threshold) {};
	
	bool meets() override { return (this->Battery_->getVoltage() >= this->Threshold_); };

private:
	Batteryable* Battery_;
	double Threshold_;
};

#endif // VOLTAGEOK_H
