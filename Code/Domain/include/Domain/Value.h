#ifndef VALUE_H
#define VALUE_H

#include <string>

#include "Domain/FixedPoint.h"
#include "Domain/Unit.h"


class Value
{
public:
	Value(Unit Unit = Unit_Invalid, FixedPoint<Accuracy_Value> Value = FixedPoint<Accuracy_Value>()) : Unit_(Unit), Value_(Value) {};

	bool operator== (const Value& V);
	bool operator== (const Value& V) const;
	bool operator<(const Value& V) const { return this->Value_ < V.Value_; };
	bool operator>(const Value& V) const { return this->Value_ > V.Value_; };

	Value operator+ (const Value& V);
	Value operator- (const Value& V);
	Value operator* (const Value& V) { return Value(this->getUnit(), this->getValue() * V.getValue()); };
	Value operator* (FixedPoint<Accuracy_Value> Multiplier) { return Value(this->getUnit(), this->getValue() * Multiplier); };
	Value operator/ (const Value& V) { return Value(this->getUnit(), this->getValue() / V.getValue()); };
	Value operator/ (double Divisor);
	Value operator/ (FixedPoint<Accuracy_Value> Divisor) { return Value(this->getUnit(), this->getValue() / Divisor); };
	void operator+= (const Value& V);

	FixedPoint<Accuracy_Value> getValue() const { return this->Value_; };
	Unit getUnit() const { return this->Unit_; };
	std::string getString();

protected:
	FixedPoint<Accuracy_Value> Value_;
	Unit Unit_;
};



const Value Value_GravitationConstant(Unit_Acceleration, 9.816);
const Value Value_RADToDEG(Unit("°/rad"), FixedPoint<Accuracy_Value>(180)/PI);
const Value Value_DEGToRAD(Unit("°/rad"), PI/FixedPoint<Accuracy_Value>(180));

#endif // VALUE_H

