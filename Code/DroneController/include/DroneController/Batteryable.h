#ifndef BATTERYABLE_H
#define BATTERYABLE_H

#include "Abstraction/SafetyProvider.h"
#include "DroneController/Timeable.h"


class Batteryable : public SafetyProvider, public Timeable
{
public:
	Batteryable(double PercentageThreshold);
	
	virtual double getVoltage() { return 0.0; };
	virtual double getPercentage() { return 0.0; };
};

#endif // BATTERYABLE_H
