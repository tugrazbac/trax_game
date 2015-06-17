//------------------------------------------------------------------------------
// EndOfGameController.cpp
//
// Group: Group 11591, study assistant Thomas Neff
//
// Authors: Benjamin Franz Herbert Rauch 1431077
// Peter Lorenz 1114658
// Rene Hasenburger 1432147
//------------------------------------------------------------------------------
//

#include "EndOfGameController.h"
#include "Tile.h"
#include "NextTile.h"
#include "Position.h"
#include "Game.h"

#include <vector>
#include <iostream>

//------------------------------------------------------------------------------
bool EndOfGameController::checkForWin(Game &board, Color player,
  Position laid_tile)
{
  return checkIfClosedLine(board, player, laid_tile, Position::INVALID,
    Position::INVALID) || checkIfLine(board, player, laid_tile);
}

//------------------------------------------------------------------------------
bool EndOfGameController::checkForDraw(Game &board)
{
  return board.getRemainingTiles() <= 0;
}

//------------------------------------------------------------------------------
bool EndOfGameController::checkIfLine(Game &board, Color player, 
  Position laid_tile)
{
  std::vector<Position> used_tiles;
  NextTile next_tiles(board, player, laid_tile);
  Position next_tile = Position::INVALID; 
  Position prev_tile = Position::INVALID; 

  bool run = true;
  bool start = true;
  int tiles_in_x = 0;
  int tiles_in_y = 0;

  std::vector<Position> ends;

  if (board.getTileAtPosition(laid_tile) == nullptr)
    return false; 

  int min_x = laid_tile.getX();
  int max_x = laid_tile.getX();
  int min_y = laid_tile.getY();
  int max_y = laid_tile.getY();

  for (int dir = 0; dir < 2; dir++)
  {
    while (run)
    {
      if (start)
      {
        next_tiles = NextTile(board, player, laid_tile);
        if (dir == 0) // one direction
        {
          used_tiles.push_back(laid_tile);
          prev_tile = laid_tile; 
          if (next_tiles.getNextTile1() != Position::INVALID)
          {
            next_tile = next_tiles.getNextTile1();
          }
          else // most left/right tile
          {
            run = false;
          }
        }
        else if (dir == 1) // other direction
        {
          used_tiles.push_back(laid_tile);
          prev_tile = laid_tile;
          if (next_tiles.getNextTile2() != Position::INVALID)
          {
            next_tile = next_tiles.getNextTile2();
          }
          else
          {
            run = false;
          }
        }
        start = false;
      }
      else
      {
        prev_tile = next_tile; 
        next_tiles = NextTile(board, player, next_tile);
        next_tile = next_tiles.getNextTile1();

        if (next_tile != Position::INVALID)
        {
          for (unsigned int i = 0; i < used_tiles.size(); i++)
          {
            if (next_tile == used_tiles[i])
            {
              next_tile = next_tiles.getNextTile2();
              break;
            }
          }
        }
      }

      if (next_tile != Position::INVALID)
      {
        used_tiles.push_back(next_tile);
        if (min_x > next_tile.getX())
          min_x = next_tile.getX();
        if (max_x < next_tile.getX())
          max_x = next_tile.getX();
        if (min_y > next_tile.getY())
          min_y = next_tile.getY();
        if (max_y < next_tile.getY())
          max_y = next_tile.getY();
      }
      else
      {
        run = false;
      }
    } //while

    run = true;
    start = true;
    used_tiles.clear();

    ends.push_back(prev_tile);
  } //for

  tiles_in_x = std::abs(max_x - min_x) + 1;
  tiles_in_y = std::abs(max_y - min_y) + 1;

  if (tiles_in_x >= 8)
  {
    int index = 0;
    if (ends[0].getX() > ends[1].getX())
      index = 1;

    return 
      board.getTileAtPosition(ends[index])->getColors().getLeft() == player &&
      board.getTileAtPosition(ends[(index + 1) % 2])->getColors().getRight()
      == player;
  }
  if (tiles_in_y >= 8)
  {
    int index = 0;
    if (ends[0].getY() > ends[1].getY())
      index = 1;

    return
      board.getTileAtPosition(ends[index])->getColors().getTop() == player &&
      board.getTileAtPosition(ends[(index + 1) % 2])->getColors().getBottom()
      == player;
  }

  return false;
}

//------------------------------------------------------------------------------
bool EndOfGameController::checkIfClosedLine(Game &board, Color player, 
  Position laid_tile, Position next_tile, Position prev_tile)
{
  Position next = Position::INVALID;
  Position prev = next_tile; 

  // start 
  if(next_tile == Position::INVALID && prev_tile == Position::INVALID)
  {
    if (board.getTileAtPosition(laid_tile) == nullptr)
      return false;

    NextTile next_tiles(board, player, laid_tile); // fuer geschlossene line jeder stein, einen nachfolger
    if(next_tiles.getNextTile1() == Position::INVALID || 
       next_tiles.getNextTile2() == Position::INVALID)
    {
      return false; 
     
    }
    else
    {
      next = next_tiles.getNextTile1(); 
    }
  }
  else // recursive call
  {
    NextTile next_tiles(board, player, next_tile);
    if(next_tiles.getNextTile1() == Position::INVALID || 
       next_tiles.getNextTile2() == Position::INVALID)
    {
      return false; 
    }

    next = next_tiles.getNextTile1();
    // avoid endless loop, switch left, right
    if (next == prev_tile)
    {
      next = next_tiles.getNextTile2(); 
    }
  }

  if(next_tile != Position::INVALID && prev_tile != Position::INVALID)
  {
    // closed line 
    if (laid_tile == next)
    {
      return true; 
    }
  }
  return checkIfClosedLine(board, player, laid_tile, next, prev);
}
