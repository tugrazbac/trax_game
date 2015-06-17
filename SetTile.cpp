/* 
 * File:   SetTile.cpp
 * Author: jester
 * 
 * Created on June 8, 2015, 6:34 PM
 */

#include "SetTile.h"
#include "Tile.h"
#include "Position.h"

#include "Exceptions.h"
#include <vector>

SetTile::SetTile() : Command("settile")
{
}

SetTile::~SetTile() 
{
}

int SetTile::execute(Game &board, std::vector<std::string> &params)
{
  Position pos;
  //check number of parameters and (if available) evaluate first parameter
  if (params.size() != 2 || !pos.parse(params.at(0)))
  {    
    throw TraxException(TraxException::INVALID_PARAMS);
  }
  
  //preserve old data in case of screw up
  std::vector<std::vector<Tile *> > game_board = board.getBoard();
  std::pair<Position, Position> min_max_save(
    Position(board.getMinX(), board.getMinY()),
    Position(board.getMaxX(), board.getMaxY()));
  std::vector<Position> buffer;
  buffer.push_back(pos);
  
  //evaluate second parameter
  Tile::Type tile_type;
  std::string tile_type_str = params.at(1);
  if (tile_type_str == "+")
    tile_type = Tile::TYPE_CROSS;
  else if (tile_type_str == "/")
    tile_type = Tile::TYPE_CURVE_1;
  else if (tile_type_str == "\\")
    tile_type = Tile::TYPE_CURVE_2;
  else
  {
    throw TraxException(TraxException::INVALID_PARAMS);
  }

  bool first_tile = board.getStartTile() == nullptr;
  //first tile must be at (0,0)
//  if (first_tile && (pos.getX() != 0 || pos.getY() != 0))
//  {
//    throw TraxException(TraxException::POSITION_MUST_BE_ZERO);
//  }

  //check if space is taken
  if (board.getTileAtPosition(pos) != nullptr)
  {
    throw TraxException(TraxException::FIELD_NOT_FREE);
  }
  
  Tile *tile_pointer;
  //handle first tile because further calculations are not related to it
  if (first_tile)
  {
    tile_pointer = new Tile(tile_type, Color::COLOR_RED);
    board.setStartTile(tile_pointer);
    board.setTileAtPosition(pos, tile_pointer);
    board.togglePlayer();
    return 1;
  }
  
  
  
//  //calculate top color
//  int top_color_integer;
//  switch (tile_type)
//  {
//    case Tile::TYPE_CROSS:
//      top_color_integer = colors_for_tile.getTop() |
//        Game::getInvertedColor(colors_for_tile.getRight()) |
//        colors_for_tile.getBottom() |
//        Game::getInvertedColor(colors_for_tile.getLeft());
//      break;
//    case Tile::TYPE_CURVE_1:
//      top_color_integer = colors_for_tile.getTop() |
//        Game::getInvertedColor(colors_for_tile.getRight()) |
//        Game::getInvertedColor(colors_for_tile.getBottom()) |
//        colors_for_tile.getLeft();
//      break;
//    case Tile::TYPE_CURVE_2:
//      top_color_integer = colors_for_tile.getTop() |
//        colors_for_tile.getRight() |
//        Game::getInvertedColor(colors_for_tile.getBottom()) |
//        Game::getInvertedColor(colors_for_tile.getLeft());
//      break;
//  }
//  
  tile_pointer = new Tile(tile_type, static_cast<Color>(1));
  board.setTileAtPosition(pos, tile_pointer);
  
  return 0;
}
unsigned int SetTile::getParamCnt()
{
  return 2;
}
