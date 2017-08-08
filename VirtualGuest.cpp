#include "VirtualGuest.h"



VirtualGuest::VirtualGuest()
{
}


VirtualGuest::~VirtualGuest()
{
}

void VirtualGuest::addSource(std::string str)
{
	identifier.push_back(str);
	TimeStamp newStamp;
	stamps.push_back(newStamp);
}
void VirtualGuest::addReading(std::string stamp, int index, int source)
{
	//stamps.push_back()
	//TimeStamp newStamp(stamp, index);
	stamps[source].addTimeStamp(stamp);
	stamps[source].addRowIndex(index);
}

void VirtualGuest::compareStamps(int source)
{
	stamps[source].compareStamps();
}

void VirtualGuest::addField(std::string fieldName, std::string fieldData)
{
	Field newField(fieldName, fieldData);
	Fields.push_back(newField);
}

std::string VirtualGuest::getFieldData(std::string name)
{
	for (int f = 0; f < Fields.size(); f++)
	{
		if (Fields[f].getName() == name)
			return Fields[f].getData();
	}
	return "Not found";
}

void VirtualGuest::addSerial(std::string serial)
{
	serialNum = serial;
}

bool VirtualGuest::checkEmpty(int source)
{
	return stamps[source].checkEmpty();
}

std::string VirtualGuest::getIdentifier(int source)
{
	return identifier[source];
}

std::string VirtualGuest::getSerial()
{
	return serialNum;
}

int VirtualGuest::getOldestData(int source)
{
	return stamps[source].getOldestData();// *oldestData;
}