#include "BagPlotter/DataPersister.h"




size_t DataPersister::persist(DataCollector* Collector, std::string FilePath, std::size_t PrintCount)
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
		std::cout << Collector->getString(0, PrintCount-1, true) << "..." << std::endl;
		std::cout << Collector->getString(Collector->getSize() - PrintCount, Collector->getSize(), false) << std::endl;
	}
	else
	{
		std::cout << "ERROR: Did not open File: >" << FilePath << "<" << std::endl;
	}

	return ReturnValue;
}


