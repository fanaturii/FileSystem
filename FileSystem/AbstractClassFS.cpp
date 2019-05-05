#include "pch.h"
#include "AbstractClassFS.h"
#include <string>
#include <iostream>



AbstractClassFS::AbstractClassFS()
{
}


AbstractClassFS::~AbstractClassFS()
{
}

bool AbstractClassFS::Open()
{
	std::wstring FileName1 = L"\\\\.\\";
	std::wstring FileName2;
	std::wstring FileName3 = L":";
	std::wcout << L"Enter logical disk name (ex. C,D): ";
	std::wcin >> FileName2;
	FileName2 += FileName3;
	FileName1 += FileName2;
	WCHAR * fileName = &FileName1[0];

	FileHandle = CreateFileW(
							fileName,
							GENERIC_READ,
							FILE_SHARE_READ,
							NULL,
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							NULL
	);

	if (FileHandle == INVALID_HANDLE_VALUE) {
		std::cout << "Error: Can`t open disk!" << std::endl;
		exit(100);
		return false;
	}
	else {
		return true;
	}
}

void AbstractClassFS::GetFirstSector(BYTE * bufferFirst)
{
	DWORD bytesRead;
	bool readResult = ReadFile(
						FileHandle,
						bufferFirst,
						512,
						&bytesRead,
						NULL
	);

	if (!readResult) {
		std::cout << "Error read first sector!" << std::endl;
		exit(101);
	}
	
}

BYTE * AbstractClassFS::GetOEMName()
{
	return OEMName;
}


DWORD AbstractClassFS::GetBytesPerCluster() const
{
	return BytesPerCluster;
}

DWORD AbstractClassFS::GetTotalClusters() const
{
	return TotalClusters;
}

bool AbstractClassFS::ReadClusters(ULONGLONG startCluster, DWORD numberOfClusters, BYTE * outBuffer)
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
			std::cout << std::hex << DWORD(* outBuffer) << " ";
			outBuffer++;
			i++;
		}
		return true;
	}
}

void AbstractClassFS::Close()
{
	CloseHandle(FileHandle);
}


