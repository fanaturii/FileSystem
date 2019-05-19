#pragma once
#include "AbstractClassFS.h"
#include "NTFS_FS.h"
#include "FAT32_FS.h"
#include "ExFAT_FS.h"

typedef struct
{
	BYTE Padding1[3];
	BYTE OEM_Name[8];
} OEMRecord;


class FileSystemChecker
{
protected:
	HANDLE FileHandle;
public:
	FileSystemChecker();
	~FileSystemChecker();
	bool Open();
	void GetFirstSector(BYTE * bufferFirst);
	HANDLE GetHandle();
	static AbstractClassFS * CreateFileSystem(BYTE * buffer, HANDLE FileHandle);
};

