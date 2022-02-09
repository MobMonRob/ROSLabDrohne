#ifndef CALLABLE_H
#define CALLABLE_H

#include "Calling.h"


class Callable
{
public:
	virtual bool call(Calling* Caller) = 0;
};

#endif // CALLABLE_H


