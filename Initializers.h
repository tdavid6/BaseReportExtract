#pragma once

#include <vector>
#include <string>
#include "SourceFile.h"

class Initializers
{
private:
	std::vector<std::string> fieldNames;
	std::vector<int> positionIndices;
public:
	Initializers();
	~Initializers();
public:
	void addTitle(std::string str);
	void buildIndex(SourceFile &file);
	std::string getKey(int row, SourceFile &file);
	std::string getTimeStamp(int row, SourceFile &file);
	std::string getSerial(int row, SourceFile &file);
};

