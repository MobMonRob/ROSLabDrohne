#ifndef CALLER_H
#define CALLER_H

#include <set>

#include "calling/Calling.h"
#include "calling/Callable.h"


class Caller : public Calling
{
public:
	bool addCallable(Callable *Item);
	bool deleteCallable(Callable *Item) { return (this->Callables_.erase(Item) > 0); };
	
	void call();
	
private:
	bool findCallable(Callable *Item) { return (this->Callables_.find(Item) != this->Callables_.end()); };
	
private:
	std::set<Callable*> Callables_;
};

#endif // CALLER_H


