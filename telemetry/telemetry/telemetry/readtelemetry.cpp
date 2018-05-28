
#include <memory>
#include <sstream>
#include "stdafx.h"
#include "telemeterdata.h"
#include "readtelemetry.h"


void CReadtelemetry::ReadInputFile(std::string& inputfile)
{
	if (inputfile.empty())
		return; 

	std::ifstream infile(inputfile);

	std::string delimiter = ",";
	size_t pos = 0;
	std::string token;
	size_t numLines = 0;
	while (1)
	{
		std::string line;
		std::getline(infile, line);
		if (line.empty())
			break;
		int count = 0;
		while ((pos = line.find(delimiter)) != std::string::npos)
		{
			token = line.substr(0, pos);
			
			if (count == 0)
			{
				m_pData.addTimestamp(token);
			}
			else if (count == 1)
			{
				m_pData.addPower(token);
			}
			else if (count == 2)
			{
				m_pData.addVoltage(token);
			}
			line.erase(0, pos + delimiter.length());
			count += 1;
			if (count == 3)
				m_pData.addCurrent(line);
		}
		numLines += 1;
	}

	m_pData.SetDataSize(numLines);
	infile.close();
	return;
}

std::shared_ptr<CTelemeterData> CReadtelemetry::GetData()
{
	return std::make_shared<CTelemeterData>(m_pData);;
}
