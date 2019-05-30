//implementation of DuckInterpreter.h


#include "stdafx.h"
#include "DuckInterpreter.h"

/**/
/*
DuckInterpreter::RunInterpreter()

NAME

		DuckInterpreter::RunInterpreter - Runs the interpreter on the recorded statements.

SYNOPSIS

		void DuckInterpreter::RunInterpreter();

			


DESCRIPTION

		This function runs the interpreter on the statements of the vector (i.e. lines of the file).

RETURNS

		It's a void function. It does not return anything.
AUTHOR

		Nitesh Parajuli

DATE

		8:12pm 5/15/2019

*/
/**/

void DuckInterpreter::RunInterpreter()
{
	int nextStatement = 0;

	while (true)
	{
		string statement = m_statements.GetStatement(nextStatement);
		
		nextStatement = ExecuteStatement(statement, nextStatement);
		
	}
	
}

/**/
/*
DuckInterpreter::ExecuteStatement()

NAME

		DuckInterpreter::ExecuteStatement - Executes the statement that was sent after determining the type.

SYNOPSIS

		int DuckInterpreter::ExecuteStatement(string a_statement, int a_nextStatement);

			a_statement       --> The string that holds the statement to be executed.
			a_nextStatement   --> The position of the next statement that will get executed.


DESCRIPTION

		The function evaluates the statement. It consists of a switch that evaluate functions which evalutates the 
		statement of different types, through which we can get the position of next statement that should be evaluated.
		Throws an error if the type is undefined.

RETURNS

		Returns the position (vector's index) of the statement that will next be executed.
AUTHOR

		Nitesh Parajuli

DATE

		8:46pm 5/15/2019

*/
/**/

int DuckInterpreter::ExecuteStatement(string a_statement, int a_nextStatement)
{
	// Clear the stacks
	m_numberStack.clear();
	m_operatorStack.clear();
	int nextElement = 0;

	// Get the first syntactic element of the statement.  
	StatementType type = GetStatementStype(a_statement );
	
	// Based on the type, execute the remainder of the statement.
	switch (type)
	{
	case StatementType::ArithmeticStat:
		EvaluateArithmentStatment(a_statement);
		return a_nextStatement + 1;
	case StatementType::IfStat:
		return EvaluateIfStatement(a_statement, a_nextStatement);
	case StatementType::StopStat:
		exit(0);
		return a_nextStatement + 1;
	case StatementType::EndStat:
		exit(0);
	case StatementType::PrintStat:
		EvaluatePrintStatement(a_statement);
		return a_nextStatement + 1;
	case StatementType::ReadStat:
		EvaluateReadStatement(a_statement);
		return a_nextStatement + 1;
	case StatementType::gotoStat:
		return EvaluateGoToStatement(a_statement);

	default:
		cerr << "BUGBUG - program terminate: invalid return value from GetStatementStype for the statement: " << a_statement << endl;
		exit(1);
	}
}

/**/
/*
DuckInterpreter::ParseNextElement()

NAME

		DuckInterpreter::ParseNextElement - Returns the next element in the statement. 
											Returns the next location to be accessed.

SYNOPSIS

		int DuckInterpreter::ParseNextElement(const string &a_statement, int a_nextPos, string &a_stringValue, double &numValue);


			a_statement       --> The string that holds the statement to be executed.
			a_nextPos		  --> The initial position of the next element in the statement.
			a_stringValue	  --> The name of the variable, if it's a variable.
			numValue		  --> The number that was parsed, if it's not a variable.


DESCRIPTION

		This function finds the next element in a statement. It goes through each character/(s) of the string and 
		checks if the value is an alphabet, number, or other chars and stores the string value of the variable, if it's
		a variable and the number itself, if it's not a variable. Also, it calculates the initial position of the next 
		element.


RETURNS

		Returns the first position of the next element.
AUTHOR

		Nitesh Parajuli

DATE

		8:47pm 5/15/2019

*/
/**/

int DuckInterpreter::ParseNextElement(const string &a_statement, int a_nextPos, string &a_stringValue, double &numValue)
{
	bool isstring = false;
	bool isnum = true;
	bool done = false;
	bool bracket = true;

	int i = a_nextPos;

	for (i; isspace(a_statement[i]); i++);

	while (isalnum(a_statement[i]) || a_statement[i] == '.' || a_statement[i] == '_')
	{
		a_stringValue += a_statement[i];
		i++;
		done = true;
		bracket = false;
	}

	while (done == false && (a_statement[i] == '=' || a_statement[i] == '+' || a_statement[i] == '-' || a_statement[i] == '*' || a_statement[i] == '/' || a_statement[i] == ';' || a_statement[i] == '!' || a_statement[i] == '>' || a_statement[i] == '<'))
	{

		a_stringValue += a_statement[i];
		i++;
		bracket = false;

	}

	while (bracket == true && (a_statement[i] == '(' || a_statement[i] == ')' || a_statement[i] == ','))
	{
		a_stringValue += a_statement[i];
		i++;
	}

	char char_array[50];
	strcpy(char_array, a_stringValue.c_str());

	for (int j = 0; j < a_stringValue.length(); j++)
	{
		if ((char_array[j] < 48 || char_array[j]>57) && char_array[j] != '.')
		{
			isstring = true;
			isnum = false;
			break;
		}

	}

	if (isnum == true)
	{
		stringstream num(a_stringValue);
		num >> numValue;
		a_stringValue.clear();
	}

	return i;

}

/**/
/*
DuckInterpreter::FindPrecedence()

NAME

		DuckInterpreter::FindPrecedence -	Returns the precendence level of the operator.

SYNOPSIS

		int DuckInterpreter::FindPrecedence(string op);


			op		--> the operator whose precedence is being determined.


DESCRIPTION

		This function returns the level of precedence of an operator. The operator is determined using the parseNextElement
		function.


RETURNS

		Returns the level of precedence of the operator.
AUTHOR

		Nitesh Parajuli

DATE

		8:51pm 5/15/2019

*/
/**/

int DuckInterpreter::FindPrecedence(string op)
{
	if (op == "(" || op == ")")
	{
		return 4;
	}
	if (op == "*" || op == "/")
	{
		return 3;
	}
	if (op == "+" || op == "-")
	{
		return 2;
	}
	if (op == "<" || op == ">")
	{
		return 1;
	}
	if (op == ";")
	{
		return 0;
	}
}



/**/
/*
void DuckInterpreter::EvaluateArithmentStatment()

NAME

		DuckInterpreter::EvaluateArithmentStatment - Evaluates an arithmetic statement.

SYNOPSIS

		void DuckInterpreter::EvaluateArithmentStatment(const string &a_statement);


			a_statement		--> the arithmetic statement that's being evaluated.


DESCRIPTION

		This function breaks the arithmetic into 3 parts: the variable that holds the value, the "=" operator, and
		the assigned value or the expression whose value is stored. It also stores the value and the variable in the 
		m_symboltable map.


RETURNS

		Nothing. It's a void function.
AUTHOR

		Nitesh Parajuli

DATE

		8:59pm 5/15/2019

*/
/**/

void DuckInterpreter::EvaluateArithmentStatment(const string &a_statement)
{
	// Record the variable that we will be assignning a value.
	int nextPos = 0;
	string resultVariable;
	double placeHolder;
	nextPos = ParseNextElement(a_statement, nextPos, resultVariable, placeHolder);
	assert(!resultVariable.empty());
	

	string assigmentOp;
	nextPos = ParseNextElement(a_statement, nextPos, assigmentOp, placeHolder);
	assert(assigmentOp == "=");
	
	double result = EvaluateArithmenticExpression(a_statement, nextPos);

	// Record the result.
	m_symbolTable.RecordVariableValue(resultVariable, result);
	

	//cout << "Symbol table Map: " << endl;
	//m_symbolTable.printMap();
	

}

/**/
/*
void DuckInterpreter::EvaluateArithmenticExpression()

NAME

		DuckInterpreter::EvaluateArithmenticExpression - Evaluate an arithmetic expression.  Return the value.  
														 The variable a_nextPos is index to the next.

SYNOPSIS

		double DuckInterpreter::EvaluateArithmenticExpression(const string &a_statement, int a_nextPos)


			a_statement		--> the arithmetic statement that's being evaluated.
			a_nextPos		--> the starting position of the next element.


DESCRIPTION

		This function determines the value of the arithmetic expression and returns that value. It also finds the 
		initial position of the next elements. It uses two stack that hold variable value/numeric values, and operators.
		Throws an error if the variable referenced is not initialized.


RETURNS

		It returns the double value after computing the expression.
AUTHOR

		Nitesh Parajuli

DATE

		9:13pm 5/15/2019

*/
/**/

double DuckInterpreter::EvaluateArithmenticExpression(const string &a_statement, int a_nextPos)
{
	int count = 0;


	while (a_statement[a_nextPos] != ';')
	{
		string stringVal;
		double numVal;


		a_nextPos = ParseNextElement(a_statement, a_nextPos, stringVal, numVal);


		if (!stringVal.empty() && ((stringVal != "+") && (stringVal != "-") && (stringVal != "*") && (stringVal != "/") && (stringVal != ">") && (stringVal != "<") && (stringVal != "(") && (stringVal != ")") && (stringVal != ";")))
		{

			if (m_symbolTable.GetVariableValue(stringVal, numVal))
			{
				stringVal.clear();
			}
			else
			{
				cout << "Variable " << stringVal << " not found" << endl;
				exit(0);
			}
		}


		if ((stringVal.empty()))
		{
			m_numberStack.push_back(numVal);

		}
		else
		{
			for (int i = 0; i < stringVal.length(); i++)
			{
				if (!(isalnum(stringVal[i])))
				{
					if (count == 0)
					{
						m_operatorStack.push_back(stringVal[0]);
						count++;
						break;
					}
					else
					{

						string prev(1, m_operatorStack.back());
						string op(1, stringVal[0]);

						if (op == ";")
						{
							break;
						}
						else if (op == "(")
						{

							int j = a_nextPos;
							string newexpression;

							while (a_statement[j] != ')')
							{
								newexpression += a_statement[j];
								j++;
							}
							a_nextPos = j + 1;
							newexpression += ';';

							int next = 0;
							double my_result = EvaluateArithmenticExpression(newexpression, next);
							m_numberStack.push_back(my_result);
						}

						else if (FindPrecedence(prev) >= FindPrecedence(op))
						{
							double exp2 = m_numberStack.back();
							m_numberStack.pop_back();
							double exp1 = m_numberStack.back();
							m_numberStack.pop_back();
							char opr = m_operatorStack.back();
							m_operatorStack.pop_back();
							double result = computeOperation(exp1, exp2, opr);
							m_numberStack.push_back(result);
							m_operatorStack.push_back(stringVal[0]);
						}
						else
						{
							char opr = stringVal[0];
							stringVal.clear();
							a_nextPos = ParseNextElement(a_statement, a_nextPos, stringVal, numVal);
							double exp2 = m_numberStack.back();
							m_numberStack.pop_back();
							double result = computeOperation(exp2, numVal, opr);
							m_numberStack.push_back(result);
						}
						break;
					}

				}
			}

		}

	}

	if (m_operatorStack.empty())
	{
		return m_numberStack.back();
	}

	double exp2 = m_numberStack.back();
	m_numberStack.pop_back();
	double exp1 = m_numberStack.back();
	m_numberStack.pop_back();
	char opr = m_operatorStack.back();
	m_operatorStack.pop_back();
	double result = computeOperation(exp1, exp2, opr);
	return result;

}

/**/
/*
double DuckInterpreter::computeOperation()

NAME

		DuckInterpreter::computeOperation - Evaluate an arithmetic expression.  Return the value.
											The variable a_nextPos is index to the next.

SYNOPSIS

		double DuckInterpreter::computeOperation(double exp1, double exp2, char op);


			exp1			--> the value of the first expression.
			exp1			--> the value of the second expression.
			op				--> the operator 


DESCRIPTION

		This function gets two value and an operator. It computes the operation based on those information.


RETURNS

		It returns the result of the operation
AUTHOR

		Nitesh Parajuli

DATE

		9:18pm 5/15/2019

*/
/**/

double DuckInterpreter::computeOperation(double exp1, double exp2, char op)
{
	switch (op)
	{
	case '+':
		exp2 = exp1 + exp2;
		break;
	case '-':
		exp2 = exp1 - exp2;
		break;
	case '*':
		exp2 = exp1 * exp2;
		break;
	case '/':
		exp2 = exp1 / exp2;
		break;
	case '>':
		exp2 = exp1 > exp2;
		break;
	case '<':
		exp2 = exp1 < exp2;
		break;
	default:
		cout << "Not yet addressed";
	}

	return exp2;
}

/**/
/*
int DuckInterpreter::EvaluateIfStatement()

NAME

		DuckInterpreter::EvaluateIfStatement - Evaluates an if statement to determine if the goto should be executed.
											

SYNOPSIS

		int DuckInterpreter::EvaluateIfStatement(string a_statement, int a_nextStatement)


			a_statement					--> the if statement that is being executed.
			a_nextStatement				--> the value of the starting position of the next element.
			


DESCRIPTION

		This function evalutes an if statement. It checks the condition of the if part and sends that to evaluate
		arithmetic, gets a value and if it's true, it goes to a specific label. If not, it simply goes to the next statement.


RETURNS

		It returns the position of the label, if true and the position of the nextStatement if false.
AUTHOR

		Nitesh Parajuli

DATE

		9:23pm 5/15/2019

*/
/**/

int DuckInterpreter::EvaluateIfStatement(string a_statement, int a_nextStatement)
{
	
	// Get past of the "if" in the if statement.
	int nextPos = 0;
	string resultString;
	string tosend;
	double placeHolder;
	nextPos = ParseNextElement(a_statement, nextPos, resultString, placeHolder);
	assert(resultString == "if" );

	// Searching from the end, fine the goto statement and replace it by ";"  Record
	// the label in the goto.
	int i = nextPos;
	while (a_statement[i] != ';')
	{
		i++;
	}
	i--;
	for (i; isspace(a_statement[i]); i--);

	string label;

	while (isalnum(a_statement[i]) || a_statement[i] == '.'|| a_statement[i] == '_')
	{
		label += a_statement[i];
		i--;
	}

	reverse(label.begin(), label.end());
	for (i; isspace(a_statement[i]); i--);

	while (isalnum(a_statement[i]) || a_statement[i] == '.'||a_statement[i] == '_')
	{
		i--;
	}
	for (i; isspace(a_statement[i]); i--);
	
	a_statement.insert(i,";");
		
	int labelLocation = m_statements.GetLabelLocation(label);

	// Verify that the label from the goto exists.

	// Evaluate the emaining arithmentic expression. 
	for (i = nextPos; isspace(a_statement[i]); i++);
	if (a_statement[i] == '(')
	{
		i++;
	}
	
	while (a_statement[i] != ')')
	{
		tosend += a_statement[i];
		i++;
	}
	
	tosend.erase(remove(tosend.begin(), tosend.end(), ' '), tosend.end());
	
	nextPos = 0;
	double result = EvaluateArithmenticExpression(tosend, nextPos);
	
	// If the result is zero, don't execute the goto.
	if (result == 0)
	{
		return a_nextStatement + 1;
	}
	return labelLocation;

}

/**/
/*
DuckInterpreter::EvaluatePrintStatement()

NAME

		DuckInterpreter::EvaluatePrintStatement - Evaluates a print statement and prints the output string and values.


SYNOPSIS

		void DuckInterpreter::EvaluatePrintStatement(string a_statement);


			a_statement					--> the print statement that is being executed.
			

DESCRIPTION

		This function evalutes a print statement. It prints out the string within  " " and also the variable values.


RETURNS

		Nothing. It's a void function.
AUTHOR

		Nitesh Parajuli

DATE

		9:31pm 5/15/2019

*/
/**/
void DuckInterpreter::EvaluatePrintStatement(string a_statement)
{
	int a_nextpos = 0;
	string stringVal;
	double numVal;
	bool isquote = false;

	int i = ParseNextElement(a_statement,a_nextpos,stringVal,numVal);
	//cout << "After removing print: " << i <<" and stringVal:  "<<stringVal<<endl;
	stringVal.clear();

	while (a_statement[i] != ';')
	{
		string tobeprinted;
		//int i = 0;
		for (i; isspace(a_statement[i]); i++);
		
		if (a_statement[i] == '"')
		{
			i++;
			for (i; a_statement[i] != '"'; i++)
			{
				tobeprinted += a_statement[i];
				isquote = true;
			}
			
			//for (i; a_statement[i] != '"'; i++);
			i++;
					
		}
		

		if (tobeprinted.length() > 0)
		{
			cout << tobeprinted;
		}
		
		for (i; isspace(a_statement[i]); i++);
		a_nextpos = i;
		
		if (isquote == false ||a_statement[i] == ',')
		{
			if (a_statement[i] == ',')
			{
				i++;
			}
			for (i; isspace(a_statement[i]); i++);

			if (a_statement[i] != '"')
			{
				a_nextpos = ParseNextElement(a_statement, i, stringVal, numVal);
				if (m_symbolTable.GetVariableValue(stringVal, numVal))
				{
					stringVal.clear();
				}
				else
				{
					cout << "Value of " << stringVal << " not defined" << endl;
					exit(1);
				}
				cout << numVal << " ";
				i = a_nextpos;
			}
			else
			{
				continue;
			}
			
			
		}
		
	
	}
	cout << endl;
	
}

/**/
/*
int DuckInterpreter::EvaluateGoToStatement()

NAME

		DuckInterpreter::EvaluateGoToStatement - Evaluates a goto statement and finds the index that has to be executed next.

SYNOPSIS

		int DuckInterpreter::EvaluateGoToStatement(string a_statement);


			a_statement					--> the goto statement that is being executed.


DESCRIPTION

		This function evalutes a goto statement. It first checks if the label exists and if it does, it returns the 
		position of the label. If the label doesn't exist, an error message is displayed.


RETURNS

		The position of the statement (in the vector) that is associated with the label.
AUTHOR

		Nitesh Parajuli

DATE

		9:39pm 5/15/2019

*/
/**/

int DuckInterpreter::EvaluateGoToStatement(string a_statement) 
{

	int a_nextpos = 0;
	string stringVal;
	double numVal;
	int userInput;
	bool isquote = false;

	int i = ParseNextElement(a_statement, a_nextpos, stringVal, numVal);
	stringVal.clear();
	for (i; isspace(a_statement[i]); i++);
	
	while (a_statement[i] != ';')
	{		
		stringVal += a_statement[i];
		i++;
	}

	int retVal= m_statements.GetLabelLocation(stringVal);
	
	return retVal;

}

/**/
/*
int DuckInterpreter::EvaluateReadStatement()

NAME

		DuckInterpreter::EvaluateReadStatement - Evaluates a read statement. It stores the inputted values in the map.

SYNOPSIS

		void DuckInterpreter::EvaluateReadStatement(string a_statement);


			a_statement					--> the read statement that is being executed.


DESCRIPTION

		This function evalutes a read statement. It prints out the prompt, takes user input and stores the variable name
		and value as a key pair in the symbolTable map.


RETURNS

		Nothing. It's a void function.
AUTHOR

		Nitesh Parajuli

DATE

		9:43pm 5/15/2019

*/
/**/

void DuckInterpreter::EvaluateReadStatement(string a_statement)
{
	int a_nextpos = 0;
	string stringVal;
	double numVal;
	double userInput;
	bool isquote = false;

	int i = ParseNextElement(a_statement, a_nextpos, stringVal, numVal);
	stringVal.clear();
	while (a_statement[i] != ';')
	{
		string tobeprinted;
		for (i; isspace(a_statement[i]); i++);

		if (a_statement[i] == '"')
		{
			i++;
			for (i; a_statement[i] != '"'; i++)
			{
				tobeprinted += a_statement[i];
				isquote = true;
			}

			i++;

		}


		if (tobeprinted.length() > 0)
		{
			cout << tobeprinted;
		}


		for (i; isspace(a_statement[i]); i++);
		a_nextpos = i;
		if (isquote == false || a_statement[i] == ',')
		{
			if (a_statement[i] == ',')
			{
				i++;
			}

			for (i; isspace(a_statement[i]); i++);

			if (a_statement[i] != '"')
			{
				a_nextpos = ParseNextElement(a_statement, i, stringVal, numVal);
				cin >> userInput;
				m_symbolTable.RecordVariableValue(stringVal, userInput);

				i = a_nextpos;
			}
		}
	}
	
}