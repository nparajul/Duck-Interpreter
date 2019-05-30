/**/
/*
NAME

		SymbolTable.h- holds all the variables.


DESCRIPTION

		This class holds all the variable and their value in a map. It also supplies tools to get and set variables. If a variable is referenced before
	declaring it, an error will be thrown.


AUTHOR

		Nitesh Parajuli

DATE

		11:49pm 5/15/2019

*/
/**/


#pragma once
class SymbolTable
{
public:
	
	void RecordVariableValue(string a_variable, double a_value);
		
	bool GetVariableValue(string a_variable, double &a_value);
		
	void printMap();
	
private:
	
	// stores the variable and its value
	unordered_map<string, double> m_SymbolTable;
};

