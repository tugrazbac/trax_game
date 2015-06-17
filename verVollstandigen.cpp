/* 
 * File:   verVollstandigen.cpp
 * Author: jester
 * 
 * Created on June 7, 2015, 4:26 PM
 */

#include "verVollstandigen.h"
#include "Game.h"
#include <iostream>
#include "AddTileCommand.h"
#include "Tile.h"
#include "Position.h"
#include "NextTile.h"
#include "string.h"

verVollstandigen::verVollstandigen() : Command("voll") 
{
}

verVollstandigen::~verVollstandigen() 
{
}

int verVollstandigen::execute(Game &board, std::vector<std::string> &params)
{
  std::vector<std::vector<Tile *>> empty_board = board.getBoard();
  std::vector<Position> buffer;
  
  if(board.getActivePlayer() != 2 )
  {
    std::cout << "toggle player!" << std::endl;
    board.togglePlayer();
  }
  if(board.getRemainingTiles() < 64)
  {
    empty_board.clear();
    board.overwriteBoard(empty_board);
  }
  bool first_tile = board.getStartTile() == nullptr;
  Position *pos = new Position(0,0);
  Tile *starttile = new Tile(Tile::Type::TYPE_CROSS, Color::COLOR_RED);
//  Tile *starttile = new Tile(Tile::Type::TYPE_CURVE_1, Color::COLOR_RED);
  Tile *tile1 = new Tile(Tile::Type::TYPE_CURVE_1, Color::COLOR_WHITE);
  Tile *tile2 = new Tile(Tile::Type::TYPE_CURVE_2, Color::COLOR_WHITE);
  Tile *tile3 = new Tile(Tile::Type::TYPE_CURVE_2, Color::COLOR_RED);
  if(first_tile)
  {
    std::cout << "Set Start tile: addtile (0,-1)" << std::endl;
    board.setTileAtPosition(*pos, starttile);
    board.setStartTile(starttile);
  }
  
  Position *pos1 = new Position(0,1);
  Position *pos2 = new Position(1,1);
  Position *pos3 = new Position(1,0);
//  
//  board.setTileAtPosition(*pos3, tile3);
//  board.setTileAtPosition(*pos1, tile2);
//  board.setTileAtPosition(*pos2, tile1);
    
//  board.checkForDraw();
//  board.checkForWin(*pos);
  
  std::vector<std::string> args;
  args.push_back("(0,-1)");
  args.push_back("+");
//  args.push_back("+");
//  args.push_back("\\");
  
  AddTileCommand cmd;
 
  cmd.execute(board, args);
  
  return 0;
}

unsigned int verVollstandigen::getParamCnt()
{
  return  0;
}