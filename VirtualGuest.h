#pragma once

#include <string>
#include <vector>

#include "Field.h"
#include "TimeStamp.h"

class VirtualGuest
{
private:
	std::vector<std::string> identifier;
	std::string serialNum;
	std::vector<TimeStamp> stamps;

	std::vector<Field> Fields;
public:
	VirtualGuest();
	~VirtualGuest();
public:
	void addReading(std::string stamp, int index, int source);
	void addSource(std::string str);
	void addSerial(std::string);
	void addField(std::string fieldName, std::string fieldData);

	std::string getIdentifier(int source);
	std::string getSerial();
	
	void compareStamps(int source);
	int getOldestData(int source);
	bool checkEmpty(int source);
	std::string getFieldData(std::string name);
};

