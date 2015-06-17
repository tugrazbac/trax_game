/* 
 * File:   DelLast.h
 *
 * Created on June 9, 2015, 10:23 AM
 */

#ifndef DELLAST_H
#define	DELLAST_H
#include "Command.h"

class DelLast : public Command
{
public:
  DelLast();
  virtual ~DelLast();
  virtual int execute(Game &board, std::vector<std::string> &params);
  virtual unsigned int getParamCnt();
private:

};

#endif	/* DELLAST_H */

