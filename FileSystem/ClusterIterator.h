#pragma once
#include "AbstractClassFS.h"


class ClusterIterator
{
protected:
	ULONGLONG currentClusterPosition;
	AbstractClassFS *fs;
	BYTE * buffer;

public:
	ClusterIterator();
	ClusterIterator(AbstractClassFS *fs);
	~ClusterIterator();
	void First();
	void Next();
	bool IsDone();
	BYTE * GetCurrent();

};

