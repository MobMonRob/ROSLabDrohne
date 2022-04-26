#include "BagPlotter/DataPersister.h"




size_t DataPersister::persist(DataCollector* Collector, std::string FilePath)
{
	size_t ReturnValue = 0;
	std::fstream File_(FilePath, std::ios::out);


	if (File_.is_open())
	{
		File_ << Collector->getString();


		{	// validate
			std::string line;


			File_.seekg(File_.beg);

			while (std::getline(File_, line))
			{
				ReturnValue++;
			}
		}

		File_.close();


		std::cout << "Persisted " << ReturnValue << " of " << Collector->getSize() << " Lines to File. >" << FilePath << "<" << std::endl;
	}
	else
	{
		std::cout << "ERROR: Did not open File: >" << FilePath << "<" << std::endl;
	}

	return ReturnValue;
}


