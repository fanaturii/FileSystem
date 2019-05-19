#include "pch.h"
#include "AbstractClassFS.h"
#include <string>
#include <iostream>



AbstractClassFS::AbstractClassFS()
{
}


AbstractClassFS::~AbstractClassFS()
{
}



BYTE * AbstractClassFS::GetOEMName()
{
	return OEMName;
}


DWORD AbstractClassFS::GetBytesPerCluster() const
{
	return BytesPerCluster;
}

DWORD AbstractClassFS::GetTotalClusters() const
{
	return TotalClusters;
}


void AbstractClassFS::Close()
{
	CloseHandle(FileHandle);
}


