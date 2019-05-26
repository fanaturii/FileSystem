#include "pch.h"
#include "DecoratorBMP.h"


DecoratorBMP::DecoratorBMP(ClusterIterator *iterator)
{
	this->iterator = iterator;
	this->isNextNotAvailable = 0;
}


DecoratorBMP::~DecoratorBMP()
{
}

void DecoratorBMP::First()
{
	this->isNextNotAvailable = 0;
	iterator->First();
	BYTE * bufferByte = { 0 };
	bufferByte = iterator->GetCurrent();
	while (!(int(bufferByte[0]) == 66 && int(bufferByte[1]) == 77 && int(bufferByte[2]) == 82))
	{
		delete(bufferByte);
		iterator->Next();
		bufferByte = iterator->GetCurrent();
		if (iterator->IsDone()) {
			this->isNextNotAvailable = 1;
			break;
		}
	}
}

void DecoratorBMP::Next()
{
	int temp = 0;
	if (this->isNextNotAvailable == 1 || this->iterator->IsDone()) {
		
	}
	else {
		iterator->Next();
		BYTE * bufferByte = { 0 };
		while (true)
		{
			delete(bufferByte);
			bufferByte = iterator->GetCurrent();
			if (iterator->IsDone()) {
				this->isNextNotAvailable = 1;
				break;
			}
			if (int(bufferByte[0]) == 66 && int(bufferByte[1]) == 77 && int(bufferByte[2]) == 82) {
				break;
			}
			iterator->Next();
		}
		
	}
}

bool DecoratorBMP::IsDone()
{
	if (this->isNextNotAvailable == 1 || this->iterator->IsDone()) {
		return true;
	}
	else {
		return false;
	}
	
}

BYTE * DecoratorBMP::GetCurrent()
{
	return iterator->GetCurrent();
}
