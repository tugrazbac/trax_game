/* 
 * File:   Reset.h
 * Author: jester
 *
 * Created on June 9, 2015, 12:42 PM
 */

#ifndef RESET_H
#define	RESET_H

#include "Command.h"
#include "Game.h"

class Reset : public Command
{
public:
  Reset();
  virtual ~Reset();
  virtual int execute(Game &board, std::vector<std::string> &params);
  virtual unsigned int getParamCnt();
private:

};

#endif	/* RESET_H */

