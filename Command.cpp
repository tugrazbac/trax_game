//------------------------------------------------------------------------------
// Command.cpp
//
// Group: Group 11591, study assistant Thomas Neff
//
// Authors: Benjamin Franz Herbert Rauch 1431077
// Peter Lorenz 1114658
// Rene Hasenburger 1432147
//------------------------------------------------------------------------------
//

#include "Command.h"

//------------------------------------------------------------------------------
Command::Command(std::string name) : command_name_(name)
{
}

//------------------------------------------------------------------------------
Command::~Command()
{
}

//------------------------------------------------------------------------------
std::vector<std::string> Command::args(const std::string &str, 
  std::string &command)
{
  std::size_t start_pos = str.find(" ");
  command = str.substr(0, start_pos);

  for (auto &c : command)
  {
    int ic = static_cast<int>(c);
    if (65 <= ic && ic <= 90)
      c = static_cast<char>(ic + 32);
  }

  std::vector<std::string> vec;
  while (start_pos != std::string::npos)
  {
    std::size_t next = str.find(" ", start_pos + 1);
    std::string arg = str.substr(start_pos + 1, next - (start_pos + 1));
    if (arg != "")
      vec.push_back(arg);
    start_pos = next;
  }
  return vec;
}

//------------------------------------------------------------------------------
const std::string &Command::getName() const
{
  return command_name_;
}
