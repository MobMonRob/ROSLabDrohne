#pragma once


#include "threading/rosThread.h"

template <class T>
class RosThread_derived :
    public RosThread<T>
{
public:
    RosThread_derived(double Frequency = 1) : RosThread<T>(Frequency) {};

    T runOnce() override;
    T runOnce(T Payload) override;
};




class Test_Mock
{
};



bool TEST_RosThread_derived();
bool TEST_RosThread_derived_runOnce_Payload();
bool TEST_RosThread_derived_runOnce_Payload_Multiple(int Cycles);
bool TEST_RosThread_derived_setPayload();
bool TEST_RosThread_derived_run();




