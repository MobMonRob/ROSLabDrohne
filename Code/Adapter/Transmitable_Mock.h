#ifndef TRANSMITABLE_MOCK_H
#define TRANSMITABLE_MOCK_H

#include "Application/Transmitable.h"


class Transmitable_Mock : public Transmitable
{
public:
	bool transmitAction(FixedPoint<Accuracy_Value> pitch, FixedPoint<Accuracy_Value> roll, FixedPoint<Accuracy_Value> thrust, FixedPoint<Accuracy_Value> yarn) { return false; };
};

#endif // TRANSMITABLE_MOCK_H