/* 
 * File:   Status.h
 * Author: jester
 *
 * Created on June 9, 2015, 12:51 PM
 */

#ifndef STATUS_H
#define	STATUS_H

#include "Command.h"

class Status : public Command
{
public:
  Status();
  virtual ~Status();
  virtual int execute(Game &board, std::vector<std::string> &params);
  virtual unsigned int getParamCnt();
private:

};

#endif	/* STATUS_H */

