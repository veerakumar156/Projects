#include "stdafx.h"
#include "Account.h"
#include <fstream>

CAccount::CAccount()
{
	//default account number

}


CAccount::~CAccount()
{

}

void CAccount::SetAccountNumber(const int& i)
{
	iAccoutNumber = i;
}

void CAccount::PrintTransactionHistory()
{
	std::ofstream fileptr; 
	fileptr.open("TransactionHistory.txt");

	fileptr << "The account number is: " << iAccoutNumber << std::endl;
	fileptr << "The balance in the account is: " << dBalance << std::endl;
	fileptr << "The transactions on this account are :" << std::endl;
	for (auto vTr : vTransactions)
	{
		fileptr << "Transaction type " << vTr->GetTransactionType()
			<< "\tTransaction amount: " << vTr->GetTransactionAmount() << std::endl;
	}

	fileptr.close();
}

void CAccount::AddDebitTransaction(const double & dAmount)
{
	dBalance = dBalance - dAmount; 
	std::tr1::shared_ptr<CTransaction> Tr; 
	Tr.reset(new CTransaction());
	Tr->SetTransactionAmount(dAmount); 
	Tr->SetTransactionType("Debit");
	vTransactions.push_back(Tr);
}


void CAccount::AddCreditTransaction(const double & dAmount)
{
	dBalance = dBalance + dAmount;
	std::tr1::shared_ptr<CTransaction> Tr;
	Tr.reset(new CTransaction());
	Tr->SetTransactionAmount(dAmount);
	Tr->SetTransactionType("Credit");
	vTransactions.push_back(Tr);
}