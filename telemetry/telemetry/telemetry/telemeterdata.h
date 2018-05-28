#pragma once

#include <memory>
#include <vector>


class timestamp
{
public:
	std::string GetDate() { return stamp; }
	std::string GetStamp();
	void SetStamp(const std::string& s);
	float GetSecond() { return fSecond; }
	
private:
	std::string stamp; 
	float fSecond;

};
class CTelemeterData 
{
public:
	CTelemeterData() {};
	~CTelemeterData() {};
	void addTimestamp(const std::string& str);
	void addPower(const std::string& str);
	void addVoltage(const std::string& str);
	void addCurrent(const std::string& str);
	void PerformAnamolyDetections();
	void PerformAverageCalculations(const size_t&  WindowSize);
	void SetDataSize(const size_t& sz) { dataSize = sz; }
	size_t GetDataSize() { return dataSize; }
	std::string GetOutputEntry(const size_t&, const size_t&);
	bool IsTimeAnomaly(const size_t&);
	bool IsPowerAnomaly(const size_t&);
	bool IsVoltageAnomaly(const size_t&);
	bool IsCurrentAnomaly(const size_t&);
	float GetPowerAverage(const size_t& sub);
	float GetVoltageAverage(const size_t& sub); 
	float GetCurrentAverage(const size_t& sub);

private:
	std::vector<timestamp> vTstamp;
	std::vector<float> fKW;
	std::vector<float> fVol;
	std::vector<float> fAmp;
	std::vector<bool> timeanomalyforavg;
	std::vector<bool> timeanomaly;
	std::vector<bool> poweranomaly;
	std::vector<bool> voltageanomaly;
	std::vector<bool> currentanomaly;
	std::vector<float> avg_fKW;
	std::vector<float> avg_fVol;
	std::vector<float> avg_fAmp;
	size_t dataSize = 0; 
	
};

