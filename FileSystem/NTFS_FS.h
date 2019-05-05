#pragma once
#include "AbstractClassFS.h"


typedef struct
{
	BYTE Padding1[3];
	BYTE OEM_Name[8];
	BYTE SectorSize[2];
	BYTE SectorsInCluster;
	BYTE Padding2[26];
	ULONGLONG SectorCount;
} NTFS_BootRecord;


class NTFS_FS : public AbstractClassFS
{
public:
	NTFS_FS();
	~NTFS_FS();
	virtual void SetParameters(BYTE * bufferParameters);
	virtual bool CheckFileSystem(BYTE * bufferCheck);
	
};

