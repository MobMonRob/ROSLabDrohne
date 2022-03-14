#ifndef SAFETYTRANSLATIVE_H
#define SAFETYTRANSLATIVE_H

#include "Abstraction/SafetyRequirement.h"
#include "Abstraction/SafetyProvider.h"


class SafetyTranslative : public SafetyRequirement
{
public:
	SafetyTranslative(SafetyProvider* Checker) : Checker_(Checker) {};

	bool meets() override { return this->Checker_->meetsRequirements(); };

private:
	SafetyProvider* Checker_;
};

#endif // SAFETYTRANSLATIVE_H

