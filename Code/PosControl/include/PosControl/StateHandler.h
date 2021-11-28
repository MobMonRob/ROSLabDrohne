#ifndef STATEHANDLER_H
#define STATEHANDLER_H

#include "PosControl/State.h"
#include "PosControl/Ringbuffer.h"


class StateHandler : private Ringbuffer<State>
{
public:
	StateHandler(int MaxEntries = 1) : Ringbuffer(MaxEntries) {};

	void addEntry(State State) { this->addItem(State); };

	State getAvgState();

private:
};

#endif // STATEHANDLER_H
