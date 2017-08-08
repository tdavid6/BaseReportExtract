#pragma once

#include <vector>
#include <string>

class TimeStamp
{
private:
	std::vector<std::string> timeStamp;
	std::vector<int> rowIndex;
	int oldestData;
public:
	TimeStamp();
	~TimeStamp();
public:
	void addTimeStamp(std::string stamp);
	void addRowIndex(int index);
	void compareStamps();
	std::string getTimeStamp(int index);
	int getIndex(int index);
	int getOldestData();
	bool checkEmpty();
};

