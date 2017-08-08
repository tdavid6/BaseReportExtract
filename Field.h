#pragma once

#include <string>

class Field
{
private:
	std::string fieldName;
	std::string fieldData;
public:
	void setName(std::string str) { fieldName = str; }
	std::string getName() { return fieldName; }

	void addData(std::string str) { fieldData = str; }
	std::string getData() { return fieldData; }

public:
	Field(std::string name, std::string data) : fieldName(name), fieldData(data) {}
	~Field() {}
};