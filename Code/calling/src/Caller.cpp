#include "calling/Caller.h"


bool Caller::addCallable(Callable *Item)
{
	if (Item != nullptr)
	{
		this->Callables_.insert(Item);
	}
	
	return this->findCallable(Item);
}


void Caller::call()
{
	for (Callable* Item : this->Callables_)
	{
		Item->call(this);
	}
}


