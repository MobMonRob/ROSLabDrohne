#ifndef INPUTABLE_H
#define INPUTABLE_H

#include "Abstraction/Unit.h"


class Inputable
{
public:
	virtual Unit getInputUnit() { return Unit_Invalid; };
};

#endif // INPUTABLE_H

