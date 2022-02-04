#include "coex/coexRC.h"


coexRC::coexRC(Joystick *Joystick, coexState *State, coexBattery *Battery)
	: coexRC_Transmitter(Joystick, State, Battery),
	coexRC_Receiver(Joystick)
{
}


