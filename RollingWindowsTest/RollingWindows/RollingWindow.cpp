// RollingWindow.cpp : Defines the entry point for the console application.
//
#include <vector>
#include "stdafx.h"
#include <memory>
#include "StatisticsGenerator.h"
#include "InputStream.h"

int main()
{
	//StatisticsGeneator - Created as a shared pointer for efficient resource management 
	//                     and prevents any memory leaking
	std::vector<double> iVec = { 1,2,3,4,5,6 };
	std::tr1::shared_ptr<CStatisticsGenerator> GenerateStats;
	GenerateStats.reset(new CStatisticsGenerator(iVec));
	GenerateStats->AddWindow(3);
	GenerateStats->AddWindow(5); 

	//API call to calculate statistics for all the elements in the input stream
	//for the rolling windows added above
	GenerateStats->CalculateStatistics();
	return 0;
}