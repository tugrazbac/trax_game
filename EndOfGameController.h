//------------------------------------------------------------------------------
// EndOfGameController.h
//
//------------------------------------------------------------------------------
//
 
#ifndef END_OF_GAME_CONTROLLER_H
#define END_OF_GAME_CONTROLLER_H

#include "Color.h"
#include <vector>

class Position;
class Game;

//------------------------------------------------------------------------------
// A class containing various static methods to check for draws or wins
class EndOfGameController
{
  public:
    //--------------------------------------------------------------------------
    // Checks if the player has won the game. 
    //
    // @param board Instance of the current game 
    // @param player Color of the player which has to be checked 
    // @param laid_tile Position of the laid tile 
    //
    // @return bool If the player has won the game 
    static bool checkForWin(Game &board, Color player, Position laidTile); 

    //--------------------------------------------------------------------------
    // Checks if the game ends in a draw. 
    //
    //@param board Instance of the current game
    // @return bool If the game ends in a draw. 
    static bool checkForDraw(Game &board); 

  private:
    //--------------------------------------------------------------------------
    // Checks if the player has a closed line
    //
    // @param board Instance of the current game 
    // @param player Color of the player which has to be checked 
    // @param laid_tile Position of the laid tile 
    // @param next_tile Used for recursion, is nullptr at start
    // @param prev_tile Used for recursion, is nullptr at start
    //
    // @return bool If the player has a closed line 
    //
    static bool checkIfClosedLine(Game &board, Color player, Position laidTile, 
      Position nextTile, Position prevTile);

    //--------------------------------------------------------------------------
    // Checks if the player has line over 8 rows or 8 columns. 
    //
    // @param board Instance of the current game 
    // @param player Color of the player which has to be checked 
    // @param laid_tile Position of the laid tile 
    //
    // @return bool If the player has a line 
    //
    static bool checkIfLine(Game &board, Color player, Position laidTile);
};

#endif //END_OF_GAME_CONTROLLER_H