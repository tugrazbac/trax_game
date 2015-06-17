//------------------------------------------------------------------------------
// QuitCommand.cpp
//
// Group: Group 11591, study assistant Thomas Neff
//
// Authors: Benjamin Franz Herbert Rauch 1431077
// Peter Lorenz 1114658
// Rene Hasenburger 1432147
//------------------------------------------------------------------------------
//

#include "QuitCommand.h"
#include "Game.h"
#include "Exceptions.h"

#include <iostream>

//------------------------------------------------------------------------------
QuitCommand::QuitCommand() : Command("quit")
{
}

//------------------------------------------------------------------------------
QuitCommand::~QuitCommand()
{
}

//------------------------------------------------------------------------------
int QuitCommand::execute(Game &board, std::vector<std::string> &params)
{
  std::cout << TraxException::MESSAGES[TraxException::BYE] << std::endl;
  board.setRunning(false);
  return 0;
}

//------------------------------------------------------------------------------
unsigned int QuitCommand::getParamCnt()
{
  return 0;
}
