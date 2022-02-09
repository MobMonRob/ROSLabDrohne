#include "Payload_Mock.h"




Payload_Mock::Payload_Mock(const Payload_Mock& PM)
{
	for (int i = 0; i < PM.CallHistory_.size(); i++)
	{
		this->CallHistory_.push_back(PM.CallHistory_.at(i));
	}
}



std::string Payload_Mock::getHistory()
{
	std::string ReturnString;


	for (int i = 0; i < this->CallHistory_.size(); i++)
	{
		if (ReturnString.size() > 0)
		{
			ReturnString.append(" => ");
		}

		ReturnString.append(this->CallHistory_.at(i));
	}

	return ReturnString;
}

std::ostream& operator<<(std::ostream& os, Payload_Mock obj)
{
	os << "Call History of Payload: " << obj.getHistory();

	return os;
}










void PayloadWrapper::addCall(std::string CallingFunction)
{
	if (this->PayloadPtr_ != nullptr)
	{
		this->PayloadPtr_->addCall(CallingFunction);
	}
}

std::string PayloadWrapper::getHistory()
{
	if (this->PayloadPtr_ != nullptr)
	{
		return this->PayloadPtr_->getHistory();
	}
	else
	{
		return std::string();
	}
}

int PayloadWrapper::getHistorySize()
{
	if (this->PayloadPtr_ != nullptr)
	{
		return this->PayloadPtr_->getHistorySize();
	}
	else
	{
		return -1;
	}
}

std::ostream& operator<<(std::ostream& os, PayloadWrapper obj)
{
	os << "Call History of Payload: " << obj.getHistory();

	return os;
}



bool TEST_PayloadWrapper_copy()
{
	Payload_Mock Payload;
	PayloadWrapper Wrapper1(&Payload);
	PayloadWrapper Wrapper2(Wrapper1);


	Payload.addCall("Who Knows what...");

	return (Wrapper1.getHistorySize() == 1 && Wrapper1.getHistorySize() == Wrapper2.getHistorySize());
}









