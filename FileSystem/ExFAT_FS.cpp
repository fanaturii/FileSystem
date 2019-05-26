#include "pch.h"
#include "ExFAT_FS.h"
#include <string>
#include <iostream>


ExFAT_FS::ExFAT_FS(BYTE * parameters, HANDLE fileHandle)
{
	ExFAT_BootRecord * bootRecord = (ExFAT_BootRecord*)parameters;
	memcpy(OEMName, bootRecord->OEM_Name, sizeof(OEMName));
	BytesPerSector = pow(2,bootRecord->SectorFactor);
	SectorsPerCluster = pow(2, bootRecord->ClusterFactor);
	BytesPerCluster = SectorsPerCluster * BytesPerSector;
	TotalClusters = bootRecord->TotalClusters;
	FirstDataSector = bootRecord->FirstDataSector;
	FileHandle = fileHandle;
}


ExFAT_FS::~ExFAT_FS()
{
}

bool ExFAT_FS::ReadClusters(ULONGLONG startCluster, DWORD numberOfClusters, BYTE * outBuffer)
{
	LARGE_INTEGER clusterOffset;
	DWORD bytesToRead;
	DWORD bytesRead;
	ULONGLONG exFATOffset;
	exFATOffset = (512 * FirstDataSector) - (2 * BytesPerCluster);
	clusterOffset.QuadPart = startCluster * BytesPerCluster + exFATOffset;
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
