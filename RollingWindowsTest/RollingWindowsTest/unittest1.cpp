#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include "StatisticsGenerator.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RollingWindowsTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			std::vector<double> iVec = { 1,2,3,4,5,6 };
			CStatisticsGenerator statGenerator(iVec); 
			statGenerator.AddWindow(3); 
			statGenerator.AddWindow(5);
			statGenerator.CalculateStatistics(); 
			for (int i = 0; i < iVec.size(); i++)
			{
				std::pair<Statistics, Statistics> p1 = statGenerator.GetNext();
				if (i == 5)
				{
					Assert().AreEqual(p1.first.mean, 5.0, L"Test", LINE_INFO());
					Assert().AreEqual(p1.first.max, 6.0, L"Test", LINE_INFO());
					Assert().AreEqual(p1.second.mean, 4.0, L"Test", LINE_INFO());
					Assert().AreEqual(p1.second.max, 6.0, L"Test", LINE_INFO());
				}
			}
			

		}

	};
}