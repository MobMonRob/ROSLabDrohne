#ifndef ROTOR_H
#define ROTOR_H

#include "Domain/Value.h"
#include "Domain/Vector3D.h"


class Rotor
{
public:
	Rotor() : C_T_(Value(Unit("??"), 0)), Diameter_(Value(Unit_Length, 0)), RotorSpeed_(Value(Unit_Frequence_RPM, 0)) {};
	Rotor(Value C_T, Value Diameter);
	
	void setRotorSpeed(Value RotorSpeed) { this->RotorSpeed_ = RotorSpeed; };

	Value getCT() { return this->C_T_; };
	Value getDiameter() { return this->Diameter_; };
	Value getRotorSpeed() { return this->RotorSpeed_; };
	Value getThrust(Value Density) { return Rotor::getThrust(this->getCT(), this->getDiameter(), Density, this->getRotorSpeed()); };

	static Value getThrust(Value C_T, Value Diameter, Value Density, Value RotorSpeed);

private:
	Value C_T_;
	Value Diameter_;
	Value RotorSpeed_;
};


#endif // ROTOR_H
