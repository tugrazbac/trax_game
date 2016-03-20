//------------------------------------------------------------------------------
// Exception.cpp
//
// Group: Group 11591, study assistant Thomas Neff
//
// Authors: Benjamin Franz Herbert Rauch 
// Peter Lorenz 
// Rene Hasenburger 
//------------------------------------------------------------------------------
//

#include "Exceptions.h"


const std::string TraxException::MESSAGES[] =
{
  "Invalid coordinates - first tile must be set on (0,0)",
  "Invalid coordinates - field not empty",
  "Invalid coordinates - field not connected to tile",
  "Invalid parameters",
  "Invalid move - connected line colors mismatch",
  "Invalid move - not enough tiles left",
  "Cannot write file REPLACE",
  "Board is empty!",
  "Bye!",
  "Player REPLACE wins!",
  "No more tiles left. Game ends in a draw!",
  "Error: Unknown command!",
  "Error: Wrong parameter count!",
  "Error: Out of Memory!",
  "Usage: REPLACE",
  "TheBOTsAboveCheated"
};


//------------------------------------------------------------------------------
TraxException::TraxException(ErrorMessages message, const char *additional_info)
  : error_msg_(message), additional_info_(additional_info) 
{
  std::string str = MESSAGES[static_cast<int>(error_msg_)];

  if (additional_info_ != nullptr)
    replace(str, "REPLACE", additional_info_);

  //store the error message for the what() call
  error_full_msg_ = str;
}

//------------------------------------------------------------------------------
TraxException::~TraxException()
{
}

//------------------------------------------------------------------------------
const char *TraxException::what() const noexcept
{
  return error_full_msg_.c_str();
}

//--------------------------------------------------------------------------
bool TraxException::replace(std::string &str, const std::string &what,
const std::string &with)
{
  int start_pos = str.find(what);
  if (static_cast<unsigned>(start_pos) == std::string::npos)
    return false;
  str.replace(start_pos, what.length(), with);
  return true;
}

//------------------------------------------------------------------------------
const char *TraxException::getAdditonalInfo() const
{
  return additional_info_;
}

//------------------------------------------------------------------------------
TraxException::ErrorMessages TraxException::getErrorType() const
{
  return error_msg_;
}
