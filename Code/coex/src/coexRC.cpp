#include "coex/coexRC.h"


coexRC::coexRC(Joystick *Joystick, coexState *State, coexBattery *Battery)
	: coexRC_Transmitter(State, Joystick),
	coexRC_Receiver(Joystick)
{
}


