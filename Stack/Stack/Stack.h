#pragma once
#include <vector>

class CStack
{
public:
	CStack();
	virtual ~CStack();
	
	bool Push(double);
	double Pop();
	
private:
	double dStack[100];
	int head = 0; 
};

