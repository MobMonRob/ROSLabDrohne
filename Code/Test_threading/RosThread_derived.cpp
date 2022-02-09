#include "RosThread_derived.h"

#include <iostream>
#include "Payload_Mock.h"



template<>
Payload_Mock RosThread_derived<Payload_Mock>::runOnce()
{
	this->getPayload().addCall("RosThread_derived::runOnce()");

	return RosThread::runOnce();
}

template<>
PayloadWrapper RosThread_derived<PayloadWrapper>::runOnce()
{
	this->getPayload().addCall("RosThread_derived::runOnce()");

	return RosThread::runOnce();
}

template<class T>
T RosThread_derived<T>::runOnce()
{
	return RosThread::runOnce();
}





template<>
PayloadWrapper RosThread_derived<PayloadWrapper>::runOnce(PayloadWrapper Payload)
{
	Payload.addCall("RosThread_derived::runOnce(T Payload)");

	return Payload;
}


template<class T>
T RosThread_derived<T>::runOnce(T Payload)
{
	std::cout << "Called: T RosThread_derived<T>::runOnce(T Payload)" << std::endl;



	return Payload;
}








bool TEST_RosThread_derived()
{
	std::cout << std::endl << std::endl;
	std::cout << "TEST_RosThread_derived" << std::endl;


	TEST_RosThread_derived_runOnce_Payload();
	TEST_RosThread_derived_runOnce_Payload_Multiple(2);
	TEST_RosThread_derived_setPayload();
	TEST_RosThread_derived_run();


	return false;
}


bool TEST_RosThread_derived_runOnce_Payload()
{
	RosThread_derived<PayloadWrapper> Thread1;
	Payload_Mock Payload;


	Thread1.runOnce(PayloadWrapper(&Payload));
	std::cout << Payload << std::endl;

	return (Payload.getHistorySize() == 1);
}

bool TEST_RosThread_derived_runOnce_Payload_Multiple(int Cycles)
{
	RosThread_derived<PayloadWrapper> Thread1;
	Payload_Mock Payload;
	PayloadWrapper Wrapper(&Payload);


	for (int i = 0; i < Cycles; i++)
	{
		Wrapper = Thread1.runOnce(Wrapper);
	}

	std::cout << Payload << std::endl;

	return (Payload.getHistorySize() == Cycles);
}

bool TEST_RosThread_derived_setPayload()
{
	RosThread_derived<PayloadWrapper> Thread1;
	Payload_Mock Payload;
	PayloadWrapper Wrapper(&Payload);


	Thread1.setPayload(Wrapper);
	std::cout << Payload << std::endl;

	return (Payload.getHistorySize() == 1);
}

bool TEST_RosThread_derived_run()
{
	RosThread_derived<PayloadWrapper> Thread1(100);
	Payload_Mock Payload;
	PayloadWrapper Wrapper(&Payload);


	Thread1.setPayload(Wrapper);

	Thread1.start();

	// quick and dirty delay
	for (int i = 0; i < 10000000; i++)
	{
	}

	Thread1.stop();

	std::cout << "Called " << Payload.getHistorySize() << " times." << std::endl;

	return (Payload.getHistorySize() == 1);
}

