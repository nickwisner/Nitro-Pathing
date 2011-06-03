#include "RobotCommand.h"

RobotCommand::RobotCommand(char cmd, int milisecs) : m_code(cmd), m_milisecs(milisecs)
{ }

RobotCommand::~RobotCommand(){

}

char RobotCommand::getCode(){

	return m_code;
}

int RobotCommand::getMilisecs(){

	return m_milisecs;
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
		this->m_milisecs = cmd.m_milisecs;
	}

	return *this;
}