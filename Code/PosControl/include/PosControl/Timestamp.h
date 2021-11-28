#ifndef Timestamp_H
#define Timestamp_H


class Timestamp
{
public:
	Timestamp(double Time = 0.0) : Time_(Time) {};

	bool operator==(const Timestamp& T) { return this->getTime() == T.Time_; };

	double getTime() { return this->Time_; };

protected:
	double Time_;
};

#endif // Timestamp_H
