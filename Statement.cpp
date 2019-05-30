//implementation of Statement.h

#include "stdafx.h"
#include "Statement.h"

/**/
/*
int Statement::RecordStatements()

NAME

		Statement::RecordStatements - Records all statements from a file to a vector.

SYNOPSIS

		void Statement::RecordStatements(string a_sourceFileName);


			a_sourceFileName			--> the name of the file that has all statements in duck language


DESCRIPTION

		This functions reads statement from a file and it stores them in a vector. An error will be thrown if the file
		doesn't exist in the same directory.


RETURNS

		Nothing. It's a void function.
AUTHOR

		Nitesh Parajuli

DATE

		9:49pm 5/15/2019

*/
/**/
void Statement::RecordStatements(string a_sourceFileName)
{
	ifstream inf(a_sourceFileName);
	if (!inf)
	{
		cerr << "could not open the file: " << a_sourceFileName << endl;
		exit(1);
	}
	// Read through the file one line at a time.  Find labs and record them.
	// delete any label and record the remainder of the statement.

	else
	{
		string line;
		string key;
		bool flag = false;
		while (getline(inf,line))
		{			
			for (int i = 0; i < line.length(); i++)
			{				
				if (line[i] == '"')
				{
					break;
				}
				if (line[i] == ':')
				{
					key=line.substr(0, i);
					flag = true;
					line.erase(0, i+1);
					break;
					
				}
			}
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == ';')
				{
					m_statements.push_back(line.substr(0, i+1));

					if(flag==true)
					{
						int count = m_statements.size();
						m_labelToStatement[key] = count - 1;
						flag = false;
					}
					
					break;
				}
			}
		
		}
		/*cout << "----------------------------" << endl;
		cout << "My map details " << endl;
		for (map<string, int>::iterator it = m_labelToStatement.begin(); it != m_labelToStatement.end(); ++it)
		{
			cout << it->first << " => " << it->second << '\n';
		}

		cout << "My vector details " << endl;
		for (vector<string>::iterator it = m_statements.begin(); it != m_statements.end(); ++it)
		{
			cout << *(it) << endl;
		}

		cout << "----------------------------" << endl;*/
		
			
	}
}

/**/
/*
int Statement::GetStatement()

NAME

		Statement::GetStatement - Returns a statement from the vector.

SYNOPSIS


			string Statement::GetStatement(int a_statementNum);


			a_statementNum			--> the index value in the vector m_statements whose corresponding statement is 
										being referenced.


DESCRIPTION

		This functions goes to the vector m_statements and returns the statement stored at the referenced index.


RETURNS

		It returns the statement at the requested position in the vector m_statements.
AUTHOR

		Nitesh Parajuli

DATE

		9:54pm 5/15/2019

*/
/**/

string Statement::GetStatement(int a_statementNum)
{
	return m_statements[a_statementNum];
}

/**/
/*
int Statement::GetLabelLocation()

NAME

		Statement::GetLabelLocation - Returns the index position of a label.

SYNOPSIS


			int Statement::GetLabelLocation(string a_string);


			a_string			--> the name of the label


DESCRIPTION

		This functions goes to the map that has the label and index in the vector to the statement that's associated 
		with the label. If a label doesn't exist, an error is thrown.


RETURNS

		The position of the statement, which is linked to the label, in the vector.
AUTHOR

		Nitesh Parajuli

DATE

		10:02pm 5/15/2019

*/
/**/

int Statement::GetLabelLocation(string a_string)
{
	map<string, int>::iterator it;
	it = m_labelToStatement.find(a_string);
	if (it != m_labelToStatement.end())
	{
		return it->second;
	}
	else
	{
		cerr << "Label " << a_string << " was not found" << endl;
		exit(0);
	}

}
