#pragma once

#include "CCar.h"
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

const std::string PROMPT = "> ";

class CCarControl
{
public:
	CCarControl(std::istream& input, std::ostream& output, CCar& car);
	void StartControl();

private:
	enum class CommandType
	{
		IDLE,
		HELP,
		INFO,
		EXIT,
		ENGINE_ON,
		ENGINE_OFF,
		SET_GEAR,
		SET_SPEED,
	};

	struct Command
	{
		CommandType type;
		int argument;
	};

	using CommandHandler = std::function<void(int argument)>;

	CCarControl::Command ReadCommand();
	static CCarControl::CommandType ParseCommandType(const std::string& command);
	CommandHandler GetHandlerForCommand(CommandType command);

	void PrintHelp();
	void PrintInfo();
	void EngineOn();
	void EngineOff();
	void SetGear(int gear);
	void SetSpeed(int speed);

	static std::string DirectionToString(CCar::Direction direction);

	std::istream& m_input;
	std::ostream& m_output;
	CCar& m_car;
};
