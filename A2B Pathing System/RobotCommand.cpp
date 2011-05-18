#include "RobotCommand.h"

RobotCommand::RobotCommand():m_code(0), m_cycles(0)
{	}
RobotCommand::RobotCommand(char cmd, int cycles) : m_code(cmd), m_cycles(cycles)
{ }

RobotCommand::~RobotCommand(){

}

char RobotCommand::getCode(){

	return m_code;
}

int RobotCommand::getCycles(){

	return m_cycles;
}
RobotCommand::RobotCommand( const RobotCommand & cmd )
{
	*this = cmd;
}

RobotCommand & RobotCommand::operator=( const RobotCommand & cmd )
{
	if(this != &cmd)
	{
		this->m_code = cmd.m_code;
		this->m_cycles = cmd.m_cycles;
	}

	return *this;
}