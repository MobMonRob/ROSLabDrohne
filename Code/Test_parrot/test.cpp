#include "pch.h"


#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "BagPlotter/DataCollector.h"
#include "BagPlotter/DataLoader.h"







TEST(BagLoader, SplitString)
{
	std::string String = "Hello;World";


	std::vector<std::string> Result = DataLoader::split(String, ";");

	EXPECT_EQ(Result.size(), 2);
	if (Result.size() >= 1)
	{
		EXPECT_EQ(Result.at(0), "Hello");
	}
	if (Result.size() >= 2)
	{
		EXPECT_EQ(Result.at(1), "World");
	}
}

TEST(BagLoader, LoadFile)
{
	std::string String = "Hello;World";
	std::string FilePath = "C:\\Users\\maag\\Git-Repos\\DHBW_SARB\\ROSLabDrohne\\Code\\BagPlotter\\Data\\Test.txt";
	DataCollector DC;
	DataLoader DL(&DC, FilePath);


	std::vector<std::string> Result = DC.getHeader();

	EXPECT_EQ(Result.size(), 2);
	if (Result.size() >= 1)
	{
		EXPECT_EQ(Result.at(0), "Hello");
	}
	if (Result.size() >= 2)
	{
		EXPECT_EQ(Result.at(1), "World");
	}
}

TEST(BagLoader, LoadFileData)
{
	std::string String = "Hello;World";
	std::string FilePath = "C:\\Users\\maag\\Git-Repos\\DHBW_SARB\\ROSLabDrohne\\Code\\BagPlotter\\Data\\Test.txt";
	DataCollector DC;
	DataLoader DL(&DC, FilePath);


	std::vector<std::string> Keys = DC.getHeader();

	if (Keys.size() >= 1)
	{
		std::string Result = DC.getData(0, Keys.at(0));

		EXPECT_EQ(Result, "How");
	}
	else
	{
		FAIL();
	}
	if (Keys.size() >= 2)
	{
		std::string Result = DC.getData(1, Keys.at(1));

		EXPECT_EQ(Result, "?");
	}
	else
	{
		FAIL();
	}
}








