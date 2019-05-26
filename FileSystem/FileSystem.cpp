#include "pch.h"
#include <iostream>
#include <windows.h>
#include "NTFS_FS.h"
#include "FileSystemChecker.h"
#include "ClusterIterator.h"
#include "DecoratorBMP.h"


int main()
{
	//Вывод информации о файловой системе
	std::cout << "Surnin Mikhail RI-541215" << std::endl;
	FileSystemChecker fileSystem;
	HANDLE handle;
	BYTE startBuffer[2048];
	fileSystem.Open();
	fileSystem.GetFirstSector(startBuffer);
	handle = fileSystem.GetHandle();
	AbstractClassFS * fs = fileSystem.CreateFileSystem(startBuffer, handle);
	std::cout << "OEM Name: ";
	std::cout << fs -> GetOEMName() << std::endl;
	std::cout << "Bytes Per Cluster: ";
	std::cout << fs -> GetBytesPerCluster() << std::endl;
	std::cout << "Number of clusters: ";
	std::cout << fs -> GetTotalClusters() << std::endl << std::endl << std::endl;
	

	//ULONGLONG stCluster;
	//DWORD number;
	//std::cout << "Enter initial cluster: ";
	//std::cin >> stCluster;
	//std::cout << "Enter number of cluster: ";
	//std::cin >> number;
	//DWORD bufferSize = number * fs -> GetBytesPerCluster();
	//BYTE * databuffer = new BYTE[bufferSize];
	//std::cout << "Your data: " << std::endl;
	//fs -> ReadClusters(stCluster,number,databuffer);

	//Считаем количество BMP файлов
	ClusterIterator iterator = ClusterIterator(fs);
	DecoratorBMP decorator = DecoratorBMP(&iterator);
	decorator.First();
	int counter = 0;
	while (!decorator.IsDone())
	{
		counter++;
		decorator.Next();
	}
	std::cout << "Count of BMP images: " << counter << std::endl;

	system("pause");
	return 0;
 
}


