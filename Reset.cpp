/* 
 * File:   Reset.cpp
 * Author: jester
 * 
 * Created on June 9, 2015, 12:42 PM
 */

#include "Reset.h"
#include "Position.h"
#include <iostream>
#include <vector>
#include "WriteCommand.h"

Reset::Reset() : Command("reset")
{
}

Reset::~Reset() 
{
}
  
int Reset::execute(Game &board, std::vector<std::string> &params)
{
  std::vector<std::vector<Tile *>> empty_board = board.getBoard();
  empty_board.clear();
  board.overwriteBoard(empty_board);
  
  board.setMinMaxX(0);
  board.setMinMaxY(0);
  board.setStartTile(nullptr);
  
  board.togglePlayer();
  
//  WriteCommand *a = new WriteCommand();
//  
//  
//  a->execute(board.getBoard(), params[0]);
//  board.setWriteFile("binar");
  
  
  return 0;
}

unsigned int Reset::getParamCnt()
{
  return 0;
}
