#ifndef UNIT_H
#define UNIT_H

#include <string>


#define UNIT_INVALID std::string("invalid")


class Unit
{
public:
	Unit(std::string Name = UNIT_INVALID) { this->UnitName_ = Name; };

	bool operator== (const Unit& U) { return this->UnitName_ == U.UnitName_; };

	std::string getUnit() { return this->UnitName_; };

protected:
	std::string UnitName_;
};

#endif // UNIT_H
