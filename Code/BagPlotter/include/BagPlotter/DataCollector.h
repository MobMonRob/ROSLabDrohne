#pragma once

#include <vector>
#include <map>
#include <string>









class DataCollector
{
public:
	bool addKey(std::string Key);
	bool addEntry(std::string Key, std::string Value);
	void addDataset();

	size_t getSize() const { return this->Data_.size(); };
	std::vector<std::string> getHeader() const { return this->Header_; };
	std::string getData(size_t ID, std::string Key);
	std::string getString(size_t StartID = -1, size_t EndID = -1, bool HeaderIncluded = true);
	std::string getString_Header();

	bool isKey(std::string Key);
	bool isData(size_t ID, std::string Key);

private:
	std::string getString_Data(size_t ID);
	
	bool isDataset(size_t ID) { return (ID >= 0 && ID < this->getSize()); };
	
private:
	std::vector<std::string> Header_;
	std::vector<std::map<std::string, std::string>*> Data_;
};

