#include "stdafx.h"
#include <sstream> 
#include <iomanip> 
#include <string>
#include "telemeterdata.h"



std::string timestamp::GetStamp()
{
	return stamp;
}

void timestamp::SetStamp(const std::string& s)
{
	stamp = s; 
	size_t pos = s.find_last_of(":");
	fSecond = static_cast<float>(atof(s.substr(pos+1).c_str()));;
}


void CTelemeterData::addTimestamp(const std::string& str)
{
	timestamp stamp; 
	stamp.SetStamp(str);
	vTstamp.push_back(stamp);

}
void CTelemeterData::addPower(const std::string& str)
{
	float f = atof(str.c_str());
	fKW.push_back(f);
}


void CTelemeterData::addVoltage(const std::string& str)
{
	float f = atof(str.c_str());
	fVol.push_back(f);
}


void CTelemeterData::addCurrent(const std::string& str)
{
	float f = atof(str.c_str());
	fAmp.push_back(f);
}


void CTelemeterData::PerformAnamolyDetections()
{
	float fPrevSecond = NULL;
	timeanomalyforavg.assign(dataSize, false);
	timeanomaly.assign(dataSize, false); 
	poweranomaly.assign(dataSize, false); 
	voltageanomaly.assign(dataSize, false); 
	currentanomaly.assign(dataSize, false);

	for (size_t i = 0; i < dataSize; i++)
	{
		//Perform Timestamp gap detection
		float fCurrentSecond = vTstamp[i].GetSecond();
		if (fPrevSecond == NULL)
		{
			fPrevSecond = fCurrentSecond;
			timeanomaly[i] = false;
		}
		else if (fCurrentSecond != NULL)
		{
			if ((fPrevSecond > 59) && (fPrevSecond < 60))
				fPrevSecond -= 60; 
			if (abs(fPrevSecond - fCurrentSecond) > 1.5)
				timeanomaly[i] = true;
			else
				timeanomaly[i] = false; 

			if (abs(fPrevSecond - fCurrentSecond) > 5)
				timeanomalyforavg[i] = true;
			else
				timeanomalyforavg[i] = false;

			fPrevSecond = fCurrentSecond;
		}


		//Perform negative values of kW detection 
		if (fKW[i] < 0.0f)
			poweranomaly[i] = true;
		else
			poweranomaly[i] = false; 


		//Perform out of range values of voltage detection
		if ((fVol[i] < 475) || (fVol[i] > 485))
			voltageanomaly[i] = true;
		else
			voltageanomaly[i] = false; 


		//Perform negative values of current detection 
		if (fAmp[i] < 0.0f)
			currentanomaly[i] = true;
		else
			currentanomaly[i] = false;

	}
}


void CTelemeterData::PerformAverageCalculations(const size_t& WindowSize)
{
	if (dataSize == 0)
		return;
	float local_powertotal = 0.0f;
	float local_voltagetotal = 0.0f;
	float local_currenttotal = 0.0f;
	avg_fKW.assign(dataSize, 0.0f);
	avg_fVol.assign(dataSize, 0.0f);
	avg_fAmp.assign(dataSize, 0.0f);

	for (int i = 0; i < WindowSize; i++)
	{
		local_powertotal += fKW[i]; 
		local_voltagetotal += fVol[i];
		local_currenttotal += fAmp[i];

		if (i == WindowSize -1)
		{
			avg_fKW[i] = local_powertotal / WindowSize;
			avg_fVol[i] = local_voltagetotal / WindowSize;
			avg_fAmp[i] = local_currenttotal / WindowSize;
		}
	}
	int oldest = 0; 
	for (size_t i = WindowSize; i < dataSize; i++)
	{
		if (timeanomalyforavg[i])
			continue; 
		local_powertotal -= fKW[oldest];
		local_powertotal += fKW[i];
		avg_fKW[i] = local_powertotal/WindowSize;
		local_voltagetotal -= fVol[oldest];
		local_voltagetotal += fVol[i];
		avg_fVol[i] = local_voltagetotal / WindowSize;
		local_currenttotal -= fAmp[oldest];
		local_currenttotal += fAmp[i];
		avg_fAmp[i] = local_currenttotal / WindowSize;
		oldest++;
	}

}

std::string CTelemeterData::GetOutputEntry(const size_t& sub, const size_t& WindowSize)
{
	std::ostringstream ss;
	using namespace std;
	string outLine;
	
	if ((sub < WindowSize-1) || timeanomalyforavg[sub])
	{
		ss << vTstamp[sub].GetStamp() << " , " << std::setw(7) << setprecision(6) << fKW[sub] << " , " << fVol[sub]
			<< " , " << fAmp[sub] << ",  ,  ," ;
		outLine = ss.str();
	}
	else
	{
		ss << vTstamp[sub].GetStamp() << " , " << std::setw(7) <<  setprecision(6) << fKW[sub] << " , " << fVol[sub]
			<< " , " << fAmp[sub] << " , " << avg_fKW[sub] << " , " << avg_fVol[sub] << " , " << avg_fAmp[sub];
		outLine = ss.str();
	}
	return outLine;
}

bool CTelemeterData::IsTimeAnomaly(const size_t& sub)
{
	if (sub < dataSize)
		return timeanomaly[sub];
	else
		return false; 
}

bool CTelemeterData::IsPowerAnomaly(const size_t& sub)
{
	if (sub < dataSize)
		return poweranomaly[sub];
	else
		return false;
}

bool CTelemeterData::IsVoltageAnomaly(const size_t& sub)
{
	if (sub < dataSize)
		return voltageanomaly[sub];
	else
		return false;
}

bool CTelemeterData::IsCurrentAnomaly(const size_t & sub)
{
	if (sub < dataSize)
		return currentanomaly[sub];
	else
		return false;
}

float CTelemeterData::GetPowerAverage(const size_t & sub)
{
	if (sub < dataSize)
		return avg_fKW[sub];
	else
		return false;
}

float CTelemeterData::GetVoltageAverage(const size_t & sub)
{
	if (sub < dataSize)
		return avg_fVol[sub];
	else
		return false;
}

float CTelemeterData::GetCurrentAverage(const size_t & sub)
{
	if (sub < dataSize)
		return avg_fAmp[sub];
	else
		return false;
}
