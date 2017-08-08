#include <iostream>
#include"SourceFile.h"
#include "VirtualGuest.h"
#include "Initializers.h"
#include "FieldIndices.h"

void delimFinder(const std::string& str, const char &delim, std::vector<int>& positions);
void fillData(const std::string &sourceTitle, SourceFile &source, VirtualGuest &myGuest, const std::string &fieldTitle, int which, int parse);
void exportData(std::vector<VirtualGuest> &exportInfo);
int main()
{
	SourceFile sources[2] =
	{
		{ "la.txt", "Hostname"},
		{ "ka.txt", "CEC_SN" }
	};
	int number_of_sources = sizeof(sources) / sizeof(sources[0]);
	
	Initializers empty_init;
	std::vector<Initializers> init;
	for (int whichSource = 0; whichSource < number_of_sources; whichSource++)
		init.push_back(empty_init);

	init[0].addTitle("Hostname");
	init[0].addTitle("Timestamp");
	init[0].addTitle("Machine_Serial");

	init[1].addTitle("CEC_SN");
	init[1].addTitle("Timestamp");

	for (int whichSource = 0; whichSource < number_of_sources; whichSource++)
		init[whichSource].buildIndex(sources[whichSource]);

	
	std::vector<VirtualGuest> virtualGuestVector;
	int guestTotal = sources[0].getGuestCount();

	for (int i = 0; i < guestTotal; i++)
		virtualGuestVector.push_back(VirtualGuest());

	for (int i = 0; i < guestTotal; i++)
	{
		std::string tmp = sources[0].principalTitle(i);
		virtualGuestVector[i].addSource(tmp);
	}

	for (int whichSource = 0; whichSource < number_of_sources; whichSource++)
	{
		for (int guest = 0; guest < guestTotal; guest++)
		{
			bool found = false;
			
			for (int row = 0; row < sources[whichSource].getDataSize() - 1; row++)
			{
				std::string key = init[whichSource].getKey(row, sources[whichSource]);
				if (key == virtualGuestVector[guest].getIdentifier(whichSource))
				{
					found = true;
					std::string timePusher = init[whichSource].getTimeStamp(row, sources[whichSource]);
					
					virtualGuestVector[guest].addReading(timePusher, row, whichSource);
				}
			}
			if (!found)
			{
				virtualGuestVector[guest].addReading("n/a", -1, whichSource);
			}
		}

		for (int guest = 0; guest < guestTotal; guest++)
			virtualGuestVector[guest].compareStamps(whichSource);
		
		if (!whichSource)
		{
			for (int guest = 0; guest < guestTotal; guest++)
			{
				int row = virtualGuestVector[guest].getOldestData(whichSource);
				std::string serialPusher = init[whichSource].getSerial(row, sources[whichSource]);//source1.locateFieldData(virtualGuestVector[guest].getOldestData(), serialIndex);
				virtualGuestVector[guest].addSerial(serialPusher);
				virtualGuestVector[guest].addSource(serialPusher);
			}
		}
	}
	
	FieldIndices fields;
	for (int guest = 0; guest < guestTotal; guest++)
	{
		for (int fieldPos = 0; fieldPos < FieldIndices::fieldAmt; fieldPos++)
		{
			int fromFile = fields.Source_Num[fieldPos];
			fillData(fields.Source_Title[fieldPos], sources[fromFile], virtualGuestVector[guest], 
				fields.Field_Title[fieldPos], fromFile, fields.case_Num[fieldPos]);
		}
	}
	
	exportData(virtualGuestVector);

	return 0;
}
	
void delimFinder(const std::string& str, const char &delim, std::vector<int>& positions)
{
	for (int i = 0; i < str.size() - 1; i++)
	{
		if (str[i] == delim)
			positions.push_back(i);
	}

}

void fillData(const std::string &sourceTitle, SourceFile &source, VirtualGuest &myGuest, const std::string &fieldTitle, int which, int parse)
{
	int fieldIndex = source.indexField(sourceTitle);
	
	int row = myGuest.getOldestData(which);
	if (myGuest.checkEmpty(which))
		myGuest.addField(fieldTitle, "UNKNOWN");
	else
	{
		std::string pusher = source.locateFieldData(row, fieldIndex);
		switch (parse)
		{
		case 1:
		{
			std::vector<int> positions;
			delimFinder(pusher, '-', positions);
			if (positions.size() == 3)
				pusher = pusher.substr(positions[2] + 1);
			else
				pusher = "n/a";
			break;
		}
		case 2:
		{
			std::vector<int> positions;
			delimFinder(pusher, '-', positions);
			if (pusher.substr(0, 3) == "PH:")
				pusher = pusher.substr(3, positions[0] - 3);
			else
				pusher = "n/a";
			break;
		}
		default:
			break;
		}
		myGuest.addField(fieldTitle, pusher);
	}
}

void exportData(std::vector<VirtualGuest> &exportInfo)
{
	
	std::string outputFile = "BaseReportExtract.txt";
	std::ofstream newFile(outputFile);

	FieldIndices finalFields;
	
	newFile << "Virtual Guest Name" << ",";
	newFile << "Physical Host ID" << ",";

	for (int i = 0; i < finalFields.fieldAmt; i++)
		newFile << finalFields.Field_Title[i] << ",";
	newFile << "\n";

	for (int guest = 0; guest < exportInfo.size(); guest++)
	{
		newFile << exportInfo[guest].getIdentifier(0) << ",";
		newFile << exportInfo[guest].getSerial() << ",";
		for (int fieldPos = 0; fieldPos < finalFields.fieldAmt; fieldPos++)
		{
			newFile << exportInfo[guest].getFieldData(finalFields.Field_Title[fieldPos]) << ",";
		}
		newFile << "\n";
	}
	
}