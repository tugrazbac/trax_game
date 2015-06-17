//------------------------------------------------------------------------------
// Game.h
//
//------------------------------------------------------------------------------
//

#ifndef GAME_H
#define GAME_H

#include "Color.h"

#include <vector>

//forward declaration
class Tile;
class Position;
class Command;

//------------------------------------------------------------------------------
// Class for the Trax game.
// Contains methods to start the game, set the start tile, get the current
// player as well as toggle them.
//
class Game 
{
  private:
    
    
    int white_wins;
    int red_wins;
    
    
    
    Color active_player_;
    Tile *start_tile_;
    bool running_;

    
    std::vector<Command *> command_array_;
    std::vector<std::vector<Tile *> > played_tiles_;

    int min_x_ = 0;
    int max_x_ = 0;
    int min_y_ = 0;
    int max_y_ = 0;
    int remaining_tiles_ = 0;
    int toggle_player_;

    static char *write_file_;
  
    //--------------------------------------------------------------------------
    // executes the write command if a value greater zero is passed and if the
    // static member has been initialized with setWriteFile(char *). 
    // @param greater_zero if a value less or equal zero is passed, the write
    //        command won't be executed
    void write(int greater_zero);

  public:
    
 

    
    //--------------------------------------------------------------------------
    // Default Constructor. New games get start with the active_player as white
    // and the start tile as null.
    Game();
    
    //--------------------------------------------------------------------------
    // Default Destructor. Deletes all the pointers stored in played_tiles_
    ~Game();
    
    //--------------------------------------------------------------------------
    // Copy Constructor
    Game(const Game &orig);

    
    void setWhite()
    {
      white_wins++;
    }
    
    void setRed()
    {
      red_wins++;
    }
    
    int getWhite()
    {
      return white_wins;
    }
    
    int getRed()
    {
      return red_wins;
    }
    
    //--------------------------------------------------------------------------
    // setter write file
    static void setWriteFile(char *file);
    //--------------------------------------------------------------------------
    // getter write file
    static char *getWriteFile();

    //--------------------------------------------------------------------------
    // getters for start_tile_ and active_player_ and the min and max x/y values
    Tile *getStartTile() const;
    Color getActivePlayer() const;
    int getMinX() const;
    int getMaxX() const;
    int getMinY() const;
    int getMaxY() const;

    //--------------------------------------------------------------------------
    // setters for start_tile_ and active_player_ and the min and max x/y values
    // the min/max setters determines on it's own where to write.
    void setStartTile(Tile *start_tile);
    void setRunning(const bool running);
    void setMinMaxX(const int x);
    void setMinMaxY(const int y);
    
    //--------------------------------------------------------------------------
    // get the Tile pointer at a given position, nullptr if empty.
    // @paraam pos The position at which a Tile should be fetched
    // @return Tile * A pointer to the tile which was fetched from the field
    Tile *getTileAtPosition(const Position &pos) const;
    //--------------------------------------------------------------------------
    // get the Tile pointer at a given position, nullptr if empty.
    // @paraam x The x position at which a Tile should be fetched
    // @paraam y The y position at which a Tile should be fetched
    // @return Tile * A pointer to the tile which was fetched from the field
    Tile *getTileAtPosition(const int x, const int y) const;

    void deleteTileAtPositon(const Position &pos, Tile *tile);
    
    //--------------------------------------------------------------------------
    // set or overwrite the Tile pointer at a given position, nullptr if empty.
    // @param pos The position at which a tile should be (over)written
    // @param *tile The tile pointer
    void setTileAtPosition(const Position &pos, Tile *tile);
    

    //--------------------------------------------------------------------------
    // Checks if a player has won the game and throws a TraxException
    // containging the winning message.
    // @param laid_tile Position of the laid tile.  
    // @return bool If a player has won the game. 
    bool checkForWin(Position laid_tile); 

    //--------------------------------------------------------------------------
    // Checks for a draw of the game and throws a TraxException containing the
    // message
    void checkForDraw();
    
    //--------------------------------------------------------------------------
    // Get's the remaining tiles before the game ends in a draw
    // @return  int The remeining tiles... duh
    int getRemainingTiles() const;
    
    //--------------------------------------------------------------------------
    // Starts the actual game in a loop until running_ is set false.
    // The program will continuesly pring "sep> " and then read a line and
    // execute the commands that are inputed through it.
    int run();

    //--------------------------------------------------------------------------
    // Toggles the active player from COLOR_RED to COLOR_WHITE and vice versa.
    void togglePlayer();

    //--------------------------------------------------------------------------
    // getter for the whole board
    std::vector<std::vector<Tile *> > getBoard();
    //--------------------------------------------------------------------------
    // setter for the whole board
    void overwriteBoard(const std::vector<std::vector<Tile *> > board);
    
    //--------------------------------------------------------------------------
    // enforces certain values for the min and the max x/y values
    // @param min Holding the minX and minY value
    // @param max Holding the maxX and maxY value
    void forceMinMax(const Position &min, const Position &max);

    //------------------------------------------------------------------------------
    // Inverts a color enumerator. COLOR_MISMATCH and COLOR_NOT_DEFINED remain
    // unchanged.
    // @param col The color to be converted and inverted.
    // @return Color The inverted color.
    static Color getInvertedColor(Color col);
    
    std::vector<Command *> getCommandArray() const
    {
      return command_array_;
    }
    
    int getTogglePlayer()
    {
      return toggle_player_;
    }

};
#endif  /* GAME_H */



