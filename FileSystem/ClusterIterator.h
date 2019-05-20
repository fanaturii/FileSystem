#pragma once
#include "AbstractClassFS.h"


class ClusterIterator
{
protected:
	ULONGLONG currentClusterPosition;
	AbstractClassFS *fs;

public:
	ClusterIterator(AbstractClassFS *fs);
	~ClusterIterator();
	void First();
	void Next();
	bool IsDone();
	BYTE * GetCurrent();

};

