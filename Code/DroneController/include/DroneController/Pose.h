#ifndef POSE_H
#define POSE_H

#include <string>

#include "Domain/Vector3D.h"
#include "Domain/Timestamp.h"

class Pose
{
public:
	Pose() : Pose(Timestamp(), Vector3D(Unit_None, 0, 0, 0), Vector3D(Unit_None, 0, 0, 0)) {};
	Pose(Timestamp Time, Vector3D Position, Vector3D Orientation) : Pose(Time, Position, Orientation, Vector3D(Unit_None, 0, 0, 0), Vector3D(Unit_None, 0, 0, 0)) {};
	Pose(Timestamp Time, Vector3D Position, Vector3D Orientation, Vector3D PositionUncertainty, Vector3D OrientationUncertainty);

	Timestamp getTime() const { return this->Time_; };
	Vector3D getPosition() const { return this->Position_; };
	Vector3D getPositionUncertainty() const { return this->PositionUncertainty_; };
	Vector3D getOrientation() const { return this->Orientation_; };
	Vector3D getOrientationUncertainty() const { return this->OrientationUncertainty_; };
	std::string getString();

private:
	Timestamp Time_;
	Vector3D Position_;
	Vector3D PositionUncertainty_;
	Vector3D Orientation_;
	Vector3D OrientationUncertainty_;
};

#endif // POSE_H

