#include "DataCollector.h"





bool DataCollector::addKey(std::string Key)
{
	if (this->getSize() == 0 && !this->isKey(Key))
	{
		this->Header_.push_back(Key);
	}

	return this->isKey(Key);
}


bool DataCollector::addEntry(std::string Key, std::string Value)
{
	if (this->getSize() == 0)
	{
		this->addDataset();
	}

	if (!this->isData(this->getSize() - 1, Key))
	{
		this->Data_.at(this->getSize() - 1)->insert(std::pair<std::string, std::string>(Key, Value));
	}

	return (this->getData(this->getSize()-1, Key) == Value);
}

void DataCollector::addDataset()
{
	this->Data_.push_back(new std::map<std::string, std::string>());
}







std::string DataCollector::getString(size_t StartID, size_t EndID, bool HeaderIncluded)
{
	std::string ReturnString = "";


	if (HeaderIncluded)
	{
		ReturnString.append(this->getString_Header()).append("\n");
	}

	if (StartID < 0)
	{
		StartID = 0;
	}
	if (EndID < 0 || EndID >= this->getSize())
	{
		EndID = this->getSize() - 1;
	}


	for (size_t i = StartID; i <= EndID; i++)
	{
		ReturnString.append(this->getString_Data(i)).append("\n");
	}

	return ReturnString;
}

std::string DataCollector::getString_Header()
{
	std::string ReturnString = "ID;";


	for (std::vector<std::string>::iterator it = this->Header_.begin(); it != this->Header_.end(); it++)
	{
		ReturnString.append(*it);
		ReturnString.append(";");
	}

	return ReturnString;
}

std::string DataCollector::getString_Data(size_t ID)
{
	std::string ReturnString = std::string(std::to_string(ID)).append(";");


	if (this->isDataset(ID))
	{
		for (std::vector<std::string>::iterator it = this->Header_.begin(); it != this->Header_.end(); it++)
		{
			ReturnString.append(this->getData(ID, *it));
			ReturnString.append(";");
		}
	}

	return ReturnString;
}

std::string DataCollector::getData(size_t ID, std::string Key)
{
	std::string ReturnString = "";


	if (this->isData(ID, Key))
	{
		std::map<std::string, std::string>::iterator it = this->Data_.at(ID)->find(Key);


		ReturnString = it->second;
	}

	return ReturnString;
}










bool DataCollector::isKey(std::string Key)
{
	bool ReturnBool = false;


	for (std::vector<std::string>::iterator it = this->Header_.begin(); it != this->Header_.end(); it++)
	{
		if (*it == Key)
		{
			ReturnBool = true;

			break;
		}
	}

	return ReturnBool;
}

bool DataCollector::isData(size_t ID, std::string Key)
{
	bool ReturnBool = false;
	std::map<std::string, std::string>* Dataset = nullptr;


	if (this->isDataset(ID))
	{
		Dataset = this->Data_.at(ID);
		std::map<std::string, std::string>::iterator it = Dataset->find(Key);


		ReturnBool = (it != Dataset->end());
	}

	return ReturnBool;
}

