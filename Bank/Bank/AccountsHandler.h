#pragma once
#include <Windows.h>
#include <thread>
#include <vector>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <memory>
#include "Account.h"


class CAccountsHandler
{
public:
	CAccountsHandler();
	virtual ~CAccountsHandler();

	void IdentifyAccountWithHighestBalance(); 
	void PerformDebit();
	void PerformCredit();
	void PerformAnalysis();
	void Debit();
	void Credit();
	void Analysis();
	void PrintTransactionHistory();

	std::thread DebitThread() {
		return std::thread([=] { Debit(); });
	}

	std::thread CreditThread() {
		return std::thread([=] { Credit(); });
	}

	std::thread AnalysisThread() {
		return std::thread([=] { Analysis(); });
	}

	void SetStartTime();

private:

	//all the accounts created
	std::vector<std::tr1::shared_ptr<CAccount>> accounts;

	//Highest balance account
	double dAverageBalance;
	std::mutex mtx;
	std::condition_variable cv;
	bool ready = false;
	unsigned int iStartTime; 
	unsigned int iCurrentTime;
	void CalculateAverageBalance(); 
	bool IsThreadRunnable();
};

