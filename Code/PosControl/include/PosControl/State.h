#ifndef STATE_H
#define STATE_H




#include "PosControl/Timestamp.h"
#include "PosControl/Vector3D.h"

class State
{
public:
	State(Vector3D Translative, Vector3D Angular, Timestamp Time);










private:
	Vector3D Translative_;
	Vector3D Angular_;
	Timestamp Time_;
};

#endif // STATE_H
