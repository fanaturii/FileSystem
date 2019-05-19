#pragma once
#include <windows.h>


class AbstractClassFS
{
protected:
	HANDLE FileHandle;
	BYTE OEMName[8];
	DWORD BytesPerSector;
	DWORD SectorsPerCluster;
	DWORD BytesPerCluster;
	DWORD TotalClusters;

public:
	AbstractClassFS();
	~AbstractClassFS();
	BYTE *GetOEMName();
	DWORD GetBytesPerCluster() const;
	DWORD GetTotalClusters() const;
	virtual bool ReadClusters(ULONGLONG startCluster, DWORD numberOfClusters, BYTE *outBuffer) = 0;
	void Close();
};

