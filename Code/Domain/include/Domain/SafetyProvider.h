#ifndef SAFETYPROVIDER_H
#define SAFETYPROVIDER_H

#include <vector>
#include <cstddef>

#include "Domain/SafetyRequirement.h"


class SafetyProvider
{
public:
	bool meetsRequirements();

protected:
	void addRequirement(SafetyRequirement Requirement) { this->Requirements_.push_back(Requirement); };

private:
	std::vector<SafetyRequirement> Requirements_;
};

#endif // SAFETYPROVIDER_H

