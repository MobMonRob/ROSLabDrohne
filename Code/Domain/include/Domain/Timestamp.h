#ifndef Timestamp_H
#define Timestamp_H


#include "Domain/FixedPoint.h"



class Timestamp
{
public:
	Timestamp(FixedPoint<Accuracy_Time> Time = FixedPoint<Accuracy_Time>()) : Time_(Time) {};
	//Timestamp(FixedPoint<0> Seconds, FixedPoint<0> NanoSeconds = FixedPoint<0>()) {};

	bool operator==(const Timestamp& T) { return this->Time_ == T.Time_; };
	bool operator==(const Timestamp& T) const { return this->Time_ == T.Time_; };
	bool operator!=(const Timestamp& T) { return !this->operator==(T); };
	bool operator<(const Timestamp& T) { return this->getTime() < T.Time_; };
	bool operator<=(const Timestamp& T) { return this->getTime() <= T.Time_; };
	bool operator>(const Timestamp& T) { return this->getTime() > T.Time_; };
	bool operator>=(const Timestamp& T) { return this->getTime() >= T.Time_; };
	Timestamp operator+(const Timestamp& T) { return Timestamp(this->getTime() + T.Time_); };
	Timestamp operator-(const Timestamp& T) { return Timestamp(this->getTime() - T.Time_); };
	void operator-=(const Timestamp& T) { this->getTime() -= T.Time_; };

	FixedPoint<Accuracy_Time> getTime() const { return this->Time_; };

protected:
	FixedPoint<Accuracy_Time> Time_;
};

#endif // Timestamp_H
