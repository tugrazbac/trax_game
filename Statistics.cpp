#include "Statistics.h"
#include "Tile.h"
#include <iostream>

using std::cout;
using std::endl;

Statistics::Statistics() : Command("statistics"),
  toggle_player_(0), remaining_tiles_(0), used_tiles_(0), red_tiles_topcolor_(0),
        white_tiles_topcolor_(0), cross_(0), left(0), right(0)
{
}

Statistics::~Statistics() 
{
}

int Statistics::execute(Game &board, std::vector<std::string> &params)
{
  toggle_player_ = board.getTogglePlayer();
  remaining_tiles_ = board.getRemainingTiles();
  used_tiles_ = 63 - board.getRemainingTiles();

  // write head to binary file
  char write_active_player = static_cast<char>(board.getActivePlayer());
  signed char write_smallest_x = static_cast<signed char>(board.getMinX());
  signed char write_smallest_y = static_cast<signed char>(board.getMinY());
  signed char write_biggest_x = static_cast<signed char>(board.getMaxX());
  signed char write_biggest_y = static_cast<signed char>(board.getMaxY());
  Tile *field_type;
  for(; write_smallest_y <= write_biggest_y; write_smallest_y++)
  {
    for (int x = write_smallest_x; x <= write_biggest_x; x++)
    {
      field_type = (board.getTileAtPosition(x, write_smallest_y));
      
      if(field_type->getTopColor() == 1)
        white_tiles_topcolor_++;
      if(field_type->getTopColor() == 2)
        red_tiles_topcolor_++;
      
      if(field_type->getSide() ==  1)
        cross_++;
      if(field_type->getSide() ==  2)
        left++;
      if(field_type->getSide() ==  3)
        right++;
    }
  }
  
  cout << "toggle player   " << toggle_player_   << endl;
  cout << "remaining tiles " << remaining_tiles_ << endl;
  cout << "used tiles      " << used_tiles_ << endl;
  cout << "white tiles     " << white_tiles_topcolor_ << endl;
  cout << "red tiles       " << red_tiles_topcolor_   << endl;
  cout << "cross           " << cross_  << endl;
  cout << "left            " << left << endl;
  cout << "right           " << right << endl;
  
  return 0;
}

unsigned int Statistics::getParamCnt()
{
  return 0;
}