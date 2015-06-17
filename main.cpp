//------------------------------------------------------------------------------
// main.cpp
//
//------------------------------------------------------------------------------
//

#include <iostream>
#include "Game.h"
#include "Exceptions.h"

//------------------------------------------------------------------------------
// main function, entry point for execution
// @param argc argument count
// @param **argv argument values
// @return return value for the OS
//
int main(int argc, char **argv)
{
  try
  {
    if(argc != 1 && (argc != 3))
      throw TraxException(TraxException::USAGE, argv[0]);

    if (argc == 3)
    {
      if (std::string(argv[1]) == "-g")
        Game::setWriteFile(argv[2]);
      else
        throw TraxException(TraxException::USAGE, argv[0]);
    }
    Game trax;
    trax.run();

    return 0;
  }
  catch(TraxException &ex)
  {
    std::cout << ex.what() << std::endl;
    if (ex.getErrorType() == TraxException::USAGE)
      return 2;
    return 0;
  }
  catch(std::bad_alloc)
  {
    std::cout << TraxException::MESSAGES[TraxException::OUT_OF_MEMORY]
      << std::endl;
    return 1;
  }
  
}