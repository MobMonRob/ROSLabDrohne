#ifndef SAFETYPROVIDER_H
#define SAFETYPROVIDER_H

#include <vector>
#include <cstddef>

#include "Domain/SafetyRequirement.h"
#include "Domain/SafetyReceiver.h"


class SafetyProvider
{
public:
	void addReceiver(SafetyReceiver* Receiver) { this->Receivers_.push_back(Receiver); };
	
	bool meetsRequirements();
	
protected:
	void addRequirement(SafetyRequirement* Requirement) { this->Requirements_.push_back(Requirement); };

	void triggerReceivers();

protected:
	std::vector<SafetyRequirement*> Requirements_;
	std::vector<SafetyReceiver*> Receivers_;
};

#endif // SAFETYPROVIDER_H

