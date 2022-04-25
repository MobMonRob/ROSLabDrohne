#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "BagPlotter/DataCollector.h"



class DataLoader
{
public:
	DataLoader(DataCollector* Collector, std::string FilePath);

public:
	void readHeader();
	void readContent();
	void addLineContent(std::vector<std::string> Keys, std::vector<std::string> LineContent);

	bool goFileBegin();
	std::vector<std::string> split(std::string String, std::string Separator);

private:
	DataCollector* Collector_;
	std::fstream File_;

};

