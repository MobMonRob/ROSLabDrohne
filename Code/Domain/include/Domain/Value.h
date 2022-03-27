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

	Value operator+ (const Value& V);
	Value operator- (const Value& V);
	Value operator* (FixedPoint<Accuracy_Value> Multiplier) { return Value(this->getUnit(), this->getValue() * Multiplier); };
	Value operator/ (double Divisor);
	Value operator/ (FixedPoint<Accuracy_Value> Divisor) { return Value(this->getUnit(), this->getValue() / Divisor); };
	void operator+= (const Value& V);

	FixedPoint<Accuracy_Value> getValue() { return this->Value_; };
	Unit getUnit() { return this->Unit_; };
	std::string getString();

protected:
	FixedPoint<Accuracy_Value> Value_;
	Unit Unit_;
};

#endif // VALUE_H

