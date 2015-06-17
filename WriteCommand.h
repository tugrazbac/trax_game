//------------------------------------------------------------------------------
// WriteCommand.h
//
//------------------------------------------------------------------------------
//

#ifndef WRITE_COMMAND_H
#define WRITE_COMMAND_H

#include "Command.h"

//------------------------------------------------------------------------------
// Class for writing the game board to a file. Inherits from the abstract
// Command class.
class WriteCommand : public Command 
{
  public:
    //--------------------------------------------------------------------------
    // Constructor
    WriteCommand();
    
    //--------------------------------------------------------------------------
    // Destructor
    virtual ~WriteCommand();
    
    //--------------------------------------------------------------------------
    // getter to check, if there is one param availables
    virtual unsigned int getParamCnt();
    
    //--------------------------------------------------------------------------
    // Executes write + filename
    // @param board read tiles and write them into the binary
    // @param params params[0] is the binary filename
    // @return Integer representing the success of the action
    virtual int execute(Game& board, std::vector<std::string>& params);
};

#endif  /* WRITE_COMMAND_H */

