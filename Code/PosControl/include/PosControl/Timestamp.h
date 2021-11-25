#ifndef Timestamp_H
#define Timestamp_H


class Timestamp
{
public:
	Timestamp(double Time = 0.0) : Time_(Time) {};

	double getTime() { return this->Time_; };

protected:
	double Time_;
};

#endif // Timestamp_H
