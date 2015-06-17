//------------------------------------------------------------------------------
// Tile.h
//
//------------------------------------------------------------------------------
//

#ifndef TILE_H
#define TILE_H

#include "Color.h"
#include <iostream>



//------------------------------------------------------------------------------
// Class for the Tile.
// Clearly defines a tile used in the game by it's type and the top color.
//
class Tile
{
  public:
    
    friend std::ostream& operator<<(std::ostream& stream, Tile &c)
    {
      stream << "Get Color: " << ""<< ", Side: " << c.getSide() << std::endl;
      return stream;
    }
    
    enum Type
    {
      TYPE_CROSS = 1,
      TYPE_CURVE_1 = 2,
      TYPE_CURVE_2 = 3
    };

    //--------------------------------------------------------------------------
    // Class for the colors of all sides of a Tile
    // Contains the colors a tile has in each direction.
    //
    class ColorsOnTile
    {
      public:
        //----------------------------------------------------------------------
        // Default constructor
        ColorsOnTile();

        //----------------------------------------------------------------------
        // Constructor initializing the 4 members
        // @param top The color that is at the top of the tile
        // @param right The color that is to the right of the tile
        // @param bottom The color that is at the bottom of the tile
        // @param left The color that is to the left of the tile
        ColorsOnTile(Color top, Color right, Color bottom, Color left);

        //----------------------------------------------------------------------
        // copy constructor
        ColorsOnTile(const ColorsOnTile &other);

        //----------------------------------------------------------------------
        // Default constructor
        ~ColorsOnTile();

        //----------------------------------------------------------------------
        // getter for the colors
        Color getTop() const;
        Color getLeft() const;
        Color getRight() const;
        Color getBottom() const;

        //----------------------------------------------------------------------
        // setters for color
        void setTop(Color top);
        void setLeft(Color left);
        void setRight(Color right);
        void setBottom(Color bottom);

      private:
        Color top_color_;
        Color right_color_;
        Color bottom_color_;
        Color left_color_;
    };

    //--------------------------------------------------------------------------
    // Constructor for a defined tile
    // @param side What kind of tile it is
    // @param orientation The top color. In combination with the side it clearly
    //   defines the appearance of a tile
    Tile(Type side, Color orientation);
    //--------------------------------------------------------------------------
    // Default destructor
    ~Tile();

    //--------------------------------------------------------------------------
    // getter for the struct to know which colors are at which sides of the tile
    ColorsOnTile getColors();

    //--------------------------------------------------------------------------
    // getter for members.
    Color getTopColor();
    Type getSide();
    //static int getRemainingTiles();
    
    const static int MAXIMUM_TILES;
    
  private:
    Type side_;
    Color top_color_;

    //--------------------------------------------------------------------------
    // private copy constructor
    Tile(const Tile &orig);
};

#endif //TILE_H