#include "pch.h"
#include <iostream>
#include <windows.h>
#include "NTFS_FS.h"


int main()
{
	std::cout << "Surnin Mikhail RI-541215" << std::endl;
	NTFS_FS fileSystem;
	fileSystem.Open();
	BYTE startBuffer[2048];
	fileSystem.GetFirstSector(startBuffer);
	fileSystem.CheckFileSystem(startBuffer);
	std::cout << "OEM Name: ";
	std::cout << fileSystem.GetOEMName() << std::endl;
	std::cout << "Bytes Per Cluster: ";
	std::cout << fileSystem.GetBytesPerCluster() << std::endl;
	std::cout << "Number of clusters: ";
	std::cout << fileSystem.GetTotalClusters() << std::endl << std::endl << std::endl;
	

	ULONGLONG stCluster;
	DWORD number;
	std::cout << "Enter initial cluster: ";
	std::cin >> stCluster;
	std::cout << "Enter number of cluster: ";
	std::cin >> number;
	DWORD bufferSize = number * fileSystem.GetBytesPerCluster();
	BYTE * databuffer = new BYTE[bufferSize];
	std::cout << "Your data: " << std::endl;
	fileSystem.ReadClusters(stCluster,number,databuffer);

	system("pause");
	return 0;
 
}


