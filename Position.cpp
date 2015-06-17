//------------------------------------------------------------------------------
// Position.cpp
//
// Group: Group 11591, study assistant Thomas Neff
//
// Authors: Benjamin Franz Herbert Rauch 1431077
// Peter Lorenz 1114658
// Rene Hasenburger 1432147
//------------------------------------------------------------------------------
//

#include "Position.h"
#include <sstream>

const Position Position::INVALID = Position(65, 65);


//------------------------------------------------------------------------------
Position::Position() : x_(0), y_(0)
{
}
//------------------------------------------------------------------------------
Position::Position(int x, int y) : x_(x), y_(y)
{
}
//------------------------------------------------------------------------------
Position::Position(const Position &orig) : x_(orig.getX()), y_(orig.getY())
{
}

//------------------------------------------------------------------------------
Position::~Position()
{
}

//------------------------------------------------------------------------------
int Position::getX() const
{
  return x_;
}
//------------------------------------------------------------------------------
int Position::getY() const
{
  return y_;
}


//------------------------------------------------------------------------------
bool Position::operator==(const Position &other)
{  
  return (other.x_ == x_) && (other.y_ == y_);
}
//------------------------------------------------------------------------------
bool Position::operator!=(const Position &other)
{
  return !(*this == other);
}
//------------------------------------------------------------------------------
bool Position::operator<(const Position &other)
{
  //y =0-126
  //x =0-126
  int this_val = (y_ + 63) * 127 + (x_ + 63);
  int other_val = ((other.getY() + 63) * 127 + (other.getX() * 63));
  return (this_val < other_val);
}
//------------------------------------------------------------------------------
Position::operator bool() const
{
  return x_ < 64 && y_ < 64;
}

//------------------------------------------------------------------------------
bool Position::parse(std::string input)
{
  //preserve
  int x_preserve = x_;
  int y_prexerve = y_;

  std::istringstream is(input);
  char open_bracket;
  char close_bracket;
  char comma;
  std::string s;
  is >> open_bracket >> x_ >> comma >> y_ >> close_bracket >> s;

  if (open_bracket == '(' && close_bracket == ')' && comma == ',' && s == "")
    return true;

  //restore
  x_ = x_preserve;
  y_ = y_prexerve;

  return false;
}

//------------------------------------------------------------------------------
std::string Position::toString() const
{
  std::ostringstream os;
  os << "(" << x_ << "," << y_ << ")";
  return os.str();
}