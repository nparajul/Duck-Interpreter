/**/
/*
NAME

		DuckInterpreter.h - container class for the duck interpreter.


DESCRIPTION

		This class records the program and its labs. It runs the program through functionality like Parse next statement,
		which return the element as a string and indicate its data type, Evaluate Statement, which evalauates the type
		of statement and execute it.


AUTHOR

		Nitesh Parajuli

DATE

		11:32pm 5/15/2019

*/
/**/

#pragma once
#include "Statement.h"
#include "SymbolTable.h"
class DuckInterpreter
{
public:

/**/
/*
DuckInterpreter::RecordStatements()

NAME

		DuckInterpreter::RecordStatements - Records the statements that are in the specified file.

SYNOPSIS

		void DuckInterpreter::RecordStatements(string a_fileName);

			a_fileName       --> the name of the file that contains duck language program
			

DESCRIPTION

		This function will open the file that has the duck language program. The filename is passed as a string.
		The function simply records the each statement of the duck program in m_statements vector. 

RETURNS

		It's a void function. It does not return anything.
AUTHOR

		Nitesh Parajuli

DATE

		8:12pm 5/15/2019

*/
/**/
	 
	void RecordStatements(string a_fileName)
	{
		m_statements.RecordStatements(a_fileName);
	}
	
	void RunInterpreter();

private:

	// The statement object that holds the recorded statements.
	Statement m_statements;

	// The sysmbol table object that holds all the variable names and their values.
	SymbolTable m_symbolTable;

	// Stacks for the operators and numbers.  These will be used in evaluating statements.
	vector<char> m_operatorStack;
	vector<double> m_numberStack;


	enum class StatementType
	{
		ArithmeticStat,
		IfStat,
		ReadStat,
		PrintStat,
		LoopStat,
		StopStat,
		EndStat,
		gotoStat,
	};
	
/**/
/*
StatementType DuckInterpreter::GetStatementStype()

NAME

		DuckInterpreter::RecordStatements - Determines the type of the statement

SYNOPSIS

		StatementType DuckInterpreter::GetStatementStype(const string &a_string);

			a_string       --> Records the statement whose type is being determined.


DESCRIPTION

		This function will check the first part of the statement and determinrd what type of statement.
		It checks the first few characters of the string in order to do so.

RETURNS

		Returns an object of class StatementType
AUTHOR

		Nitesh Parajuli

DATE

		8:38pm 5/15/2019

*/
/**/
	StatementType GetStatementStype(const string &a_string)
	{
		string type;
		int i = 0;
				
		for (i = 0; !(isalpha(a_string[i])); i++);

		for (i ; (isalpha(a_string[i])); i++)
		{
			type += a_string[i];
		}
			
		
		if (type == "read")
		{
			return StatementType::ReadStat;
		}
		else if (type == "goto")
		{
			return StatementType::gotoStat;
		}
		else if (type == "if")
		{
			return StatementType::IfStat;
		}
		else if (type == "print")
		{
			return StatementType::PrintStat;
		}
		else if (type == "stop")
		{
			return StatementType::StopStat;
		}
		else if (type == "end")
		{
			return StatementType::EndStat;
		}
		else
		{
			return StatementType::ArithmeticStat;
		}
		
	}

	enum class ElementType
	{
		StringType,
		NumberType,
	};

	
	int ExecuteStatement(string a_statement, int a_StatementLoc);

	int ParseNextElement(const string &a_statement, int a_nextPos, string &a_stringValue, double &numValue);
	

	int FindPrecedence(string op);
	
	void EvaluateArithmentStatment( const string &a_statement );

	double EvaluateArithmenticExpression(const string &a_statement, int a_nextPos);
	
	double computeOperation(double exp1, double exp2, char op);
	
	int EvaluateIfStatement(string a_statement, int a_nextStatement);
	
	void EvaluatePrintStatement(string a_statement);
	
	void EvaluateReadStatement(string a_statement);
	
	int EvaluateGoToStatement(string a_statement);
};

