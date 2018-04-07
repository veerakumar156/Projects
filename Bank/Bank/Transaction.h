#pragma once
#include <string>
class CTransaction
{
public:

	CTransaction()
	{
	}

	virtual ~CTransaction()
	{
	}

	void SetTransactionAmount(const double& d) { dTransAmount = d; }
	void SetTransactionType(const std::string& s) { sTransType = s; }

	double GetTransactionAmount() { return dTransAmount; }
	std::string GetTransactionType() { return sTransType; }

private:
	std::string sTransType ; 
	double dTransAmount; 
};


