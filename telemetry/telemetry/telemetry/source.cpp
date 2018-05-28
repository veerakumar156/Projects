// telemetry.cpp : Defines the entry point for the console application.
//


#include <memory>
#include "stdafx.h"
#include "readtelemetry.h"
#include "telemeterdata.h"
#include "writetelemetry.h"

using namespace std;

int main()
{
	//Read the input file 
	std::shared_ptr<CReadtelemetry> ReadFile(new CReadtelemetry());
	std::string inputfile = "telemetry.txt";
	ReadFile->ReadInputFile(inputfile);

	//Perform detections and analysis
	std::shared_ptr<CTelemeterData> Data = ReadFile->GetData(); 
	Data->PerformAnamolyDetections();
	size_t WindowSize = 5; 
	Data->PerformAverageCalculations(WindowSize);

	//Write to output log file 
	std::shared_ptr<CWritetelemetry> WriteFile(new CWritetelemetry());
	std::string outputfile = "output.txt";
	WriteFile->WriteOutputFile(outputfile, Data, WindowSize);

	return 0;
}

