#ifndef COEXRC_H
#define COEXRC_H

#include "coex/coexRC_Transmitter.h"
#include "coex/coexRC_Receiver.h"


class coexRC : public coexRC_Transmitter, public coexRC_Receiver
{
public:
	coexRC(Joystick *Joystick, coexState *State, coexBattery *Battery);
};

#endif // COEXRC_H


