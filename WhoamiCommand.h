// WhoamiCommand.h
//
//------------------------------------------------------------------------------
//

#ifndef WHO_AM_I_COMMAND_H
#define	WHO_AM_I_COMMAND_H

#include "Command.h"

class WhoamiCommand : public Command
{
public:
    //--------------------------------------------------------------------------
    // Constructor
    WhoamiCommand();
    
    //--------------------------------------------------------------------------
    // Copy Constructor
    //  WhoamiCommand(const WhoamiCommand& orig);
    
    //--------------------------------------------------------------------------
    // Destructor
    virtual ~WhoamiCommand();
    
    //--------------------------------------------------------------------------
    // Executes the whoami command.
    // @param board turns of the endless loop in the game.cpp
    // @return Integer representing the success of the action
    virtual int execute(Game &board, std::vector<std::string> &params);
    
    //--------------------------------------------------------------------------
    // @return param count
    virtual unsigned int getParamCnt();
};

#endif	/* WHO_AM_I_COMMAND_H */

    