#pragma once


#include <string>
#include <fstream>
#include "telemeterdata.h"

class CReadtelemetry 
{
public:
	CReadtelemetry() {};
	~CReadtelemetry() {};
	void ReadInputFile(std::string&);
	std::shared_ptr<CTelemeterData> GetData();

private:
	CTelemeterData m_pData;
};

