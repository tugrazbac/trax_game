//------------------------------------------------------------------------------
// PlayCommand.cpp
//
//------------------------------------------------------------------------------
//
#ifndef PLAY_COMMAND_H
#define	PLAY_COMMAND_H

#include "Command.h"

class Position;

class PlayCommand : public Command
{
  public:
    PlayCommand();
    virtual ~PlayCommand();
    
    //--------------------------------------------------------------------------
    // Executes the quit command.
    // @param board turns of the endless loop in the game.cpp
    // @return Integer representing the success of the action
    virtual int execute(Game& board, std::vector<std::string>& params);
    
    //--------------------------------------------------------------------------
    // @return param count
    virtual unsigned int getParamCnt();
  private:
    std::vector<Position> getSurounding(Game &board);

};

#endif	/* PLAY_COMMAND_H */

