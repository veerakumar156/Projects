/**
* @file   inputstream.h
* @Author Veerakumar Murugesan 
* @date   August 18, 2017
* @brief  Class declaration to handle the stream of input numbers 
*
*/

#pragma once
#include <iostream>
#include <vector>
class CInputStream
{
public:
	CInputStream();
	CInputStream(const std::vector<double>& iVec);
	virtual ~CInputStream(); 

	// Returns true if more elements are available
	bool HasNext();

	// Get the next element in the stream
	double GetNext();

private:
	std::vector<double> vStream; 
	size_t iPtrToStream = 0; 
};

