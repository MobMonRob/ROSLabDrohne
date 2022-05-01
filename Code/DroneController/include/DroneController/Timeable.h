#ifndef TIMEABLE_H
#define TIMEABLE_H

#include <string>

#include "Domain/Timestamp.h"


class Timeable
{
public:
	void setTime(Timestamp Time);

	Timestamp getTime() const { return this->Time_; };
	Timestamp getTimeLocal() const { return (this->getTime() > Timestamp()) ? this->getTime() - this->getTimeOffsetLocal() : Timestamp(-1); };
	Timestamp getTimeGlobal() const { return (this->getTime() > Timestamp()) ? this->getTime() - Timeable::getTimeOffsetGlobal() : Timestamp(-1); };
	
	Timestamp getTimeOffsetLocal() const { return this->OffsetLocal_; };
	static Timestamp getTimeOffsetGlobal() { return Timeable::OffsetGlobal_; };

	std::string getTimeLocalString() { return this->getTimeString(std::to_string(this->getTimeLocal().getTime().getValue()));};
	std::string getTimeGlobalString() { return this->getTimeString(std::to_string(this->getTimeGlobal().getTime().getValue())); };
	void resetTimeOffsetLocal() { this->OffsetLocal_ = Timestamp(); };

protected:
	void setTimeOffsetLocal(Timestamp Time);

private:
	static void setTimeOffsetGlobal(Timestamp Time);
	std::string getTimeString(std::string TimeString) { return std::string("[").append(TimeString).append("]"); };

private:
	Timestamp Time_;
	Timestamp OffsetLocal_;
	static Timestamp OffsetGlobal_;
};

#endif // TIMEABLE_H
