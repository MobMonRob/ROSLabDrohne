#ifndef STATEHANDLER_H
#define STATEHANDLER_H


#include "Abstraction/Optional.h"
#include "Abstraction/Ringbuffer.h"
#include "Application/State.h"



class StateHandler : private Ringbuffer<State>
{
public:
	StateHandler(int MaxEntries = 1) : Ringbuffer<State>(MaxEntries) {};

	void addEntry(State State) { this->addItem(State); };

	int getSize() { return Ringbuffer::getSize(); };
	State getAvgState();

};

#endif // STATEHANDLER_H
