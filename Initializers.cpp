#include "Initializers.h"



Initializers::Initializers()
{
}


Initializers::~Initializers()
{
}

void Initializers::addTitle(std::string str)
{
	fieldNames.push_back(str);
}

void Initializers::buildIndex(SourceFile &file)
{
	for (int i = 0; i < fieldNames.size(); i++)
	{
		int pos = file.indexField(fieldNames[i]);
		positionIndices.push_back(pos);
	}
}

std::string Initializers::getKey(int row, SourceFile &file)
{
	return file.locateFieldData(row, positionIndices[0]);
}

std::string Initializers::getTimeStamp(int row, SourceFile &file)
{
	return file.locateFieldData(row, positionIndices[1]);
}

std::string Initializers::getSerial(int row, SourceFile &file)
{
	return file.locateFieldData(row, positionIndices[2]);
}