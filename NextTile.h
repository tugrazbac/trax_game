//------------------------------------------------------------------------------
// NextTile.h
//
//------------------------------------------------------------------------------
//
 
#ifndef NEXT_TILE_H
#define NEXT_TILE_H

#include "Position.h"
#include "Color.h"

class Game;

//------------------------------------------------------------------------------
// Class that fetches the neighbouring tiles depending on the position and the
// color. If there is no neighbouring tile, the Position will be set to
// Position::INVALID
//
class NextTile
{
  private:
    Position next_tile_1_;
    Position next_tile_2_;

    //--------------------------------------------------------------------------
    //private copy constructor
    NextTile(const NextTile &orig);

  public: 

    //--------------------------------------------------------------------------
    //Default destructor
    ~NextTile();

    //--------------------------------------------------------------------------
    // Constructor of the NextTile class. Calculates both next tiles of the 
    // laid_tile.
    //
    // @param board Instance of the current game 
    // @param player Color of the player which has to be checked 
    // @param laid_tile Position of the laid tile 
    //
    NextTile(Game &board, Color player, Position laid_tile);

    //--------------------------------------------------------------------------
    // Getter for both next tiles
    Position getNextTile1() const;
    Position getNextTile2() const; 
};

#endif //NEXT_TILE_H