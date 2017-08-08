#include "SourceFile.h"
#include <algorithm>



SourceFile::SourceFile(std::string myFile, std::string unique)
	: fileName(myFile)
{
	if (readFile());
	{
		delimPositions();
		buildPrincipal(unique);
	}
}


SourceFile::~SourceFile()
{
}

bool SourceFile::readFile()
{
	std::ifstream file;
	file.open(fileName);

	if (!file.is_open())
	{
		std::cerr << "File " << fileName << " failed to open" << std::endl;
		return false;
	}

	std::string title = "";
	getline(file, title);
	titleLine = title;

	do
	{
		std::string line = "";
		getline(file, line);
		dataLine.push_back(line);
	} while (file);
	return true;
}

void SourceFile::delimFinder(const std::string& str, const char &delim, std::vector<int>& positions)
{
	for (int i = 0; i < str.size() - 1; i++)
	{
		if (str[i] == delim)
			positions.push_back(i);
	}

}

void SourceFile::delimPositions()
{
	delimFinder(titleLine, ',', titlePositions);

	std::vector<int> empty_int_vector;
	for (int i = 0; i < dataLine.size() - 1; i++)
	{
		dataPositions.push_back(empty_int_vector);
		delimFinder(dataLine[i], ',', dataPositions[i]);
	}
}

void SourceFile::buildPrincipal(std::string identifier)
{
	int hostIndex = indexField(identifier);
	for (int row = 0; row < getDataSize() - 1; row++)
	{
		std::string hostPusher = locateFieldData(row, hostIndex);
		principalVector.push_back(hostPusher);
	}
	quickSort(&principalVector[0], &principalVector[principalVector.size() - 1]);
	principalCount = removeDuplicates(principalVector);
}

int SourceFile::indexField(std::string titleName)
{
	int pos = 0; 
	int size = titlePositions.size();
	std::string tmp = titleLine.substr(pos, titlePositions[0] - pos);
	if (titleName == tmp)
		return 0;
	tmp = titleLine.substr(titlePositions[size - 1] + 1);
	if (titleName == tmp)
		return size;
	for (int t = 1; t < size; t++)
	{
		pos = titlePositions[t - 1] + 1;
		tmp = titleLine.substr(pos, titlePositions[t] - pos);
		if (tmp == titleName)
			return t;
	}
	return -1;
}

std::string SourceFile::locateFieldData(int row, int col)
{
	int pos = 0;
	if (col == 0)
		return dataLine[row].substr(pos, dataPositions[row][col - 1] - pos);
	pos = dataPositions[row][col - 1] + 1;
	if (col == dataPositions[row].size())
		return dataLine[row].substr(pos);
	else
		return dataLine[row].substr(pos, dataPositions[row][col] - pos);
}


int SourceFile::removeDuplicates(std::vector<std::string> &sorted)
{
	int prev = 0;
	for (int i = 0; i < sorted.size(); i++)
	{
		if (sorted[i] != sorted[prev])
			sorted[++prev] = sorted[i];
	}
	int count = prev + 1;
	return count;
}

void SourceFile::quickSort(std::string* begin, std::string* end)
{
	if (end - begin < 2)
		return;
	std::string* left = begin;
	std::string* right = end - 1;

	int rando = rand();
	std::string* pivot = left + rando % (right - left + 1);

	while (left != right)
	{
		while (*left < *pivot)
			++left;
		while (*right >= *pivot && left < right)
			--right;

		if (pivot == left)
			pivot = right;
		
		std::swap(*left, *right);
		
	}

	std::swap(*pivot, *left);
	

	quickSort(begin, left);
	quickSort(left + 1, end);
}

int SourceFile::getDataSize()
{
	return dataLine.size();
}

int SourceFile::getGuestCount()
{
	return principalCount;
}

std::string SourceFile::principalTitle(int guestPosition)
{
	return principalVector[guestPosition];
}