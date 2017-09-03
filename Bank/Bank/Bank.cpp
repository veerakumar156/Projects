// Bank.cpp : Defines the entry point for the console application.
//
#include <Windows.h>
#include <memory>
#include "stdafx.h"
#include "AccountsHandler.h"

//Bank:
//------
// CAccountsHandler is the driver class that spawns threads for various transaction
// It holds the 10,000 accounts as its data member of type CAccount. The class 
// CAccount holds a class called Transaction that has details of any transaction such 
// as transaction amount, transaction type. 


int main()
{
	std::tr1::shared_ptr<CAccountsHandler> accountHandler; 
	accountHandler.reset(new CAccountsHandler());
	accountHandler->SetStartTime();
	std::thread tw1 = accountHandler->DebitThread(); 
	std::thread tw2 = accountHandler->CreditThread(); 
	std::thread tw3 = accountHandler->AnalysisThread(); 

	tw1.join();
	tw2.join();
	tw3.join();

	accountHandler->IdentifyAccountWithHighestBalance(); 
	accountHandler->PrintTransactionHistory();

    return 0;
}
