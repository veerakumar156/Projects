#pragma once
#include <memory>
#include <algorithm>
#include <vector>
#include <string>
#include "Transaction.h"


class CTransaction; 
class CAccount
{
public:
	CAccount();
	//Can be derived to different types of accounts such as checking, savings
	virtual ~CAccount();

	void SetAccountNumber(const int & i);

	double GetBalance() { return dBalance; }
	void PrintTransactionHistory();
	void AddDebitTransaction(const double& dAmt);
	void AddCreditTransaction(const double& dAmt);

private:
	int iAccoutNumber; 
	double dBalance = 1000; //starting balance
	std::vector<std::tr1::shared_ptr<CTransaction>> vTransactions;

	
};

