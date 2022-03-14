#ifndef BATTERYABLE_H
#define BATTERYABLE_H

#include "Abstraction/SafetyProvider.h"


class Batteryable : public SafetyProvider
{
public:
	Batteryable(double VoltageThreshold = 42.0) : VoltageThreshold_(VoltageThreshold) {};
	
	virtual double getVoltage() { return 0.0; };
	virtual double getPercentage() { return 0.0; };
	bool isSafe() { return this->getVoltage() > this->VoltageThreshold_; };

private:
	double VoltageThreshold_;
};

#endif // BATTERYABLE_H
