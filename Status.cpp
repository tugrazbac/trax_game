/* 
 * File:   Status.cpp
 * Author: jester
 * 
 * Created on June 9, 2015, 12:51 PM
 */

#include "Status.h"
#include "iostream"
#include "Game.h"

Status::Status() : Command("status")
{
}

Status::~Status() 
{
}

int Status::execute(Game &board, std::vector<std::string> &params)
{
  std::cout << "Status begins" << std::endl;
  
  std::cout << "White: " << board.getWhite() << std::endl;
  std::cout << "Red:   " << board.getRed() << std::endl;
  
  return 0;
}

unsigned int Status::getParamCnt()
{
  return 0;
}

