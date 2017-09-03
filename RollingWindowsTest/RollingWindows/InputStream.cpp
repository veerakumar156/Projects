
#include "stdafx.h"
#include "InputStream.h"


CInputStream::CInputStream(const std::vector<double>& iVec)
{
	vStream.assign(iVec.begin(), iVec.end());
}

CInputStream::CInputStream()
{
	using namespace std;
	std::cout << "Enter the length of the stream" << std::endl; 
	int length;
    std::cin >> length;
	int ip;
	for (int i = 0; i < length; i++)
	{
		std::cout << "Enter the " << i << " number " << std::endl;
	    std::cin >> ip; 
		vStream.push_back(ip);
	}
}

CInputStream::~CInputStream()
{
}

bool CInputStream::HasNext()
{
	if (iPtrToStream >= vStream.size())
		return false;
	else
		return true; 
}

double CInputStream::GetNext()
{
	if (HasNext())
	{
		return vStream[iPtrToStream++];
	}
	else
	{
		return NAN;
	}
}
