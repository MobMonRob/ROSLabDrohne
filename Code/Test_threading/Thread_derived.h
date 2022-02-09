#pragma once

#include "threading/Thread.h"


template <class T>
class Thread_derived :
    public Thread<T>
{
public:
    T runOnce() override;



private:


};




bool TEST_Thread_derived();
bool TEST_Thread_derived_runOnce();






