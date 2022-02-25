#include "Thread_derived.h"

#include "Payload_Mock.h"


template<>
inline Payload_Mock Thread_derived<Payload_Mock>::runOnce()
{
	Payload_Mock Payload;


	Payload.addCall("T Thread_derived<T>::runOnce()");

	return Payload;
}

template<class T>
inline T Thread_derived<T>::runOnce()
{
	Payload_Mock Payload;


	std::cout << "Called: T Thread_derived<T>::runOnce()" << std::endl;

	return T();
}








bool TEST_Thread_derived()
{
	TEST_Thread_derived_runOnce();


	return true;
}

bool TEST_Thread_derived_runOnce()
{
	Thread_derived<Payload_Mock> Thread1;
	Payload_Mock Payload = Thread1.runOnce();


	return (Payload.getHistorySize() == 1);
}






