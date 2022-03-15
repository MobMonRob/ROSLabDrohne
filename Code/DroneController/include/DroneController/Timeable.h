#ifndef TIMEABLE_H
#define TIMEABLE_H

#include "Abstraction/Timestamp.h"


class Timeable
{
public:
	virtual Timestamp getTime() { return this->Time_; };

protected:
	void setTime(Timestamp Time) { this->Time_ = Time; };

private:
	Timestamp Time_;
};

#endif // TIMEABLE_H
