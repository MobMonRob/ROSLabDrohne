#ifndef UNIT_H
#define UNIT_H

#include <string>


class Unit
{
public:
	Unit(std::string Name = "invalid") { this->UnitName_ = Name; };

	bool operator== (const Unit& U) { return this->UnitName_ == U.UnitName_; };

	std::string getUnit() { return this->UnitName_; };

protected:
	std::string UnitName_;
};

#endif // UNIT_H
