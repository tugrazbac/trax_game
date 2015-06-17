// WhoamiCommand.cpp
//
// Group: Group 11591, study assistant Thomas Neff
//
// Authors: Benjamin Franz Herbert Rauch 1431077
// Peter Lorenz 1114658
// Rene Hasenburger 1432147
//------------------------------------------------------------------------------
//

#include "WhoamiCommand.h"
#include "Game.h"
#include "Exceptions.h"
#include <iostream>


//------------------------------------------------------------------------------
WhoamiCommand::WhoamiCommand() : Command("whoami")
{
}

//------------------------------------------------------------------------------
WhoamiCommand::~WhoamiCommand() 
{
}

    
//------------------------------------------------------------------------------
int WhoamiCommand::execute(Game &board, std::vector<std::string> &params)
{
  std::cout << TraxException::MESSAGES[TraxException::TEAM_NAME] << std::endl;
  return 0;
}

//------------------------------------------------------------------------------
unsigned int WhoamiCommand::getParamCnt()
{
  return 0;
}
