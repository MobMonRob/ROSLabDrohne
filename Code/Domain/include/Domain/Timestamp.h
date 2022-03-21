#ifndef Timestamp_H
#define Timestamp_H


#include "Domain/FixedPoint.h"



class Timestamp
{
public:
	Timestamp(FixedPoint<Accuracy_Time> Time = FixedPoint<Accuracy_Time>()) : Time_(Time) {};

	bool operator==(const Timestamp& T) { return this->Time_ == T.Time_; };
	bool operator==(const Timestamp& T) const { return this->Time_ == T.Time_; };
	bool operator!=(const Timestamp& T) { return !this->operator==(T); };
	bool operator<(const Timestamp& T) { return this->getTime() < T.Time_; };
	bool operator<=(const Timestamp& T) { return this->getTime() <= T.Time_; };
	bool operator>(const Timestamp& T) { return this->getTime() > T.Time_; };
	bool operator>=(const Timestamp& T) { return this->getTime() >= T.Time_; };

	FixedPoint<Accuracy_Time> getTime() { return this->Time_; };

protected:
	FixedPoint<Accuracy_Time> Time_;
};

#endif // Timestamp_H
