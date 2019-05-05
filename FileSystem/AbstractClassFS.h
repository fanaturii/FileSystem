#pragma once
#include <windows.h>


class AbstractClassFS
{
protected:
	HANDLE FileHandle;
	BYTE OEMName[8];
	DWORD BytesPerSector;
	DWORD SectorsPerCluster;
	DWORD BytesPerCluster;
	DWORD TotalClusters;

public:
	AbstractClassFS();
	~AbstractClassFS();
	bool Open();
	void GetFirstSector(BYTE * bufferFirst);
	virtual void SetParameters(BYTE * bufferParameters) = 0;
	virtual bool CheckFileSystem(BYTE * bufferCheck) = 0;
	BYTE *GetOEMName();
	DWORD GetBytesPerCluster() const;
	DWORD GetTotalClusters() const;
	bool ReadClusters(ULONGLONG startCluster, DWORD numberOfClusters, BYTE *outBuffer);
	void Close();
};

