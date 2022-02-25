#ifndef ANGVELTOANG_H
#define ANGVELTOANG_H

#include "Domain/Integral1.h"


class AngVelToAng : public Integral1
{
public:
	AngVelToAng(double InitAng = 0.0)
		: Integral1(Unit_AngleVelDeg, Unit_AngleDeg, InitAng) {};

};

#endif // ANGVELTOANG_H
