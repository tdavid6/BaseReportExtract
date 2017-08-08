#include "TimeStamp.h"



TimeStamp::TimeStamp()
{
}


TimeStamp::~TimeStamp()
{
}

void TimeStamp::compareStamps()
{
	oldestData = rowIndex[0];
	std::string last = timeStamp[0];
	for (int i = 0; i < timeStamp.size(); i++)
	{
		if (timeStamp[i] > last)
		{
			oldestData = rowIndex[i];
			last = timeStamp[i];
		}
	}
}

void TimeStamp::addTimeStamp(std::string stamp)
{
	timeStamp.push_back(stamp);
}

void TimeStamp::addRowIndex(int index)
{
	rowIndex.push_back(index);
}

bool TimeStamp::checkEmpty()
{
	for (int i = 0; i < rowIndex.size(); i++)
	{
		if (rowIndex[i] != -1)
			return false;
	}
	return true;
}

std::string TimeStamp::getTimeStamp(int index)
{
	return timeStamp[index];
}
int TimeStamp::getIndex(int index)
{
	return rowIndex[index];
}

int TimeStamp::getOldestData()
{
	return oldestData;
}