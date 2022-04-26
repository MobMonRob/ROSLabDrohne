#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "BagPlotter/DataCollector.h"



class DataPersister
{
public:
	static size_t persist(DataCollector* Collector, std::string FilePath);

};

