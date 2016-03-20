//------------------------------------------------------------------------------
// PlayCommand.cpp
//
// Group: Group 11591, study assistant Thomas Neff
//
// Authors: Benjamin Franz Herbert Rauch 
// Peter Lorenz 
// Rene Hasenburger 
//------------------------------------------------------------------------------
//

#include "PlayCommand.h"
#include "Exceptions.h"
#include "Position.h"
#include <iostream>
#include "Game.h"
#include "AddTileCommand.h"
#include <vector>
#include <algorithm>
#include <cstdlib>

PlayCommand::PlayCommand() : Command("play") 
{
}

PlayCommand::~PlayCommand() 
{
}

std::vector<Position> PlayCommand::getSurounding(Game& board)
{
  std::vector<Position> pos;
  for(int x = board.getMinX(); x <= board.getMaxX(); x++)
  {
    for(int y = board.getMinY(); y <= board.getMaxY(); y++)
    {
      if(board.getTileAtPosition(x, y) != nullptr)
      {
        if( board.getTileAtPosition(x + 1, y) == nullptr &&
          std::find(pos.begin(), pos.end(), Position(x + 1, y)) == pos.end() )
        {
            pos.push_back(Position(x + 1, y));
        }
        if(board.getTileAtPosition(x - 1, y) == nullptr &&
          std::find(pos.begin(), pos.end(), Position(x - 1, y)) == pos.end() )
        {
          pos.push_back(Position(x - 1, y));
        }
        if(board.getTileAtPosition(x, y + 1) == nullptr &&
          std::find(pos.begin(), pos.end(), Position(x, y + 1)) == pos.end() )
        {
          pos.push_back(Position(x, y + 1));
        }
        if(board.getTileAtPosition(x, y - 1) == nullptr && 
          std::find(pos.begin(), pos.end(), Position(x,  - 1)) == pos.end() )
        {
          pos.push_back(Position(x, y - 1));
        }
      }
    }
  }
  if(pos.empty())
    pos.push_back(Position(0,0));
  return pos;
}


int PlayCommand::execute(Game &board, std::vector<std::string> &params)
{
  std::vector<Position> pos = getSurounding(board);
  
  std::vector<std::string> options;
  options.push_back("+");
  options.push_back("\\");
  options.push_back("/");
  
  Color active =board.getActivePlayer();
  Color invertedColor = Game::getInvertedColor(active); 
  std::string col[] {"dummy", "white", "red"};
  
  //search for winning tile
  for(const auto &single_pos : pos)
  {
    for(const auto &opt : options)
    {
      Game copy_of_game = board;
      AddTileCommand cmd;
      std::vector<std::string> args;
      args.push_back(single_pos.toString());
      std::cout << single_pos.toString() << std::endl;
      args.push_back(opt);
      
      try
      {
        cmd.execute(copy_of_game, args);
      }
      catch(TraxException &ex)
      {
        if(ex.getErrorType() == TraxException::PLAYER_WINS &&
          std::string(ex.getAdditonalInfo()) == col[active])
        {
          std::cout << single_pos.toString() << " " << opt << std::endl;
          cmd.execute(board, args);
        }
      }
    }
  }
  
  //play normal
  Game main_copy = board;
  bool still_playing = true;
  do
  {
    int random = rand() % pos.size();
    std::vector<std::string> options_new;
    options_new.push_back("+");
    options_new.push_back("\\");
    options_new.push_back("/");    
  
    AddTileCommand cmd;
    std::vector<std::string> args;
    
    while(options_new.size() != 0)
    {
      Game copy_of_game = main_copy;
      int option_index = rand() % options_new.size();
      args.push_back(pos.at(random).toString());
      args.push_back(options_new.at(option_index));
      try
      {
        cmd.execute(copy_of_game, args);
        cmd.execute(main_copy, args);  
        
        //check if opponent wins
        std::vector<Position> new_pos = getSurounding(main_copy);
        for(const auto &single_pos : new_pos)
        {
          for(const auto &opt : options)
          {
            Game copy_of_main_copy = main_copy;
            std::vector<std::string> args_opp;
            args_opp.push_back(single_pos.toString());
            args_opp.push_back(opt);
            try
            {
              cmd.execute(copy_of_main_copy, args_opp);
            }
            catch(TraxException &ex)
            {
              if(ex.getErrorType() == TraxException::PLAYER_WINS &&
                std::string(ex.getAdditonalInfo()) == col[invertedColor])
              {
                throw ex;
              }
            }
          }
        }
        
        still_playing = false;
        std::cout << pos.at(random).toString() << " " 
          << options_new.at(option_index) << std::endl;
        cmd.execute(board, args);
        break;        
      }
      catch(TraxException &ex)
      {
        options_new.erase(options_new.begin() + option_index);
        args.clear();
      }
    }    
    pos.erase(pos.begin() + random);
    
  }while(still_playing && pos.size() != 0);
  
  return 1;
}

unsigned int PlayCommand::getParamCnt()
{
  return 0;
}
