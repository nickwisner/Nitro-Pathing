///////////////////////////////////////////////////////////
//  RobotCommand.h
//  Implementation of the Class RobotCommand
//  Generated by Enterprise Architect
//  Created on:      17-Apr-2011 5:15:04 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#ifndef ROBOTCOMMAND_H
#define ROBOTCOMMAND_H

#include <string>
using std::string;

class RobotCommand {

public:
	RobotCommand(char cmd, int cycles);
	RobotCommand & operator=( const RobotCommand & cmd );
	RobotCommand( const RobotCommand & cmd );
	~RobotCommand();

	char getCode();
	int getCycles();

private:
	char m_code;
	int m_cycles;	

};

#endif