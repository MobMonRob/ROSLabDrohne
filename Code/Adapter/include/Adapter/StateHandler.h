#ifndef STATEHANDLER_H
#define STATEHANDLER_H


#include "Domain/Optional.h"
#include "Domain/Ringbuffer.h"
#include "DroneController/IMUState.h"



class StateHandler : private Ringbuffer<IMUState>
{
public:
	StateHandler(std::size_t MaxEntries = 1) : Ringbuffer<IMUState>(MaxEntries) {};

	void addEntry(IMUState State) { this->addItem(State); };

	std::size_t getSize() { return Ringbuffer::getSize(); };
	std::size_t getSizeMax() { return Ringbuffer::getSizeMax(); };
	Timestamp getTime();
	IMUState getAvgState();
	IMUState getMedianState();
	IMUState getVariance();
	
	void clear() { Ringbuffer<IMUState>::clear(); };

private:
	static FixedPoint<Accuracy_Value> calcVariance(std::vector<FixedPoint<Accuracy_Value>> Data);
};

#endif // STATEHANDLER_H
