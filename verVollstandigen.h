/* 
 * File:   verVollstandigen.h
 * Author: jester
 *
 * Created on June 7, 2015, 4:26 PM
 */

#ifndef VERVOLLSTANDIGEN_H
#define	VERVOLLSTANDIGEN_H

#include "Command.h"


class verVollstandigen : public Command
{
public:
  verVollstandigen();
  verVollstandigen(const verVollstandigen& orig);
  virtual ~verVollstandigen();
  
  virtual int execute(Game &board, std::vector<std::string> &params);
  
  virtual unsigned int getParamCnt();

  
private:

};

#endif	/* VERVOLLSTANDIGEN_H */

