//implementation of SymbolTable.h

#include "stdafx.h"
#include "SymbolTable.h"

/**/
/*
void SymbolTable::RecordVariableValue()

NAME

		SymbolTable::RecordVariableValue - Records/ Updates the value of a variable.

SYNOPSIS


			void SymbolTable::RecordVariableValue(string a_variable, double a_value);


			a_variable			--> the name of the variable
			a_value             --> a variable's value


DESCRIPTION

		This functions stores a variable and its value in the m_SymbolTable map.


RETURNS

		Nothing. It's a void function.
AUTHOR

		Nitesh Parajuli

DATE

		10:06pm 5/15/2019

*/
/**/

void SymbolTable::RecordVariableValue(string a_variable, double a_value)
{
	m_SymbolTable[a_variable] = a_value;
}

/**/
/*
bool SymbolTable::GetVariableValue()

NAME

		SymbolTable::GetVariableValue - Returns the value of a variable, if it exists.

SYNOPSIS


			bool SymbolTable::GetVariableValue(string a_variable, double &a_value);


			a_variable			--> the name of the variable
			a_value             --> holds the value of a variable


DESCRIPTION

		This function checks if a variable exists in the map and gets its value if it exists. If not, error message
		will be displayed.


RETURNS

		Returns true if variable exists, false if not.

AUTHOR

		Nitesh Parajuli

DATE

		10:17pm 5/15/2019

*/
/**/

bool SymbolTable::GetVariableValue(string a_variable, double &a_value)
{
	unordered_map<string, double>::iterator it;

	it = m_SymbolTable.find(a_variable);

	if (it != m_SymbolTable.end())
	{
		a_value = it->second;
		return true;
	}

	return false;
}

/**/
/*
void SymbolTable::printMap()

NAME

		SymbolTable::printMap - Returns the value of a variable, if it exists.

SYNOPSIS


			void SymbolTable::printMap();


DESCRIPTION

		This function displays all variables and their values.


RETURNS

		Nothing. It's a void function.

AUTHOR

		Nitesh Parajuli

DATE

		10:23pm 5/15/2019

*/
/**/

void SymbolTable::printMap()
{
	for (unordered_map<string, double>::iterator it = m_SymbolTable.begin(); it != m_SymbolTable.end(); ++it)
	{
		cout << it->first << " => " << it->second << '\n';
	}
}