#pragma once
#include "AbstractClassFS.h"
#include <cmath>

typedef struct
{
	BYTE Padding1[3];
	BYTE OEM_Name[8];
	BYTE Padding2[0x3D];
	ULONGLONG TotalSectors;
	DWORD FAT_StartSector;
	DWORD FAT_Size;
	DWORD FirstDataSector;
	DWORD TotalClusters;
	DWORD RootDirCluster;
	BYTE Padding3[8];
	BYTE SectorFactor;
	BYTE ClusterFactor;

} ExFAT_BootRecord;

class ExFAT_FS : public AbstractClassFS
{
protected:
	DWORD FirstDataSector;
public:
	ExFAT_FS(BYTE * parameters, HANDLE fileHandle);
	~ExFAT_FS();
	virtual bool ReadClusters(ULONGLONG startCluster, DWORD numberOfClusters, BYTE *outBuffer);
};

