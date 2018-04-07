#include "stdafx.h"
#include "AccountsHandler.h"
#include <random>

// The operator takes const references - it can compare const objects
bool Compare(const std::tr1::shared_ptr<CAccount> L, const std::tr1::shared_ptr<CAccount> R) {
	return L->GetBalance() < R->GetBalance();
}

CAccountsHandler::CAccountsHandler()
{
	//accounts created 
	accounts.resize(10000);
	for (int i = 0; i < 10000; i++)
	{
		accounts[i].reset(new CAccount());
		accounts[i]->SetAccountNumber(i);
	}

}

void CAccountsHandler::SetStartTime()
{
	iStartTime = GetTickCount();
}



CAccountsHandler::~CAccountsHandler()
{
}


void CAccountsHandler::IdentifyAccountWithHighestBalance()
{
	std::sort(accounts.begin(), accounts.end(), Compare);
}


void CAccountsHandler::CalculateAverageBalance()
{
	double dSum = 0.0;
	for (auto& n : accounts)
		dSum += n->GetBalance();

	dAverageBalance = dSum / 10000;
}

bool CAccountsHandler::IsThreadRunnable()
{
	bool bCanRun = true;
	if (dAverageBalance == 1100)
		bCanRun = false;

	iCurrentTime = GetTickCount();
	unsigned int uDiffTime = iCurrentTime - iStartTime;
	if (uDiffTime >= 120000) //Has run for 2 minutes 
		bCanRun = false;

	return bCanRun;
}


void CAccountsHandler::PerformDebit()
{

	std::unique_lock<std::mutex> lock(mtx);
	while (!ready)
		cv.wait(lock);


	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> GenAcctnum(0, 9999);
	std::uniform_real_distribution<> GenAmount(50, 200);

	int iAcc = GenAcctnum(gen);
	double dAmount = GenAmount(gen);

	//srand(time(0));
	//unsigned int iAcc = int(rand() % 10000);
	//srand(time(0));
	//ouble dAmount = double((rand() % 151) + 50); //To generate random numbers from 50 to 200

	accounts[iAcc]->AddDebitTransaction(dAmount);

}

void CAccountsHandler::PerformCredit()
{

	std::unique_lock<std::mutex> lock(mtx);
	while (!ready)
		cv.wait(lock);

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> GenAcctnum(0, 9999);
	std::uniform_real_distribution<> GenAmount(100, 400);

	int iAcc = GenAcctnum(gen);
	double dAmount = GenAmount(gen);

	accounts[iAcc]->AddCreditTransaction(dAmount);
}

void CAccountsHandler::PerformAnalysis()
{
	std::unique_lock<std::mutex> lck(mtx);
	CalculateAverageBalance();
	ready = true;
	int x = 10000;
	//std::cout << "sleep during the analysis" << std::endl;
	//std::this_thread::sleep_for(std::chrono::milliseconds(x));
	cv.notify_all();

}


void CAccountsHandler::Debit() 
{
	while (true)
	{
		if (!IsThreadRunnable())
			break;
		unsigned int Now = GetTickCount();
		unsigned int uDiffTime = Now - iStartTime;
		if (uDiffTime % 20 == 0)
		{
			//Every 20 milliseconds a transaction is called thus 50 transaction per second
			PerformDebit();
		}
	}
}


void CAccountsHandler::Credit()
{
	while (true)
	{
		if (!IsThreadRunnable())
			break;
		unsigned int Now = GetTickCount();
		unsigned int uDiffTime = Now - iStartTime;
		if (uDiffTime % 10 == 0)
		{
			//Every 10 milliseconds a transaction is called thus 100 transaction per second
			PerformCredit();
		}			
	}
}


void CAccountsHandler::Analysis() 
{

	while (true)
	{
		if (!IsThreadRunnable())
			break;
		unsigned int Now = GetTickCount();
		unsigned int uDiffTime = Now - iStartTime;
		if (uDiffTime % 1000 == 0)
		{
			//Every 1000 milliseconds an analysis is called thus 1 analysis per second
			PerformAnalysis();
		}
	}
}


void CAccountsHandler::PrintTransactionHistory()
{
	//Below call is only valid after calling IdentifyAccountWithHighestBalance()
	accounts[accounts.size()-1]->PrintTransactionHistory();
}