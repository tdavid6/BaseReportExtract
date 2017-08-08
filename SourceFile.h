#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class SourceFile
{
private:
	std::string fileName;
	std::string titleLine;
	std::vector<std::string> dataLine;

	std::vector<int> titlePositions;
	std::vector<std::vector<int>> dataPositions;

	std::vector<std::string> principalVector;
	int principalCount;
public:
	SourceFile(std::string myFile, std::string unique);
	~SourceFile();
private:
	bool readFile();
	void delimPositions();
	void quickSort(std::string* begin, std::string* end);
	int removeDuplicates(std::vector<std::string> &sorted);
public:
	void delimFinder(const std::string& str, const char &delim, std::vector<int>& positions);
	void buildPrincipal(std::string identifier);
	int indexField(std::string titleName);
	std::string locateFieldData(int row, int col);

	int getDataSize();
	int getGuestCount();
	std::string principalTitle(int guestPosition);
};

