#ifndef INPUTABLE_H
#define INPUTABLE_H

#include "PosControl/Unit.h"


class Inputable
{
public:
	virtual Unit getInputUnit() { return Unit_Invalid; };
};

#endif // INPUTABLE_H

