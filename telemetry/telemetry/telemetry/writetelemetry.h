#pragma once


#include <string>
#include "telemeterdata.h"

class CWritetelemetry 
{
public:
	CWritetelemetry() {};
	~CWritetelemetry() {};
	void WriteOutputFile(std::string&, std::shared_ptr<CTelemeterData>&, const size_t&);
};

