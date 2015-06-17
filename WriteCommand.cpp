//------------------------------------------------------------------------------
// WriteCommand.cpp
//
// Group: Group 11591, study assistant Thomas Neff
//
// Authors: Benjamin Franz Herbert Rauch 1431077
// Peter Lorenz 1114658
// Rene Hasenburger 1432147
//------------------------------------------------------------------------------
//

const int FILE_INDEX = 0;
typedef signed char schar;

#include "fstream" // ostream

#include "WriteCommand.h"
#include "Tile.h"
#include "Exceptions.h"
#include "Game.h"

//------------------------------------------------------------------------------
WriteCommand::WriteCommand() : Command("write")
{
}

//------------------------------------------------------------------------------
WriteCommand::~WriteCommand()
{
}

//------------------------------------------------------------------------------
unsigned int WriteCommand::getParamCnt() 
{
  return 1;
}

//------------------------------------------------------------------------------
int WriteCommand::execute(Game &board, std::vector<std::string> &params)
{
  if(board.getStartTile() == nullptr)
  {
    throw TraxException(TraxException::BOARD_IS_EMPTY);
  }
  else
  {
    // write to file
    std::ofstream binary_file;
    binary_file.open(params[FILE_INDEX], std::ios::trunc | std::ios::binary);
    if(binary_file.fail())
    {
      throw TraxException(TraxException::CANNOT_WRITE_FILE,
        params[FILE_INDEX].c_str());
    }
    else
    {
      // write head to binary file
      char write_active_player = static_cast<char>(board.getActivePlayer());
      schar write_smallest_x = static_cast<schar>(board.getMinX());
      schar write_smallest_y = static_cast<schar>(board.getMinY());
      schar write_biggest_x = static_cast<schar>(board.getMaxX());
      schar write_biggest_y = static_cast<schar>(board.getMaxY());

      binary_file << "TRAX";
      binary_file << write_active_player;
      binary_file << write_smallest_x;
      binary_file << write_smallest_y;
      binary_file << write_biggest_x;
      binary_file << write_biggest_y;

      Tile *field_type;
      for(; write_smallest_y <= write_biggest_y; write_smallest_y++)
      {
        for (int x = write_smallest_x; x <= write_biggest_x; x++)
        {
          field_type = (board.getTileAtPosition(x, write_smallest_y));

          // check if field at position x,y is not empty
          if(field_type != nullptr)
          {
            // side: cross (1), curve1 "/" (2), curve2 "\" (3)
            binary_file << static_cast<char>(field_type->getSide());
            // topcolor: white(1), red(2)
            binary_file << static_cast<char>(field_type->getTopColor());
          }
          else
          {
            // side: no stone (0); topcolor: no color (0)
            binary_file << '\x0';
            binary_file << '\x0';
          }
        }
      }
    }
    binary_file.close();
  }

  return 0;
}
