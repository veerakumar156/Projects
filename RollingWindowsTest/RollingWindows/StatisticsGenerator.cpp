#include "stdafx.h"
#include <memory>
#include "InputStream.h"
#include "StatisticsGenerator.h"


CStatisticsGenerator::CStatisticsGenerator()
{
	InputStream.reset(new CInputStream());
}

CStatisticsGenerator::CStatisticsGenerator(const std::vector<double>& iVec)
{
	InputStream.reset(new CInputStream(iVec));
}

CStatisticsGenerator::~CStatisticsGenerator()
{
	//All the statistics pointers created during calculation of statistics 
	//should be deallocated before the relevant vectors are cleared. 
	for (int i = 0; i < StatisticsVectorFirstWindow.size(); i++)
	{
		delete StatisticsVectorFirstWindow[i];
		delete StatisticsVectorSecondWindow[i]; 
	}

	StatisticsVectorFirstWindow.clear(); 
	StatisticsVectorSecondWindow.clear(); 
	vWindowSizes.clear();
}

bool CStatisticsGenerator::HasNext()
{
	if (iPtrToStat >= StatisticsVectorFirstWindow.size())
		return false;
	else
		return true;
}

bool CStatisticsGenerator::AddWindow(const int& iWindow)
{
	if (vWindowSizes.size() < 2)
	{
		vWindowSizes.push_back(iWindow);
	}
	else
	{
		return false;
	}
}

/**
* @brief 
* This method returns the next available statistics structure
*
*
* @param None
*
* @retval Next pair of statistics for two rollowing windows.
*
*/
std::pair<Statistics, Statistics> CStatisticsGenerator::GetNext()
{
	if (HasNext())
	{
		Statistics stat1 = *StatisticsVectorFirstWindow[iPtrToStat];
		Statistics stat2 = *StatisticsVectorSecondWindow[iPtrToStat];
		iPtrToStat++;
		return std::pair<Statistics, Statistics>(stat1, stat2);
	}
	else
	{
		return std::pair<Statistics, Statistics>();
	}
}


/**
* @brief
* Calculate the statistics such as mean and max for a stream of numbers. This is done using
* two rolling windows of various sizes. 
*
*
* @param None
*
* @retval None 
*
*/
void CStatisticsGenerator::CalculateStatistics()
{
	vector<double> InputVector; 
	int head = 0;
	int window1 = vWindowSizes[0];
	int window2 = vWindowSizes[1];
	StatisticsVectorFirstWindow.clear();
	StatisticsVectorSecondWindow.clear();
	while (InputStream->HasNext())
	{

		InputVector.push_back(InputStream->GetNext());

		//Created in heap so that it is available till gets deallocated at the end of program in the destructor. 
		Statistics* FirstWindow = new Statistics(); 
		PopulateStatistics(InputVector, head, window1, FirstWindow);
		
		//Created in heap so that it is available till gets deallocated at the end of program in the destructor. 
		Statistics* SecondWindow = new Statistics();
		PopulateStatistics(InputVector, head, window2, SecondWindow);

		head++;
		StatisticsVectorFirstWindow.push_back(FirstWindow);
		StatisticsVectorSecondWindow.push_back(SecondWindow);
	}
}


/**
* @brief
* This method populates the statistics calculated for valid window sizes. For invalid window sizes
* Statistics structure is populated with default values 
*
*
* @param [in] InputVector - contains the numbers populated from the CInputStream::GetNext()
* @param [in] head - head of the window to keep track of the moving 
* @param [in] iWindow - Size of the window
* @param [in, out] Stat - Statistics structure to be popualated 
*
* @retval None   Successfully did nothing.
*
*/
void CStatisticsGenerator::PopulateStatistics(const std::vector<double>& InputVector, const int& head, const int & iWindow, Statistics* Stat)
{
	if (ValidWindow(InputVector, head, iWindow))
	{
		Stat->valid = true;
		int iCount = 0;
		double sum = 0;
		double max = InputVector[head - iCount];
		while (iCount < iWindow)
		{
			sum = sum + InputVector[head - iCount];
			if (max < InputVector[head - iCount])
				max = InputVector[head - iCount];
			iCount = iCount + 1;
		}

		Stat->mean = sum / iWindow; 
		Stat->max = max; 
	}
	else
	{
		Stat->valid = false;
		Stat->mean = NAN;
		Stat->max = NAN;
	}
}

/**
* @brief
* This method is used check if there are enough elements in the window to calculate statistics
*
*
* @param [in] InputVector - contains the numbers populated from the CInputStream::GetNext()
* @param [in] head - head of the window to keep track of the moving
* @param [in] iWindow - Size of the window
*
* @retval TRUE  if number of elements in the input vector are greater or equal to window size, otherwise FALSE. 
* 
*
*/
bool CStatisticsGenerator::ValidWindow(const std::vector<double>& InputVector, const int& head, const int & iWindow)
{
	bool bValid = false; 
	if ((head < iWindow -1) ||
		(head >= InputVector.size()))
	{
		bValid = false; 
	}
	else 
	{
		bValid = true;

	}
	return bValid;
}


