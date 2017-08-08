#pragma once
#include <iostream>
#include <string>
#include <vector>

struct FieldIndices
{
	enum
	{
		AIX_LPAR, KPH_SERVER_DETAILS, KPH_MANAGED_LPARS, Unknown
	};

	static const int fieldAmt = 12;

	std::string Source_Title[fieldAmt] =
	{
		"System_Name", "State", "Entitlement",
		"Number_of_Virtual_CPUs", "Entitlement_Used_Pct", "Online_Mem",
		"Max_Memory", "CEC_name", /*Derived from */"CEC_name"/* Suffix*/,
		"Uptime", "Node", "CEC_Model"
	};

	std::string Field_Title[fieldAmt] =
	{
		"TEPS Guest Name", "Guest Status", "Guest CPU Total AIX",
		"Guest Max CPU Total AIX", "Guest CPU Pct Used AIX", "Guest Memory Total AIX",
		"Guest Memory Max AIX", "Physical Host Name", "Cluster Name",/* "Location",*/ /*"Specific Location",*/
		"Guest Uptime", "Management Tool", "Physical Host Model"
	};

	int Source_Num[fieldAmt] =
	{
		AIX_LPAR, KPH_SERVER_DETAILS, AIX_LPAR,
		AIX_LPAR, AIX_LPAR, AIX_LPAR,
		AIX_LPAR, KPH_SERVER_DETAILS, KPH_SERVER_DETAILS, /*KPH_SERVER_DETAILS, *//*KPH_SERVER_DETAILS,*/
		AIX_LPAR, KPH_SERVER_DETAILS, KPH_SERVER_DETAILS
	};

	int case_Num[fieldAmt] =
	{
		0, 0, 0, 
		0, 0, 0, /*2,*//*3,*/
		0, 0, 1,
		0, 2, 0
	}; //designates special cases (0 signifies whole string of data is used) (otherwise data parsed)
};