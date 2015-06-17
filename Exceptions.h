//------------------------------------------------------------------------------
// Exception.h
//
// Group: Group 11591, study assistant Thomas Neff
//
//------------------------------------------------------------------------------
//

#ifndef TRAX_EXCEPTION_H
#define  TRAX_EXCEPTION_H

#include <exception>
#include <string>

//------------------------------------------------------------------------------
// Exceptions for the Trax game. A collection of error messages
class TraxException : public std::exception
{
  public:
    enum ErrorMessages 
    { 
      POSITION_MUST_BE_ZERO,
      FIELD_NOT_FREE,
      FIELD_NOT_CONNECTED,
      INVALID_PARAMS,
      CONNECTED_LINES_MISMATCH,
      NOT_ENOUGH_TILES_LEFT,
      CANNOT_WRITE_FILE,  //filename
      BOARD_IS_EMPTY,
      BYE,
      PLAYER_WINS,  //player
      DRAW,
      UNKNOWN_COMMAND,
      WRONG_PARAM_COUNT,
      OUT_OF_MEMORY,
      USAGE,  // how to
      TEAM_NAME,
    };

    static const std::string MESSAGES[];
  
    //--------------------------------------------------------------------------
    // destructor
    virtual ~TraxException();
  
    //--------------------------------------------------------------------------
    virtual const char *what() const noexcept;
  
    //--------------------------------------------------------------------------
    // constructor
    // @param message it is an enum, which collects some error messages
    // @param additionale_info (optional) if the programm will start with
    //        with three arguments
    TraxException(ErrorMessages message, const char *additional_info = nullptr);
  
    //--------------------------------------------------------------------------
    // getter to check the usage error
    const char *getAdditonalInfo() const;

    //--------------------------------------------------------------------------
    // getter for the type
    ErrorMessages getErrorType() const;
  
  private:
    const ErrorMessages error_msg_;
    const char *additional_info_;
    std::string error_full_msg_;
    
    //--------------------------------------------------------------------------
    // Replaces the first occurance of a certain string in a string with another
    // string.
    // @param str Thr string in which something is to be replaced
    // @param what What should be replaced
    // @param with What the "what" should be replaced with.
    // @return bool If a successfull replace occured.
    bool replace(std::string &str, const std::string &what,
      const std::string &with);
};

#endif  /* TRAX_EXCEPTION_H */

