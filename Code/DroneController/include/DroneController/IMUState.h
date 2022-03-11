#ifndef IMUSTATE_H
#define IMUSTATE_H


#include "Abstraction/Value.h"
#include "Abstraction/Vector3D.h"
#include "Abstraction/Timestamp.h"


/* Expects following Units:
 * Translative			Unit_Acceleration
 * Angular				Unit_AngleVelRad
 * GroundClearance		Unit_Length
 */

class IMUState
{
public:
	IMUState() : IMUState(Vector3D(Unit_Acceleration), Vector3D(Unit_AngleVelRad), Value(Unit_Length), Timestamp()) {};
	IMUState(Vector3D Translative, Vector3D Angular, Value GroundClearance, Timestamp Time);

	bool operator==(const IMUState& S);
	bool operator==(const IMUState& S) const;
	void operator+=(const IMUState& S);
	IMUState operator-(const IMUState& S);

	Vector3D getVector_Linear() { return this->Accelerations_; };
	Vector3D getVector_Angular() { return this->Angles_; };
	Value getGroundClearance() { return this->GroundClearance_; };
	Timestamp getTimestamp() { return this->Time_; };
	
private:
	Vector3D Accelerations_;
	Vector3D Angles_;
	Value GroundClearance_;
	Timestamp Time_;
};

#endif // IMUSTATE_H
