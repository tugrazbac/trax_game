
#include "DelLast.h"
#include "Command.h"
#include "Game.h"
#include "Position.h"
#include "Tile.h"

DelLast::DelLast() : Command("delete")
{
  
}

DelLast::~DelLast() 
{
}

int DelLast::execute(Game &board, std::vector<std::string> &params)
{
  Position pos;
//  Tile *type_tile = new Tile();
  board.deleteTileAtPositon(pos, nullptr);
  
  
  return 0;
}

unsigned int DelLast::getParamCnt()
{
  return 1;
}