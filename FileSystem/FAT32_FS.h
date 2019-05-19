#pragma once
#include "AbstractClassFS.h"

typedef struct
{
	BYTE Padding1[3];
	BYTE OEM_Name[8];
	BYTE SectorSize[2];
	BYTE SectorsInCluster;
	BYTE Padding2[18];
	ULONGLONG SectorCount;
} FAT32_BootRecord;

class FAT32_FS : public AbstractClassFS
{
public:
	FAT32_FS(BYTE * parameters, HANDLE fileHandle);
	~FAT32_FS();
	virtual bool ReadClusters(ULONGLONG startCluster, DWORD numberOfClusters, BYTE *outBuffer);
};

