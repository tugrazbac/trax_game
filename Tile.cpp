//------------------------------------------------------------------------------
// Tile.cpp
//
// Group: Group 11591, study assistant Thomas Neff
//
// Authors: Benjamin Franz Herbert Rauch 1431077
// Peter Lorenz 1114658
// Rene Hasenburger 1432147
//------------------------------------------------------------------------------
//

#include "Tile.h"


//Tile::ColorsOnTile from here on
//------------------------------------------------------------------------------
Tile::ColorsOnTile::ColorsOnTile() : top_color_(COLOR_NOT_DEFINED),
  right_color_(COLOR_NOT_DEFINED), bottom_color_(COLOR_NOT_DEFINED),
  left_color_(COLOR_NOT_DEFINED)
{
}

//------------------------------------------------------------------------------
Tile::ColorsOnTile::ColorsOnTile(Color top, Color right, Color bottom,
  Color left) : top_color_(top), right_color_(right), bottom_color_(bottom),
  left_color_(left)
{
}

//------------------------------------------------------------------------------
Tile::ColorsOnTile::ColorsOnTile(const ColorsOnTile &other) :
  top_color_(other.getTop()), right_color_(other.getRight()), 
  bottom_color_(other.getBottom()), left_color_(other.getLeft())
{
}

//------------------------------------------------------------------------------
Tile::ColorsOnTile::~ColorsOnTile()
{
}

//------------------------------------------------------------------------------
Color Tile::ColorsOnTile::getTop() const
{
  return top_color_;
}
//------------------------------------------------------------------------------
 Color Tile::ColorsOnTile::getBottom() const
{
  return bottom_color_;
}
//------------------------------------------------------------------------------
Color Tile::ColorsOnTile::getLeft() const
{
  return left_color_;
}
//------------------------------------------------------------------------------
Color Tile::ColorsOnTile::getRight() const
{
  return right_color_;
}

//------------------------------------------------------------------------------
void Tile::ColorsOnTile::setTop(Color top)
{
  top_color_ = top;
}
//------------------------------------------------------------------------------
void Tile::ColorsOnTile::setBottom(Color bottom)
{
  bottom_color_ = bottom;
}
//------------------------------------------------------------------------------
void Tile::ColorsOnTile::setLeft(Color left)
{
  left_color_ = left;
}
//------------------------------------------------------------------------------
void Tile::ColorsOnTile::setRight(Color right)
{
  right_color_ = right;
}

//from here on Tile class
//------------------------------------------------------------------------------
const int Tile::MAXIMUM_TILES = 64;

//------------------------------------------------------------------------------
Tile::Tile(Tile::Type side, Color orientation) : side_(side),
  top_color_(orientation)
{
}

//------------------------------------------------------------------------------
Tile::~Tile()
{
}

//------------------------------------------------------------------------------
Tile::ColorsOnTile Tile::getColors()
{
  int val_ = static_cast<int>(side_) * 2 + static_cast<int>(top_color_);
  
  switch (val_)
  {
    case 3: //Cross & White
      return { COLOR_WHITE, COLOR_RED, COLOR_WHITE, COLOR_RED };
    case 4: //Cross & Red
      return { COLOR_RED, COLOR_WHITE, COLOR_RED, COLOR_WHITE };
    case 5: //curve_1 & White
      return { COLOR_WHITE, COLOR_RED, COLOR_RED, COLOR_WHITE };
    case 6: //curve_1 & Red
      return { COLOR_RED, COLOR_WHITE, COLOR_WHITE, COLOR_RED };
    case 7: //curve_2 & White
      return { COLOR_WHITE, COLOR_WHITE, COLOR_RED, COLOR_RED };
    case 8: //curve_2 & Red
      return { COLOR_RED, COLOR_RED, COLOR_WHITE, COLOR_WHITE };
    default: //should never happen
      return { COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED };
  }
}

//------------------------------------------------------------------------------
Tile::Type Tile::getSide()
{
  return side_;
}

//------------------------------------------------------------------------------
Color Tile::getTopColor()
{
  return top_color_;
}

