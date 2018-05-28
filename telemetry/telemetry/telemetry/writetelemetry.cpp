#include "stdafx.h"
#include <fstream>
#include "writetelemetry.h"


void CWritetelemetry::WriteOutputFile(std::string& outputFile, std::shared_ptr<CTelemeterData>& data, const size_t& WindowSize)
{
	std::ofstream outFile(outputFile); 

	for (int i = 0; i < data->GetDataSize(); i++)
	{
		std::string outLine;
		if (data->IsTimeAnomaly(i))
			outLine = outLine + "* Anomaly - time gap detected\n";
		if (data->IsPowerAnomaly(i))
			outLine = outLine + "* Anomaly - negative power detected\n";
		if (data->IsVoltageAnomaly(i))
			outLine = outLine + "* Anomaly - out of range voltage detected\n";
		if (data->IsCurrentAnomaly(i))
			outLine = outLine + "* Anomaly -  negative current detected\n";
		outLine = outLine + data->GetOutputEntry(i, WindowSize);
		outFile << outLine << std::endl;
	}
	outFile.close();
}
