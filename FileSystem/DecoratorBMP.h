#pragma once
#include "ClusterIterator.h"
class DecoratorBMP : public ClusterIterator
{
protected:
	ClusterIterator *iterator;
	BOOL isNextNotAvailable;
public:
	DecoratorBMP(ClusterIterator *iterator);
	~DecoratorBMP();
	void First();
	void Next();
	bool IsDone();
	BYTE * GetCurrent();

};

