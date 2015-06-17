/* 
 * File:   SetTile.h
 * Author: jester
 *
 * Created on June 8, 2015, 6:34 PM
 */

#ifndef SETTILE_H
#define	SETTILE_H


#include "Command.h"
#include "Game.h"

class SetTile : public Command
{
public:
  SetTile();
  virtual ~SetTile();
  virtual int execute(Game &board, std::vector<std::string> &params);
  virtual unsigned int getParamCnt();
private:

};

#endif	/* SETTILE_H */

