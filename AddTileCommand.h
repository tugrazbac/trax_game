//------------------------------------------------------------------------------
// AddTileCommand.h
//
//
//------------------------------------------------------------------------------
//

#ifndef ADD_TILE_COMMAND_H
#define ADD_TILE_COMMAND_H

#include "Command.h"
#include "Color.h"

class Position;

//------------------------------------------------------------------------------
// Class for adding tiles to the gameboard. Inherits from the abstract command
// class
class AddTileCommand : public Command
{
  public:
    //--------------------------------------------------------------------------
    // Executes the add tile command.
    // @param board The board where action should be performed on
    // @param params Possible parameters neede for the execution
    // @return Integer, the number of tiles added
    virtual int execute(Game &board, std::vector<std::string> &params);

    //--------------------------------------------------------------------------
    // Get the number of parameters the command must have
    // return Integer The exact number of parameters needed for the command to
    //   run successfully. In this case always 2.
    virtual unsigned int getParamCnt();

    //--------------------------------------------------------------------------
    // Default constructor
    AddTileCommand();

    //--------------------------------------------------------------------------
    // Default destructor
    virtual ~AddTileCommand();
    
    //--------------------------------------------------------------------------
    // Check if the tile is clearly defined and place it if so. If a tile is
    // placed the neighbours will also be checked for now defined tiles.
    // @param board The board where actions should be performed on
    // @param x The x coordinate to check on
    // @param y The y coordinate to check on
    // @param buffer of positions to clear if running out of tiles
    // @return Integer, the number of tiles added
    static int checkAdditionalTiles(Game &board, int x, int y, 
      std::vector<Position> &buffer);

  private:
    //--------------------------------------------------------------------------
    // private copy constructor
    AddTileCommand(const AddTileCommand &orig);
};

#endif //ADD_TILE_COMMAND_H
