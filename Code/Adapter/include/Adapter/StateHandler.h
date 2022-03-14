#ifndef STATEHANDLER_H
#define STATEHANDLER_H


#include "Abstraction/Optional.h"
#include "Abstraction/Ringbuffer.h"
#include "DroneController/IMUState.h"



class StateHandler : private Ringbuffer<IMUState>
{
public:
	StateHandler(int MaxEntries = 1) : Ringbuffer<IMUState>(MaxEntries) {};

	void addEntry(IMUState State) { this->addItem(State); };

	int getSize() { return Ringbuffer::getSize(); };
	IMUState getAvgState();

	void clear() { Ringbuffer<IMUState>::clear(); };

};

#endif // STATEHANDLER_H
