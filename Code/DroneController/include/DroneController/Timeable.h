#ifndef TIMEABLE_H
#define TIMEABLE_H

#include "Domain/Timestamp.h"


class Timeable
{
public:
	Timeable(Timestamp TimeOffset = Timestamp()) {};
	
	virtual Timestamp getTime() { return this->Time_ - Timeable::getTimeOffset(); };

	static Timestamp getTimeOffset() { return Timeable::TimeOffset_; };

protected:
	void setTime(Timestamp Time);

private:
	static void setTimeOffset(Timestamp Time) { Timeable::TimeOffset_ = Time; };

private:
	Timestamp Time_;
	static Timestamp TimeOffset_;
};

#endif // TIMEABLE_H
