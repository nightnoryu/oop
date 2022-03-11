#pragma once

#include "CCalculator.h"
#include <functional>
#include <iostream>
#include <sstream>

class CCalculatorControl
{
public:
	CCalculatorControl(std::istream& input, std::ostream& output, CCalculator& calculator);
	void StartControl();

private:
	const std::string PROMPT = "$ ";

	enum class ExpressionType
	{
		IDLE,
		HELP,
		EXIT,
		CREATE_VARIABLE,
		ASSIGN_VARIABLE,
		CREATE_FUNCTION,
		PRINT_IDENTIFIER,
		PRINT_VARIABLES,
		PRINT_FUNCTIONS,
	};

	struct Expression
	{
		ExpressionType type;
		std::string arguments;
	};

	using ExpressionHandler = std::function<void(const std::string& argument)>;

	Expression ReadExpression();
	static ExpressionType ParseExpressionType(const std::string& expression);
	ExpressionHandler GetHandlerForExpression(ExpressionType expression);

	void PrintHelp();
	void CreateVariable(const std::string& arguments);
	void AssignVariable(const std::string& arguments);
	void CreateFunction(const std::string& arguments);
	void PrintIdentifier(const std::string& arguments);
	void PrintVariables();
	void PrintFunctions();

	std::istream& m_input;
	std::ostream& m_output;
	CCalculator& m_calculator;
};