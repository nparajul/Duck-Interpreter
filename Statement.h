/**/
/*
NAME

		Statement.h- holds the statement that make up a duck program.


DESCRIPTION

		Within this class, the statement are recorded in a vector. It also consists of a map that links labels to statements.
		It also provides access to statements based on position and label by searching them in the map and/or the vector.


AUTHOR

		Nitesh Parajuli

DATE

		11:38pm 5/15/2019

*/
/**/



#pragma once
class Statement
{
public:
	
	void RecordStatements(string a_sourceFileName);
	
	string GetStatement(int a_statementNum);
	
	int GetLabelLocation(string a_string);
	

private:

	//stores all statement
	vector<string> m_statements;

	//stores the label and the position of the statement in the label
	map<string, int> m_labelToStatement;
};

