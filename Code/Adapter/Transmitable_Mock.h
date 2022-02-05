#ifndef TRANSMITABLE_MOCK_H
#define TRANSMITABLE_MOCK_H

#include "Adapter/Transmitable.h"


class Transmitable_Mock : public Transmitable
{
public:
	bool transmitAction(double pitch, double roll, double thrust, double yarn) { return false; };
};

#endif // TRANSMITABLE_MOCK_H