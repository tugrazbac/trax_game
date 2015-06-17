//------------------------------------------------------------------------------
// QuitCommand.h
//
//------------------------------------------------------------------------------
//

#ifndef QUIT_COMMAND_H
#define QUIT_COMMAND_H

#include "Command.h"

class QuitCommand : public Command
{
  public:
    //--------------------------------------------------------------------------
    // constructor
    QuitCommand();
    
    //--------------------------------------------------------------------------
    // destructor
    virtual ~QuitCommand();
    
    //--------------------------------------------------------------------------
    // Executes the quit command.
    // @param board turns of the endless loop in the game.cpp
    // @return Integer representing the success of the action
    virtual int execute(Game& board, std::vector<std::string>& params);
    
    //--------------------------------------------------------------------------
    // @return param count
    virtual unsigned int getParamCnt();
    
  private:
    //--------------------------------------------------------------------------
    // copy constructor
    QuitCommand(const QuitCommand &orig);
};

#endif  /* QUIT_COMMAND_H */

