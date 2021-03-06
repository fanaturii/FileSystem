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
		return false;
	}
	//else {
	//	int i = 0;
	//	while (i != bytesToRead) {
	//		if (int(*outBuffer) >= 0 and int(*outBuffer) <= 15) {
	//			std::cout << '0';
	//			std::cout << std::hex << DWORD(*outBuffer) << " ";
	//		}
	//		else {

	//			std::cout << std::hex << DWORD(*outBuffer) << " ";
	//		}
	//		outBuffer++;
	//		i++;
	//		if (i % 16 == 0)
	//		{
	//			std::cout << std::endl;
	//		}
	//	}
	//	return true;
	//}
	else {
		return true;
	}
}


