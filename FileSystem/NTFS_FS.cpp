#include "pch.h"
#include "NTFS_FS.h"
#include <string>
#include <iostream>


NTFS_FS::NTFS_FS(BYTE * parameters, HANDLE fileHandle)
{
	NTFS_BootRecord * bootRecord = (NTFS_BootRecord*)parameters;
	memcpy(OEMName, bootRecord->OEM_Name, sizeof(OEMName));
	BytesPerSector = *((WORD*)bootRecord->SectorSize);
	SectorsPerCluster = bootRecord->SectorsInCluster;
	BytesPerCluster = SectorsPerCluster * BytesPerSector;
	TotalClusters = bootRecord->SectorCount / SectorsPerCluster;
	FileHandle = fileHandle;
}


NTFS_FS::~NTFS_FS()
{
}

bool NTFS_FS::ReadClusters(ULONGLONG startCluster, DWORD numberOfClusters, BYTE * outBuffer)
{
	LARGE_INTEGER clusterOffset;
	DWORD bytesToRead;
	DWORD bytesRead;
	clusterOffset.QuadPart = startCluster * BytesPerCluster;
	bytesToRead = numberOfClusters * BytesPerCluster;
	unsigned long currentPosition = SetFilePointer(
		FileHandle,
		clusterOffset.LowPart,
		&clusterOffset.HighPart,
		FILE_BEGIN
	);

	if (currentPosition != clusterOffset.LowPart) {
		std::cout << "Error: Can`t move pointer!" << std::endl;
		exit(102);
		return false;
	}

	bool readResult = ReadFile(
		FileHandle,
		outBuffer,
		bytesToRead,
		&bytesRead,
		NULL
	);

	if (!readResult || bytesRead != bytesToRead) {
		std::cout << "Error read bytes!" << std::endl;
		exit(103);
		return false;
	}
	else {
		int i = 0;
		while (i != bytesToRead) {
			std::cout << std::hex << DWORD(*outBuffer) << " ";
			outBuffer++;
			i++;
		}
		return true;
	}
}


