#ifndef UNIT_H
#define UNIT_H

#include <string>


class Unit
{
public:
	Unit(std::string Name) { this->UnitName_ = Name; };

	bool operator== (const Unit& U) const { return this->UnitName_ == U.UnitName_; };

	std::string getUnit() { return this->UnitName_; };

protected:
	std::string UnitName_;
};


// move into Unit.cpp?
const Unit Unit_Invalid("INVALID");

const Unit Unit_None("");

const Unit Unit_Length("m");
const Unit Unit_Velocity("m/s");
const Unit Unit_Acceleration("m/(s*s)");

const Unit Unit_AngleDeg("deg");
const Unit Unit_AngleVelDeg("deg/s");
const Unit Unit_AngleRad("rad");
const Unit Unit_AngleVelRad("rad/s");

const Unit Unit_Percent("%");

const Unit Unit_Force("N");
const Unit Unit_Force_Moment("Nm");

const Unit Unit_Pressure("N/(mm*mm)");
const Unit Unit_Pressure_mPa("mPa");

const Unit Unit_Frequence("1/s");
const Unit Unit_Frequence_RPM("1/min");


#endif // UNIT_H
