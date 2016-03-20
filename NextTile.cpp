//------------------------------------------------------------------------------
// NextTile.cpp
//
// Group: Group 11591, study assistant Thomas Neff
//
// Authors: Benjamin Franz Herbert Rauch 
// Peter Lorenz 
// Rene Hasenburger 
//------------------------------------------------------------------------------
//

#include "NextTile.h"
#include "Game.h"
#include "Tile.h"

//------------------------------------------------------------------------------
NextTile::~NextTile()
{
}
   

//------------------------------------------------------------------------------
NextTile::NextTile(Game &board, Color player, Position laid_tile)
{
  Tile::Type type = board.getTileAtPosition(laid_tile)->getSide(); 
  Color topcolor = board.getTileAtPosition(laid_tile)->getTopColor();  
  int pos_x = laid_tile.getX(); 
  int pos_y = laid_tile.getY(); 
  
  if(player == COLOR_WHITE)
  {
    if(topcolor == COLOR_WHITE)
    {
      if(type == Tile::TYPE_CROSS)
      {
        next_tile_1_ = Position(pos_x, pos_y - 1);
        next_tile_2_ = Position(pos_x, pos_y + 1);
      }
      if(type == Tile::TYPE_CURVE_1)
      {
        next_tile_1_ = Position(pos_x - 1, pos_y);
        next_tile_2_ = Position(pos_x, pos_y - 1);
      }
      if(type == Tile::TYPE_CURVE_2)
      {
        next_tile_1_ = Position(pos_x + 1, pos_y);
        next_tile_2_ = Position(pos_x, pos_y - 1);
      }
    }
    else if(topcolor == COLOR_RED)
    {
      if(type == Tile::TYPE_CROSS)
      {
        next_tile_1_ = Position(pos_x - 1, pos_y);
        next_tile_2_ = Position(pos_x + 1, pos_y);
      }
      if(type == Tile::TYPE_CURVE_1)
      {
        next_tile_1_ = Position(pos_x + 1, pos_y);
        next_tile_2_ = Position(pos_x, pos_y + 1);
      }
      if(type == Tile::TYPE_CURVE_2)
      {
        next_tile_1_ = Position(pos_x - 1, pos_y);
        next_tile_2_ = Position(pos_x, pos_y + 1);
      }
    }
  }
  else if(player == COLOR_RED)
  {
    if(topcolor == COLOR_RED)
    {
      if(type == Tile::TYPE_CROSS)
      {
        next_tile_1_ = Position(pos_x, pos_y - 1);
        next_tile_2_ = Position(pos_x, pos_y + 1);
      }
      if(type == Tile::TYPE_CURVE_1)
      {
        next_tile_1_ = Position(pos_x - 1, pos_y);
        next_tile_2_ = Position(pos_x, pos_y - 1);
      }
      if(type == Tile::TYPE_CURVE_2)
      {
        next_tile_1_ = Position(pos_x + 1, pos_y);
        next_tile_2_ = Position(pos_x, pos_y - 1);
      }
    }
    else if(topcolor == COLOR_WHITE)
    {
      if(type == Tile::TYPE_CROSS)
      {
        next_tile_1_ = Position(pos_x - 1, pos_y);
        next_tile_2_ = Position(pos_x + 1, pos_y);
      }
      if(type == Tile::TYPE_CURVE_1)
      {
        next_tile_1_ = Position(pos_x + 1, pos_y);
        next_tile_2_ = Position(pos_x, pos_y + 1);
      }
      if(type == Tile::TYPE_CURVE_2)
      {
        next_tile_1_ = Position(pos_x - 1, pos_y);
        next_tile_2_ = Position(pos_x, pos_y + 1);
      }
    }
  }
  // no next tile
  if(board.getTileAtPosition(next_tile_1_) == nullptr)
  {
    next_tile_1_ = Position::INVALID; 
  }
  if (board.getTileAtPosition(next_tile_2_) == nullptr)
  {
    next_tile_2_ = Position::INVALID;
  }
  
}

//------------------------------------------------------------------------------
Position NextTile::getNextTile1() const
{
  return next_tile_1_;
}

//------------------------------------------------------------------------------
Position NextTile::getNextTile2() const
{
  return next_tile_2_;
}
