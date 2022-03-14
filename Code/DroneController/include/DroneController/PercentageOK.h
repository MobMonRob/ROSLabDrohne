#ifndef PERCENTAGEOK_H
#define PERCENTAGEOK_H

#include "Abstraction/SafetyRequirement.h"

#include "DroneController/Batteryable.h"


class PercentageOK : public SafetyRequirement
{
public:
	PercentageOK(Batteryable* Battery, double Threshold) : Battery_(Battery), Threshold_(Threshold) {};
	
	bool meets() override { return (this->Battery_->getPercentage() >= this->Threshold_); };

private:
	Batteryable* Battery_;
	double Threshold_;
};

#endif // PERCENTAGEOK_H
