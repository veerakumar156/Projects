#include "stdafx.h"
#include "CppUnitTest.h"
#include "../telemetry/writetelemetry.h"
#include "../telemetry/readtelemetry.h"
#include "../telemetry/telemeterdata.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test_telemetry
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestEmptyInputFile)
		{
			std::string inputFile; 
			std::shared_ptr<CReadtelemetry> ReadFile(new CReadtelemetry());
			ReadFile->ReadInputFile(inputFile);
		    std::shared_ptr<CTelemeterData> Data = ReadFile->GetData();
			Assert().AreEqual(int(Data->GetDataSize()), 0, L"Test", LINE_INFO());
		}

		TEST_METHOD(TestValidInputFile)
		{
			std::string inputFile = "../telemetry/telemetry.txt";
			std::shared_ptr<CReadtelemetry> ReadFile(new CReadtelemetry());
			ReadFile->ReadInputFile(inputFile);
			std::shared_ptr<CTelemeterData> Data = ReadFile->GetData();
			Assert().AreEqual(int(Data->GetDataSize()), 97, L"Test", LINE_INFO());
		}

		TEST_METHOD(TestOutputFile)
		{
			std::shared_ptr<CReadtelemetry> ReadFile(new CReadtelemetry());
			std::string inputFile = "../telemetry/telemetry.txt";
			ReadFile->ReadInputFile(inputFile);
			std::shared_ptr<CTelemeterData> Data = ReadFile->GetData();
			Data->PerformAnamolyDetections();
			size_t WindowSize = 5;
			Data->PerformAverageCalculations(WindowSize);
			std::shared_ptr<CWritetelemetry> WriteFile(new CWritetelemetry());
			std::string outputfile = "output.txt";
			WriteFile->WriteOutputFile(outputfile, Data, WindowSize);

			int number_of_lines = 0;
			std::string line;
			std::ifstream myfile(outputfile);

			while (std::getline(myfile, line))
				++number_of_lines;
			Assert().AreEqual(number_of_lines, 103, L"Test", LINE_INFO());
		}

		TEST_METHOD(TestAnamolyDetection)
		{
			std::shared_ptr<CReadtelemetry> ReadFile(new CReadtelemetry());
			std::string inputFile = "../telemetry/telemetry.txt";
			ReadFile->ReadInputFile(inputFile);
			std::shared_ptr<CTelemeterData> Data = ReadFile->GetData();
			Data->PerformAnamolyDetections();
			//vectors in data are indexed from 0.Hence the indices checked below are linenumber in text file - 1
			Assert().IsTrue(Data->IsTimeAnomaly(37));
			Assert().IsTrue(Data->IsPowerAnomaly(87));
			Assert().IsTrue(Data->IsVoltageAnomaly(76));
			Assert().IsTrue(Data->IsCurrentAnomaly(87));  
		}

		TEST_METHOD(TestAverageCalculation)
		{
			std::shared_ptr<CReadtelemetry> ReadFile(new CReadtelemetry());
			std::string inputFile = "../telemetry/telemetry.txt";
			ReadFile->ReadInputFile(inputFile);
			std::shared_ptr<CTelemeterData> Data = ReadFile->GetData();
			Data->PerformAnamolyDetections();
			size_t WindowSize = 5;
			Data->PerformAverageCalculations(WindowSize);
			//vectors in data are indexed from 0.Hence the indices checked below are linenumber in text file - 1
			Assert().AreEqual(float(Data->GetPowerAverage(3)), 0.0f, L"Test", LINE_INFO());
			Assert().AreEqual(float(Data->GetVoltageAverage(3)), 0.0f, L"Test", LINE_INFO());
			Assert().AreEqual(float(Data->GetCurrentAverage(3)), 0.0f, L"Test", LINE_INFO());
			int power_val = static_cast<int>(Data->GetPowerAverage(4) - 403.544);
			int voltage_val = static_cast<int>(Data->GetVoltageAverage(4) - 479.0056);
			int current_val = static_cast<int>(Data->GetCurrentAverage(4) - 841.897);
			Assert().AreEqual(power_val, 0, L"Test", LINE_INFO());
			Assert().AreEqual(voltage_val, 0, L"Test", LINE_INFO());
			Assert().AreEqual(current_val, 0, L"Test", LINE_INFO());
			power_val = static_cast<int>(Data->GetPowerAverage(96) - 431.752);
			voltage_val = static_cast<int>(Data->GetVoltageAverage(96) - 480.581);
			current_val = static_cast<int>(Data->GetCurrentAverage(96) - 898.603);
			Assert().AreEqual(power_val, 0, L"Test", LINE_INFO());
			Assert().AreEqual(voltage_val, 0, L"Test", LINE_INFO());
			Assert().AreEqual(current_val, 0, L"Test", LINE_INFO());
		}
	};
}