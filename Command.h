//------------------------------------------------------------------------------
// Command.h
//
//
//------------------------------------------------------------------------------
//

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

class Game;

//------------------------------------------------------------------------------
// Abstract class every command used in the game must inherit from.
class Command
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    Command(const Command &original);

    //--------------------------------------------------------------------------
    // Private assignment operator
    Command &operator=(const Command &original);

    //--------------------------------------------------------------------------
    /// Name of this command
    std::string command_name_;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    Command(std::string name);

    //--------------------------------------------------------------------------
    // Destructor
    virtual ~Command();
    
    //--------------------------------------------------------------------------
    // Executes the command.
    // @param board The board where action should be performed on
    // @param params Possible parameters neede for the execution
    // @return Integer representing the success of the action
    virtual int execute(Game &board, std::vector<std::string> &params) = 0;

    //--------------------------------------------------------------------------
    // Get the number of parameters the command must have
    // return Integer The exact number of parameters needed for the command to
    //   run successfully
    virtual unsigned int getParamCnt() = 0;

    //--------------------------------------------------------------------------
    // Gets the command and the arguments from an input string. To command will
    // be lower cased.
    // @param str The input string from which command and parameters are taken
    // @param command A reference to a string that the command will be over-
    //   written to. The command will be returned in lowercase.
    // @return std::vector<std::string> The by whitespace seperated arguments
    //   after the command. Empty arguments will not be added.
    static std::vector<std::string> args(const std::string &str,
      std::string &command);

    //--------------------------------------------------------------------------
    // Getter Methods
    const std::string &getName() const;
};

#endif //COMMAND_H


