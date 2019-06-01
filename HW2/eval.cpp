#include <stack>
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

int evaluate(string infix, string& postfix, bool& result);
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.

bool isValidOperand(string infix, int pos); // functions to test the validity of infix string
bool isValidOperator(string infix, int pos);
bool isValidNot(string infix, int pos);
bool isValidLeft(string infix, int pos);
bool isValidRight(string infix, int pos);


int evaluate(string infix, string& postfix, bool& result)
{
	string candidate;
	stack<char> converter;
	for (int i = 0; infix[i] != '\0'; i++)
	{
		switch (infix[i])
		{
		case 'T':
		case 'F':
			if (!isValidOperand(infix,i))
				return 1;
			candidate += infix[i];
			break;
		case '(':
			if (!isValidLeft(infix,i))
				return 1;
			converter.push(infix[i]);
			break;
		case ')':
			if (!isValidRight(infix, i))
				return 1;
			if (converter.empty())
			{
				return 1;
			}
			while (converter.top() != '(')
			{
				candidate += converter.top();
				converter.pop();
				if (converter.empty())
				{
					return 1;
				}
			}
			converter.pop();
			break;
		case '^':
			if (!isValidOperator(infix,i))
				return 1;
			while (!converter.empty() && converter.top() != '(')
			{
				candidate += converter.top();
				converter.pop();
			}
			converter.push(infix[i]);
			break;
		case '!':
			if (!isValidNot(infix, i))
			{
				return 1;
			}
				while (!converter.empty() && converter.top() != '(' && converter.top() != '^' && converter.top() != '&' && converter.top() != '!') // evaluate precedence // only pop when the top is not operand
				{
					candidate += converter.top();
					converter.pop();
				}
			converter.push(infix[i]);
			break;
		case '&':
			if (!isValidOperator(infix,i))
				return 1;
			while (!converter.empty() && converter.top() != '(' && converter.top() != '^') // evaluate precedence
			{
				candidate += converter.top();
				converter.pop();
			}
			converter.push(infix[i]);
			break;
		case ' ':
			break;
		default:
			return 1;
			break;
		}
	}
	while (!converter.empty())
	{
		if (converter.top() == '(')// if the brackets are balanced, no left bracket will be left
		{
			return 1;
		}
		candidate += converter.top();
		converter.pop();
	}
	postfix = candidate;
	if (postfix == "") // empty string is invalid
		return 1;
	
	stack<char> evaluator;
	for (int i = 0; postfix[i] != '\0'; i++)
	{
		char operand2, operand1, operand;
		switch (postfix[i])
		{
		case 'T':
		case 'F':
			evaluator.push(postfix[i]);
			break;
		case '&':
			if (evaluator.empty())
				return 1;
			operand2 = evaluator.top();
			evaluator.pop();
			if (evaluator.empty())
			{
				return 1;
			}
			operand1 = evaluator.top();
			evaluator.pop();
			if (operand2 == 'T' && operand2 == operand1)
			{
				evaluator.push('T');
			}
			else
			{
				evaluator.push('F');
			}
			break;
		case '^':
			if (evaluator.empty())
				return 1;
			operand2 = evaluator.top();
			evaluator.pop();
			if (evaluator.empty())
			{
				return 1;
			}
			operand1 = evaluator.top();
			evaluator.pop();
			if (operand2 == operand1)
			{
				evaluator.push('F');
			}
			else
			{
				evaluator.push('T');
			}
			break;
		case '!':
			if (evaluator.empty())
				return 1;
			operand = evaluator.top();
			evaluator.pop();
			if (operand == 'T')
			{
				evaluator.push('F');
			}
			else if (operand == 'F')
			{
				evaluator.push('T');
			}
			break;
		default:
			return 1;
			break;
		}
	}
	char hold = evaluator.top();
	evaluator.pop();
	if (!evaluator.empty())
	{
		return 1;
	}
	if (hold == 'T')
	{
		result = true;
	}
	else
	{
		result = false;
	}
	return 0;
}

bool isValidOperand(string infix, int pos)
{
	if (pos != 0)
	{
		if (infix[pos - 1] != '!' && infix[pos - 1] != '&' && infix[pos - 1] != '^' && infix[pos - 1] != '(' && infix[pos - 1] != ' ')
			return false;
	}
	if (infix[pos + 1] != '\0')
	{
		if (infix[pos + 1] != '&' && infix[pos + 1] != '^' && infix[pos + 1] != ')' && infix[pos + 1] != ' ')
			return false;
	}
	return true;
}

bool isValidOperator(string infix, int pos)
{
	if (pos == 0 || infix[pos + 1] == '\0')
		return false;
	if (infix[pos - 1] != 'T' && infix[pos - 1] != 'F' && infix[pos - 1] != ')' &&  infix[pos - 1] != ' ')
		return false;
	if (infix[pos + 1] != 'T' && infix[pos + 1] != 'F' && infix[pos + 1] != '(' && infix[pos + 1] != '!' && infix[pos + 1] != ' ')
		return false;
	return true;

}

bool isValidNot(string infix, int pos)
{
	if (pos != 0)
	{
		if (infix[pos - 1] != '!' && infix[pos - 1] != '&' && infix[pos - 1] != '^' && infix[pos - 1] != '(' && infix[pos - 1] != ' ')
			return false;
	}
	if (infix[pos + 1] == '\0')
		return false;
	if (infix[pos + 1] != 'T' && infix[pos + 1] != 'F' && infix[pos + 1] != '!' && infix[pos + 1] != '(' && infix[pos + 1] != ' ')
		return false;
	return true;
}

bool isValidLeft(string infix, int pos)
{
	if (pos != 0)
	{
		if (infix[pos - 1] != '!' && infix[pos - 1] != '&' && infix[pos - 1] != '^'&& infix[pos - 1] != '('  && infix[pos - 1] != ' ')
			return false;
	}
	if (infix[pos + 1] == '\0')
		return false;
	if (infix[pos + 1] != 'T' && infix[pos + 1] != 'F' && infix[pos + 1] != '!'&& infix[pos + 1] != '(' && infix[pos + 1] != ' ')
		return false;
	return true;
}
bool isValidRight(string infix, int pos)
{
	if (pos == 0)
		return false;
	if (pos != 0)
	{
		if (infix[pos - 1] != 'T' && infix[pos - 1] != 'F' && infix[pos - 1] != ')' && infix[pos - 1] != ' ')
			return false;
	}
	if (infix[pos + 1] != '\0')
	{
		if (infix[pos + 1] != '^' && infix[pos + 1] != '&' && infix[pos + 1] != ')' && infix[pos + 1] != ' ')
			return false;
	}
	return true;
}










