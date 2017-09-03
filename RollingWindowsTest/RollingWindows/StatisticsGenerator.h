/**
* @file   StatisticsGenerator.h
* @Author Veerakumar Murugesan
* @date   August 18, 2017
* @brief  Class declaration to calculate statistics such as mean using a rolling window on a stream of numbers 
*         
*
*/

#pragma once
#include <utility>
#include <memory>
#include <vector>
using namespace std; 

struct Statistics {
	bool valid; // true only if mean and max fields are valid
	double mean;
	double max;
};

class CInputStream;
class CStatisticsGenerator
{
public:
	CStatisticsGenerator();
	CStatisticsGenerator(const std::vector<double>& iVec); 
	virtual ~CStatisticsGenerator();
	bool AddWindow(const int & iWindow);
	void CalculateStatistics();
	// Get the current statistics.
	std::pair<Statistics, Statistics> GetNext();
	

private:
	// Returns true if more elements are available
	bool HasNext();

	//Internal methods to calculate statistics
	void PopulateStatistics(const std::vector<double>& ForWindow1, const int& head, const int & iWindow, Statistics* stat);
	bool ValidWindow(const std::vector<double>& ForWindow1, const int& head, const int& iWindow);

	//data members 
	size_t iPtrToStat = 0; //Points to next available statistics
	std::vector<int> vWindowSizes; //Stores all the rolling window sizes
	std::vector<Statistics*> StatisticsVectorFirstWindow; //all the statistics calculated based on first window
	std::vector<Statistics*> StatisticsVectorSecondWindow; //all the statistics calculated based on second window
	std::tr1::shared_ptr<CInputStream> InputStream; //Created as a smart pointer to facilitate efficient resource mangaement 
};


