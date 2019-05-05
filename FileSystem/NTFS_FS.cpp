#include "pch.h"
#include "NTFS_FS.h"
#include <string>
#include <iostream>


NTFS_FS::NTFS_FS()
{
}


NTFS_FS::~NTFS_FS()
{
}

void NTFS_FS::SetParameters(BYTE * bufferParameters)
{
	NTFS_BootRecord * bootRecord = (NTFS_BootRecord*)bufferParameters;
	memcpy(OEMName,bootRecord->OEM_Name,sizeof(OEMName));
	BytesPerSector = *((WORD*)bootRecord->SectorSize);
	SectorsPerCluster = bootRecord->SectorsInCluster;
	BytesPerCluster = SectorsPerCluster * BytesPerSector;
	TotalClusters = bootRecord->SectorCount / SectorsPerCluster;

}

bool NTFS_FS::CheckFileSystem(BYTE * bufferCheck)
{
	std::string NTFS_Name = "NTFS";
	NTFS_BootRecord * bootRecord = (NTFS_BootRecord*)bufferCheck;
	std::string OEM((char *)bootRecord->OEM_Name, 4);
	

	if (OEM.compare(NTFS_Name) == 0) {
		this->SetParameters(bufferCheck);
		return true;
	}
	else {
		std::cout << "It`s not a NTFS file system!" << std::endl;
		exit(500);
		return false;
	}
}
