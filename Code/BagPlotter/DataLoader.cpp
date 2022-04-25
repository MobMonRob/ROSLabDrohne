#include "DataLoader.h"




DataLoader::DataLoader(DataCollector* Collector, std::string FilePath)
	: Collector_(Collector),
	File_(FilePath, std::ios::in)
{
	if (this->File_.good())
	{
		this->readHeader();
		this->readContent();
	}
	else
	{
		std::cout << "ERROR: Did not open File: >" << FilePath << "<" << std::endl;
	}
}




void DataLoader::readHeader()
{
	if (this->File_.is_open())
	{
		std::streampos StreamPos = this->File_.tellg();
		std::string Line;
		std::vector<std::string> LineContent;


		this->goFileBegin();
		std::getline(this->File_, Line);
		LineContent = this->split(Line, ";");

		for (std::vector<std::string>::iterator it = LineContent.begin(); it != LineContent.end(); it++)
		{
			this->Collector_->addKey(*it);
		}

		this->File_.seekg(StreamPos);
	}
}

void DataLoader::readContent()
{
	if (this->File_.is_open())
	{
		std::vector<std::string> Keys = this->Collector_->getHeader();
		std::streampos StreamPos = this->File_.tellg();
		std::string Line;


		this->goFileBegin();
		std::getline(this->File_, Line);		// skip Header-Line
		
		while (std::getline(this->File_, Line))
		{
			this->addLineContent(Keys, this->split(Line, ";"));
		}

		this->File_.seekg(StreamPos);
	}
}

void DataLoader::addLineContent(std::vector<std::string> Keys, std::vector<std::string> LineContent)
{
	this->Collector_->addDataset();

	if (LineContent.size() == Keys.size())
	{
		for (size_t ID = 0; ID < Keys.size(); ID++)
		{
			this->Collector_->addEntry(Keys.at(ID), LineContent.at(ID));
		}
	}
	else
	{
		std::cout << "ERROR: KeyCount does not match ValueCount at Line " << this->Collector_->getSize() << std::endl;
	}
}





bool DataLoader::goFileBegin()
{
	this->File_.seekg(this->File_.beg);

	return (this->File_.beg == this->File_.tellg());
}


std::vector<std::string> DataLoader::split(std::string String, std::string Separator)
{
	std::vector<std::string> ReturnList;


	while (String.size() > 0)
	{
		size_t Alloc = String.find(Separator);


		if (Alloc != std::string::npos)
		{
			ReturnList.push_back(String.substr(0, Alloc));

			String = String.substr(Alloc+1);
		}
		else
		{
			ReturnList.push_back(String);

			break;
		}
	}
	
	return ReturnList;
}
