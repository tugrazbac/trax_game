//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 11591, study assistant Thomas Neff
//
// Authors: Benjamin Franz Herbert Rauch 1431077
// Peter Lorenz 1114658
// Rene Hasenburger 1432147
//------------------------------------------------------------------------------
//

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "Game.h"
#include "Color.h"
#include "Tile.h"
#include "Position.h"

#include "AddTileCommand.h"
#include "WriteCommand.h"
#include "QuitCommand.h"
#include "WhoamiCommand.h"
#include "PlayCommand.h"
#include "verVollstandigen.h"
#include "Statistics.h"
#include "SetTile.h"
#include "Reset.h"
#include "Status.h"

#include "Exceptions.h"
#include "EndOfGameController.h"
#include "SetTile.h"
#include "DelLast.h"
#include <memory>

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
char *Game::write_file_ = nullptr;

//------------------------------------------------------------------------------
char *Game::getWriteFile()
{
  return write_file_;
}

//------------------------------------------------------------------------------

void Game::setWriteFile(char *file)
{
  write_file_ = file;
}

//------------------------------------------------------------------------------
Game::Game() : active_player_(COLOR_WHITE), start_tile_(nullptr),
  played_tiles_(1, std::vector<Tile *>(1, nullptr)),
  remaining_tiles_(Tile::MAXIMUM_TILES), toggle_player_(0), red_wins(0), white_wins(0)
{
  command_array_.push_back(new QuitCommand());
  command_array_.push_back(new WriteCommand());
  command_array_.push_back(new AddTileCommand());
  command_array_.push_back(new WhoamiCommand());
  command_array_.push_back(new PlayCommand());
  command_array_.push_back(new verVollstandigen());
  command_array_.push_back(new Statistics());
  command_array_.push_back(new SetTile());
  command_array_.push_back(new DelLast());
  command_array_.push_back(new Reset());
  command_array_.push_back(new Status());
}

//------------------------------------------------------------------------------
Game::~Game()
{
  for (auto &vec_var : played_tiles_)
    for (auto &tile_var : vec_var)
      delete tile_var;
    
  for(auto &cmd : command_array_)
    delete cmd;
}

Game::Game(const Game &orig) : active_player_(orig.active_player_), 
  start_tile_(orig.start_tile_),
  played_tiles_(1, std::vector<Tile *>(1, nullptr)),
  remaining_tiles_(Tile::MAXIMUM_TILES)
{
  //pos pos
  for(int x = 0; x <= orig.max_x_; x++)
    for(int y = 0; y <= orig.max_y_; y++)
    {
      Tile *tile = orig.getTileAtPosition(x, y);
      if(tile != nullptr)
        tile = new Tile(tile->getSide(), tile->getTopColor());
      setTileAtPosition(Position(x, y), tile);
    }
  //pos neg
  for(int x = 0; x <= orig.max_x_; x++)
    for(int y = -1; y >= orig.min_y_; y--)
    {
      Tile *tile = orig.getTileAtPosition(x, y);
      if(tile != nullptr)
        tile = new Tile(tile->getSide(), tile->getTopColor());
      setTileAtPosition(Position(x, y), tile);
    }
  //neg neg
  for(int x = -1; x >= orig.min_x_; x--)
    for(int y = -1; y >= orig.min_y_; y--)
    {
      Tile *tile = orig.getTileAtPosition(x, y);
      if(tile != nullptr)
        tile = new Tile(tile->getSide(), tile->getTopColor());
      setTileAtPosition(Position(x, y), tile);
    }
  //neg pos
  for(int x = -1; x >= orig.min_x_; x--)
    for(int y = 0; y <= orig.max_y_; y++)
    {
      Tile *tile = orig.getTileAtPosition(x, y);
      if(tile != nullptr)
        tile = new Tile(tile->getSide(), tile->getTopColor());
      setTileAtPosition(Position(x, y), tile);
    }
}

//------------------------------------------------------------------------------
void Game::write(int greater_zero)
{
  if (write_file_ != nullptr && greater_zero > 0)
  {
    std::vector<std::string> temp;
    temp.push_back(write_file_);
    WriteCommand wr;
    wr.execute(*this, temp);
  }
}

//------------------------------------------------------------------------------
int Game::run()
{
  std::string read_line;
  running_ = true;

  while( running_ )
  {
    cout << "sep> ";
    getline(std::cin, read_line);
    if(read_line == "")
      continue;
    
    // words a seperated by a blank symbol. each word are stored in a vector
    std::vector<std::string> params_stream;
    std::stringstream ss(read_line);
    std::string temp;
    while(ss >> temp)
    {
      params_stream.push_back(temp);
    }
    
    // case insensitive 
    std::transform(params_stream[0].begin(), params_stream[0].end(), 
      params_stream[0].begin(), tolower);
    
    // compares the input with command array, if known, command will be
    // executed
    int result = -1;
    try
    {
      for(auto &cmd : command_array_)
      {
        if(params_stream[0].compare(cmd->getName()) == 0)
        {
          // remove first element (command)
          params_stream.erase(params_stream.begin());
          if(cmd->getParamCnt() == params_stream.size())
          {
            result = cmd->execute(*this, params_stream);
          }
          else
          {
            // Wrong ParamCount
            result = 0;
            throw TraxException(TraxException::WRONG_PARAM_COUNT);
          }
          break;
        }
      }

      if(result == -1)
      {
        // Unknown Command
        throw TraxException(TraxException::UNKNOWN_COMMAND);
      }
    }
    catch(TraxException &ex)
    {
      cout << ex.what() << endl;
      if (ex.getErrorType() == TraxException::DRAW || 
        ex.getErrorType() == TraxException::PLAYER_WINS)
        result = 1;
    }
    write(result);
  }
  return 0;
}

void Game::deleteTileAtPositon(const Position &pos, Tile *tile)
{
  if(played_tiles_.size() != 0) 
    played_tiles_.pop_back();
  else 
    cout << "No Tiles Left" << endl;
}

//------------------------------------------------------------------------------
void Game::setTileAtPosition(const Position &pos, Tile *tile)
{
  int x = pos.getX() - getMinX();
  int y = pos.getY() - getMinY();

  //if X is below the current index...
  if (x == -1)
  {
    //insert a new vector at the beginning filled with nullptr's of the same
    //length as the others (there has to be one at 0 so just referenzing that)
    played_tiles_.insert(played_tiles_.begin(),
      std::vector<Tile *>(played_tiles_[0].size(), nullptr));
    x++;
  }
  //if x is too big  static_cast<unsigned>
  else if (static_cast<unsigned>(x) == played_tiles_.size())
  {
    //add a new vector filled with nullptr's at the end, same length as others
    played_tiles_.push_back(
      std::vector<Tile *>(played_tiles_[0].size(), nullptr));
  }

  //if Y is below the index, insert a new nullptr at the beginning of every vec
  if (y == -1)
  {
    for (auto &vec : played_tiles_)
      vec.insert(vec.begin(), nullptr);
    y++;
  }
  //all vec in placed_tiles_ have same lenght, so any is fine. 0 is sure to be
  //available. if the index is too big
  else if (static_cast<unsigned>(y) == played_tiles_[0].size())
  {
    //add a new nullptr at the end of every vector
    for (auto &vec : played_tiles_)
      vec.push_back(nullptr);
  }

  setMinMaxX(pos.getX());
  setMinMaxY(pos.getY());
  
  played_tiles_.at(x).at(y) = tile;
  if(tile != nullptr)
    remaining_tiles_--;
}


//------------------------------------------------------------------------------
Tile *Game::getTileAtPosition(const Position &pos) const
{
  int x = pos.getX() - getMinX();
  int y = pos.getY() - getMinY();
  
  //out of index
  if (x < 0 || y < 0 || x >= static_cast<int>(played_tiles_.size()) ||
    y >= static_cast<int>(played_tiles_[0].size()))
  {
    return nullptr;
  }
  return played_tiles_.at(x).at(y);
}

//------------------------------------------------------------------------------
Tile *Game::getTileAtPosition(const int x, const int y) const
{
  int new_x = x - getMinX();
  int new_y = y - getMinY();

  //out of index
  if (new_x < 0 || new_y < 0 || new_x >= static_cast<int>(played_tiles_.size()) 
    || new_y >= static_cast<int>(played_tiles_[0].size()))
  {
    return nullptr;
  }
  return played_tiles_.at(new_x).at(new_y);
}

int Game::getRemainingTiles() const
{
  return remaining_tiles_;
}

//------------------------------------------------------------------------------
void Game::checkForDraw()
{
  if (EndOfGameController::checkForDraw(*this))
  {
    (*this).setRunning(false);
    throw TraxException(TraxException::DRAW);
  }
}

//------------------------------------------------------------------------------
bool Game::checkForWin(Position laid_tile)
{
  Color active = getActivePlayer();
  Color invertedColor = getInvertedColor(active); 
  const char *col[] {"dummy", "white", "red"};

  if (EndOfGameController::checkForWin(*this, active, laid_tile))
  {
    if((int)active == 1)
      white_wins++;
    else
      red_wins++;
      
      
      
    throw TraxException(TraxException::PLAYER_WINS, col[active]);
    
  }
  else if (EndOfGameController::checkForWin(*this, invertedColor, laid_tile))
  {
//    setRunning(false);
    if((int)active == 1)
      white_wins++;
    else
     red_wins++;
    throw TraxException(TraxException::PLAYER_WINS, col[invertedColor]);
  }
  return false; 
  
}

// -----------------------------------------------------------------------------
void Game::setStartTile(Tile *start)
{
  start_tile_ = start;
}

// -----------------------------------------------------------------------------
void Game::setRunning(bool running)
{
  running_ = running;
}

//------------------------------------------------------------------------------
void Game::setMinMaxX(const int x)
{
  if (x < min_x_)
    min_x_ = x;
  if (x > max_x_)
    max_x_ = x;
}

//------------------------------------------------------------------------------
void Game::setMinMaxY(const int y)
{
  if (y < min_y_)
    min_y_ = y;
  if (y > max_y_)
    max_y_ = y;
}

//------------------------------------------------------------------------------
void Game::togglePlayer()
{
  active_player_ = getInvertedColor(active_player_);
  toggle_player_++;
}

//------------------------------------------------------------------------------
Tile *Game::getStartTile() const
{
  return start_tile_;
}

//------------------------------------------------------------------------------
int Game::getMaxX() const
{
  return max_x_;
}
//------------------------------------------------------------------------------
int Game::getMinX() const
{
  return min_x_;
}
//------------------------------------------------------------------------------
int Game::getMaxY() const
{
  return max_y_;
}
//------------------------------------------------------------------------------
int Game::getMinY() const
{
  return min_y_;
}

// -----------------------------------------------------------------------------
Color Game::getActivePlayer() const
{
  return active_player_;
} 

// -----------------------------------------------------------------------------
Color Game::getInvertedColor(Color col)
{
  if (col == COLOR_RED)
    return COLOR_WHITE;
  if (col == COLOR_WHITE)
    return COLOR_RED;
  return col;
}

// -----------------------------------------------------------------------------
std::vector<std::vector<Tile *> > Game::getBoard()
{
  return played_tiles_;
}

// -----------------------------------------------------------------------------
void Game::overwriteBoard(const std::vector<std::vector<Tile *> > board)
{
  played_tiles_ = board;
}

// -----------------------------------------------------------------------------
void Game::forceMinMax(const Position &min, const Position &max)
{
  min_x_ = min.getX();
  min_y_ = min.getY();
  max_x_ = max.getX();
  max_y_ = max.getY();
}
