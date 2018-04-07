#include "stdafx.h"
#include "Stack.h"

CStack::CStack()
{
}


CStack::~CStack()
{
	delete dStack;
}


bool CStack::Push(double d)
{
	size_t n = sizeof(dStack) / sizeof(double);
	if (head < n)
	{
		dStack[head++] = d;
		return true;
	}
	else
	{
		return false;
	}

}


double CStack::Pop()
{
	if (head <= 0)
	{
		return NULL;
	}

	return dStack[--head];
}
