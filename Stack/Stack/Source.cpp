// Source.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Stack.h"


int main()
{
	CStack Stack; 
	Stack.Push(6);
	double d = Stack.Pop();
	std::string exp = "2+5*6+7*10";

	int iter = 0;
	char c = exp.at(iter);
	while (c != '\0')
	{
		c = exp[iter];

		iter++;
	}
	return 0;
}
