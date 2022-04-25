#pragma once

#include "gmock/gmock.h"

#include "DroneController/PoseControlable.h"


class PoseControlable_Mock : public PoseControlable
{
public:
	MOCK_METHOD(void, setPose, (Pose P), (override));
	MOCK_METHOD(bool, feedbackPose, (Pose P), (override));
	MOCK_METHOD(void, reset, (), (override));

};

