#pragma once

#include <string>
#include <vector>
#include <iostream>



class Payload_Mock
{
public:
	Payload_Mock() {};
	Payload_Mock(const Payload_Mock& PM);
	
	void addCall(std::string CallingFunction) { this->CallHistory_.push_back(CallingFunction); };

	std::string getHistory();
	int getHistorySize() { return this->CallHistory_.size(); };

protected:
	std::vector<std::string> CallHistory_;
};


class PayloadWrapper
{
public:
	PayloadWrapper(Payload_Mock* PayloadPtr = nullptr) : PayloadPtr_(PayloadPtr){};
	PayloadWrapper(const PayloadWrapper& PW) : PayloadPtr_(PW.PayloadPtr_) {};
	
	

	void addCall(std::string CallingFunction);

	std::string getHistory();
	int getHistorySize();

private:
	Payload_Mock* PayloadPtr_;
};





std::ostream& operator<<(std::ostream& os, Payload_Mock obj);

std::ostream& operator<<(std::ostream& os, PayloadWrapper obj);


bool TEST_PayloadWrapper_copy();









