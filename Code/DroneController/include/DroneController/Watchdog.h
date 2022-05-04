#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "Domain/Timestamp.h"
#include "Domain/SafetyProvider.h"
#include "Domain/SafetyReceiver.h"

#include "DroneController/TimeoutOK.h"


class Watchdog : public SafetyProvider
{
public:
	Watchdog() : TimeCount_(0) {};

	bool meetsRequirements(Timestamp Time);
	void resetTimeouts();

private:
	size_t TimeCount_;
};

#endif // WATCHDOG_H
