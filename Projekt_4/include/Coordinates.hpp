#ifndef COORDINATES_H
#define COORDINATES_H

#include "GameOptionsManager.hpp"

class Coordinates {
  
public:

  int row;
  int column;

  Coordinates(const int ROW, const int COL);
  
  void operator = (const Coordinates& COORDINATES);
  
  bool equals(const Coordinates& COORDINATES) const;
  
  int getRow() const;
  int getColumn() const;

private:    
  GameOptionsManager *gameOptionsManager = GameOptionsManager::getInstance();
    
};

#endif
