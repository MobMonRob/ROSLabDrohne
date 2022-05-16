#ifndef TIMEOUTOK_H
#define TIMEOUTOK_H

#include "Domain/Timestamp.h"
#include "Domain/SafetyRequirement.h"


class TimeoutOK : public SafetyRequirement
{
public:
	TimeoutOK(Timestamp Threshold, Timestamp Time) : Threshold_(Threshold), Time_Last_(Time), Valid_(true) {};
	
	bool updateTime(Timestamp Time);
	bool meets() override { return this->Valid_; };
	void reset() { this->Valid_ = true; };

private:
	Timestamp Time_Last_;
	Timestamp Threshold_;
	bool Valid_;
};

#endif // TIMEOUTOK_H
