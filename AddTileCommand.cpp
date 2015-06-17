//------------------------------------------------------------------------------
// AddTileCommand.cpp
//
// Group: Group 11591, study assistant Thomas Neff
//
// Authors: Benjamin Franz Herbert Rauch 1431077
// Peter Lorenz 1114658
// Rene Hasenburger 1432147
//------------------------------------------------------------------------------
//

#include "AddTileCommand.h"
#include "Position.h"
#include "Game.h"
#include "Tile.h"
#include "Exceptions.h"

#include "iostream"

//------------------------------------------------------------------------------
// Compares two colors and returns the to integer converted value it if they are
// equal, otherwise it's 0
// @param col1 color 1 to be compared
// @param col2 color 2 to be compared
// @return Integer 0 if not equal, otherwise the converted value.
int compCol(Color col1, Color col2)
{
  if (col1 == col2)
    return static_cast<int>(col1);
  return 0;
}


//------------------------------------------------------------------------------
unsigned int AddTileCommand::getParamCnt()
{
  return 2;
}

//------------------------------------------------------------------------------
int AddTileCommand::execute(Game &board, std::vector<std::string> &params)
{
  Position pos;
  
  //check number of parameters and (if available) evaluate first parameter
  if (params.size() != 2 || !pos.parse(params.at(0)))
  {    
    throw TraxException(TraxException::INVALID_PARAMS);
  }

  //preserve old data in case of screw up
  std::vector<std::vector<Tile *> > game_board = board.getBoard();
  std::pair<Position, Position> min_max_save(
    Position(board.getMinX(), board.getMinY()),
    Position(board.getMaxX(), board.getMaxY()));
  std::vector<Position> buffer;
  buffer.push_back(pos);
  
  //evaluate second parameter
  Tile::Type tile_type;
  std::string tile_type_str = params.at(1);
  if (tile_type_str == "+")
    tile_type = Tile::TYPE_CROSS;
  else if (tile_type_str == "/")
    tile_type = Tile::TYPE_CURVE_1;
  else if (tile_type_str == "\\")
    tile_type = Tile::TYPE_CURVE_2;
  else
  {
    throw TraxException(TraxException::INVALID_PARAMS);
  }

  bool first_tile = board.getStartTile() == nullptr;
  //first tile must be at (0,0)
  if (first_tile && (pos.getX() != 0 || pos.getY() != 0))
  {
    throw TraxException(TraxException::POSITION_MUST_BE_ZERO);
  }

  //check if space is taken
  if (board.getTileAtPosition(pos) != nullptr)
  {
    throw TraxException(TraxException::FIELD_NOT_FREE);
  }
  
  Tile *tile_pointer;
  //handle first tile because further calculations are not related to it
  if (first_tile)
  {
    tile_pointer = new Tile(tile_type, Color::COLOR_RED);
    board.setStartTile(tile_pointer);
    board.setTileAtPosition(pos, tile_pointer);
    board.togglePlayer();
    return 1;
  }

  //get neighboring tiles
  Tile *above = board.getTileAtPosition(pos.getX(), pos.getY() - 1);
  Tile *right = board.getTileAtPosition(pos.getX() + 1, pos.getY());
  Tile *below = board.getTileAtPosition(pos.getX(), pos.getY() + 1);
  Tile *left = board.getTileAtPosition(pos.getX() - 1, pos.getY());

  //if there are none, error
  if (above == nullptr && right == nullptr && 
    below == nullptr && left == nullptr)
  {
    throw TraxException(TraxException::FIELD_NOT_CONNECTED);
  }

  //get the colors that point to the tile to place
  Tile::ColorsOnTile colors_for_tile;
  if (above != nullptr)
    colors_for_tile.setTop(above->getColors().getBottom());
  if (right != nullptr)
    colors_for_tile.setRight(right->getColors().getLeft());
  if (below != nullptr)
    colors_for_tile.setBottom(below->getColors().getTop());
  if (left != nullptr)
    colors_for_tile.setLeft(left->getColors().getRight());

  //calculate top color
  int top_color_integer;
  switch (tile_type)
  {
    case Tile::TYPE_CROSS:
      top_color_integer = colors_for_tile.getTop() |
        Game::getInvertedColor(colors_for_tile.getRight()) |
        colors_for_tile.getBottom() |
        Game::getInvertedColor(colors_for_tile.getLeft());
      break;
    case Tile::TYPE_CURVE_1:
      top_color_integer = colors_for_tile.getTop() |
        Game::getInvertedColor(colors_for_tile.getRight()) |
        Game::getInvertedColor(colors_for_tile.getBottom()) |
        colors_for_tile.getLeft();
      break;
    case Tile::TYPE_CURVE_2:
      top_color_integer = colors_for_tile.getTop() |
        colors_for_tile.getRight() |
        Game::getInvertedColor(colors_for_tile.getBottom()) |
        Game::getInvertedColor(colors_for_tile.getLeft());
      break;
  }

  //if top color is red AND white...
  if (top_color_integer == COLOR_MISMATCH)
  {
    throw TraxException(TraxException::CONNECTED_LINES_MISMATCH);
  }
  //should't happen at this point but if no top color found...
  else if (top_color_integer == COLOR_NOT_DEFINED)
  {
    throw TraxException(TraxException::FIELD_NOT_CONNECTED);
  }

  tile_pointer = new Tile(tile_type, static_cast<Color>(top_color_integer));
  board.setTileAtPosition(pos, tile_pointer);
  
  try
  {
    int pt = 1; //placed tiles
    pt += checkAdditionalTiles(board, pos.getX(), pos.getY() - 1, buffer);
    pt += checkAdditionalTiles(board, pos.getX() + 1, pos.getY(), buffer);
    pt += checkAdditionalTiles(board, pos.getX(), pos.getY() + 1, buffer);
    pt += checkAdditionalTiles(board, pos.getX() - 1, pos.getY(), buffer);

    for (Position &pos_buffered : buffer)
    {
      if (board.checkForWin(pos_buffered))
        break;
    }
    board.checkForDraw();

    board.togglePlayer();
    return pt;
  }
  catch (TraxException &ex)
  {
    //run out of tiles or mismatch.
    if (ex.getErrorType() == TraxException::NOT_ENOUGH_TILES_LEFT ||
      ex.getErrorType() == TraxException::CONNECTED_LINES_MISMATCH)
    {
      //reset board.
      for (Position &pos : buffer)
        delete board.getTileAtPosition(pos);
      board.overwriteBoard(game_board);
      board.forceMinMax(min_max_save.first, min_max_save.second);
    }
    //pass exception on
    throw ex;
  }
}

//------------------------------------------------------------------------------
int AddTileCommand::checkAdditionalTiles(Game &board, int x, int y, 
  std::vector<Position> &buffer)
{
  //field to check already taken.
  if (board.getTileAtPosition(x, y) != nullptr)
    return 0;

  //get neighboring tiles
  Tile *above = board.getTileAtPosition(x, y - 1);
  Tile *right = board.getTileAtPosition(x + 1, y);
  Tile *below = board.getTileAtPosition(x, y + 1);
  Tile *left  = board.getTileAtPosition(x - 1, y);
  
  //get the colors that point to the tile to place
  Tile::ColorsOnTile col_for_t;
  if (above != nullptr)
    col_for_t.setTop(above->getColors().getBottom());
  if (right != nullptr)
    col_for_t.setRight(right->getColors().getLeft());
  if (below != nullptr)
    col_for_t.setBottom(below->getColors().getTop());
  if (left != nullptr)
    col_for_t.setLeft(left->getColors().getRight());
  
  int combined;

  //if top and bottom are the same = cross
  if ((combined = compCol(col_for_t.getTop(), col_for_t.getBottom())))
    board.setTileAtPosition(Position(x, y),
    new Tile(Tile::TYPE_CROSS, static_cast<Color>(combined)));
  //if top and bottom are the same = cross (but result color inverted)
  else if ((combined = compCol(col_for_t.getRight(), col_for_t.getLeft())))
    board.setTileAtPosition(Position(x, y),
    new Tile(Tile::TYPE_CROSS, static_cast<Color>(combined ^ 3)));

  //if top and left are the same = curve_1
  else if ((combined = compCol(col_for_t.getTop(), col_for_t.getLeft())))
    board.setTileAtPosition(Position(x, y),
    new Tile(Tile::TYPE_CURVE_1, static_cast<Color>(combined)));
  
  //if right and bottom are the same = curve_1 (but result color inverted)
  else if ((combined = compCol(col_for_t.getRight(), col_for_t.getBottom())))
    board.setTileAtPosition(Position(x, y),
    new Tile(Tile::TYPE_CURVE_1, static_cast<Color>(combined ^ 3)));

  //if top and right are the same = curve_2
  else if ((combined = compCol(col_for_t.getTop(), col_for_t.getRight())))
    board.setTileAtPosition(Position(x, y),
    new Tile(Tile::TYPE_CURVE_2, static_cast<Color>(combined)));
  //if left and bottom are the same = curve_2 (but result color inverted)
  else if ((combined = compCol(col_for_t.getLeft(), col_for_t.getBottom())))
    board.setTileAtPosition(Position(x, y),
    new Tile(Tile::TYPE_CURVE_2, static_cast<Color>(combined ^ 3)));
  
  //not clearly defined
  else
    return 0;

  //col_for_t = color of the paths that are leading to the tile
  //col_for_s = color of the paths of the tile itself.
  Tile::ColorsOnTile col_for_s = board.getTileAtPosition(x, y)->getColors();

  if (col_for_s.getTop() + col_for_t.getTop() == COLOR_MISMATCH ||
    col_for_s.getLeft() + col_for_t.getLeft() == COLOR_MISMATCH ||
    col_for_s.getRight() + col_for_t.getRight() == COLOR_MISMATCH ||
    col_for_s.getBottom() + col_for_t.getBottom() == COLOR_MISMATCH)
  {
    throw TraxException(TraxException::CONNECTED_LINES_MISMATCH);
  }

  if (board.getRemainingTiles() < 0)
  {
    throw TraxException(TraxException::NOT_ENOUGH_TILES_LEFT);
  }

  //one tile added, now check neighbor again
  int placed_tiles = 1;
  placed_tiles += checkAdditionalTiles(board, x, y - 1, buffer);
  placed_tiles += checkAdditionalTiles(board, x + 1, y, buffer);
  placed_tiles += checkAdditionalTiles(board, x, y + 1, buffer);
  placed_tiles += checkAdditionalTiles(board, x - 1, y, buffer);

  return placed_tiles;
}

//------------------------------------------------------------------------------
AddTileCommand::AddTileCommand() : Command("addtile")
{
}

//------------------------------------------------------------------------------
AddTileCommand::~AddTileCommand()
{
}
