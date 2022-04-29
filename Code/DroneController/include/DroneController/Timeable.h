#ifndef TIMEABLE_H
#define TIMEABLE_H

#include <string>

#include "Domain/Timestamp.h"


class Timeable
{
public:
	void setTime(Timestamp Time);

	Timestamp getTime() const { return this->Time_; };
	Timestamp getTimeLocal() const { return (this->getTimeOffsetLocal() > Timestamp()) ? this->getTime() - this->getTimeOffsetLocal() : Timestamp(); };
	Timestamp getTimeGlobal() const { return (this->getTimeOffsetGlobal() > Timestamp()) ? this->getTime() - Timeable::getTimeOffsetGlobal() : Timestamp(); };
	
	Timestamp getTimeOffsetLocal() const { return this->OffsetLocal_; };
	static Timestamp getTimeOffsetGlobal() { return Timeable::OffsetGlobal_; };

	std::string getTimeLocalString() { return std::string("[").append(std::to_string(this->getTimeLocal().getTime().getValue())).append("]"); };
	void resetTimeOffsetLocal() { this->OffsetLocal_ = Timestamp(); };

protected:
	void setTimeOffsetLocal(Timestamp Time);

private:
	static void setTimeOffsetGlobal(Timestamp Time);

private:
	Timestamp Time_;
	Timestamp OffsetLocal_;
	static Timestamp OffsetGlobal_;
};

#endif // TIMEABLE_H
