#ifndef UNIT_H
#define UNIT_H

#include <string>


class Unit
{
public:
	Unit(std::string Name) { this->UnitName_ = Name; };

	bool operator== (const Unit& U) { return this->UnitName_ == U.UnitName_; };

	std::string getUnit() { return this->UnitName_; };

protected:
	std::string UnitName_;
};


// move into Unit.cpp?
const Unit Unit_Invalid("INVALID");

const Unit Unit_Length("m");
const Unit Unit_Velocity("m/s");
const Unit Unit_Acceleration("m/s²");

const Unit Unit_AngleDeg("°");
const Unit Unit_AngleRad("rad");

const Unit Unit_Percent("%");

#endif // UNIT_H
