#ifndef ACCELTOPOS_H
#define ACCELTOPOS_H

#include "Domain/Integral2.h"


class AccelToPos : public Integral2
{
public:
	AccelToPos(double InitPos = 0.0, double InitVel = 0.0)
		: Integral2(Unit_Acceleration, Unit_Velocity, Unit_Length, InitPos, InitVel) {};

};

#endif // ACCELTOPOS_H
