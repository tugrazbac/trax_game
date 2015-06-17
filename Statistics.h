
#ifndef STATISTICS_H
#define	STATISTICS_H

#include "Command.h"
#include "Game.h"


class Statistics : public Command
{
public:
  Statistics();
  virtual ~Statistics();
  virtual int execute(Game &board, std::vector<std::string> &params);

  //--------------------------------------------------------------------------
  // Get the number of parameters the command must have
  // return Integer The exact number of parameters needed for the command to
  //   run successfully
  virtual unsigned int getParamCnt();
  
  int toggle_player_;
  int remaining_tiles_;
  int used_tiles_;
  int red_tiles_topcolor_;
  int white_tiles_topcolor_;
  int cross_;
  int left;
  int right; 
  
private:
protected:
};

#endif	/* STATISTICS_H */

