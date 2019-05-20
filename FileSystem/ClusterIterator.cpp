#include "pch.h"
#include "ClusterIterator.h"


ClusterIterator::ClusterIterator(AbstractClassFS *fs)
{
	this -> currentClusterPosition = 0;
	this -> fs = fs;
}


ClusterIterator::~ClusterIterator()
{
}

void ClusterIterator::First()
{
	currentClusterPosition = 0;
}

void ClusterIterator::Next()
{
	currentClusterPosition ++;
}

bool ClusterIterator::IsDone()
{
	if (currentClusterPosition >= fs->GetTotalClusters()) {

		return true;
	}
	else {

		return false;
	}
	
}

BYTE * ClusterIterator::GetCurrent()
{
	BYTE * buffer = new BYTE[fs->GetBytesPerCluster()];
	if (fs->ReadClusters(currentClusterPosition, 1, buffer)) {

		return buffer;
	}
	else {

		return { 0 };
	}

}
