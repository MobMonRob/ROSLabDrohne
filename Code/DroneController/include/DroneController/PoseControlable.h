#ifndef POSECONTROLABLE_H
#define POSECONTROLABLE_H

#include "DroneController/Transmitable.h"
#include "DroneController/Pose.h"


class PoseControlable : protected Transmitable
{
public:
	PoseControlable(Transmitable* Transmitter) : Transmitter_(Transmitter) {};

	virtual void setPose(Pose P) = 0;
	virtual bool feedbackPose(Pose P) = 0;

	virtual void reset() = 0;

private:
	bool transmitAction(double roll, double pitch, double yarn, double thrust) override;

protected:
	Transmitable* Transmitter_;
};

#endif // POSECONTROLABLE_H

