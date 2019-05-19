#include "pch.h"
#include "FileSystemChecker.h"
#include <string>
#include <iostream>


FileSystemChecker::FileSystemChecker()
{
}


FileSystemChecker::~FileSystemChecker()
{
}

bool FileSystemChecker::Open()
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

void FileSystemChecker::GetFirstSector(BYTE * bufferFirst)
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

HANDLE FileSystemChecker::GetHandle()
{
	return FileHandle;
}

AbstractClassFS * FileSystemChecker::CreateFileSystem(BYTE * buffer, HANDLE FileHandle)
{
	std::string NTFS_Name = "NTFS    ";
	std::string FAT32_Name = "MSDOS5.0";
	std::string ExFAT_Name = "EXFAT   ";
	OEMRecord * bootRecord = (OEMRecord*)buffer;
	std::string OEM((char *)bootRecord->OEM_Name, 8);


	if (OEM.compare(NTFS_Name) == 0) {
		
		return new NTFS_FS(buffer, FileHandle);
	}

	else if (OEM.compare(FAT32_Name) == 0) {

		return new FAT32_FS(buffer, FileHandle);
	}

	else if (OEM.compare(ExFAT_Name) == 0) {

		return new ExFAT_FS(buffer, FileHandle);
	}

	else {
		std::cout << "Cannot find known File System!" << std::endl;
		exit(102);

	}
	
}


