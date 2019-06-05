#include "../include/Coordinates.hpp"


Coordinates::Coordinates(const int ROW, const int COL) {
  
  if (ROW < 0 ||
      COL < 0 || 
      ROW >= gameOptionsManager->getBoardSize() || 
      COL >= gameOptionsManager->getBoardSize()) {
      
    throw std::invalid_argument("Nieprawidlowe wspolrzedne. Proba postawienia znaku na miejscu WIERSZ: " 
				+ std::to_string(ROW) + " i KOLUMNA: " + std::to_string(COL) + "\n");
  }
  row = ROW;
  column = COL;
}

int Coordinates::getRow() const {
  
  return row;
}

int Coordinates::getColumn() const {
  
  return column;
}

bool Coordinates::equals(const Coordinates& COORDINATES) const {
  
  return (row == COORDINATES.getRow() && column == COORDINATES.getColumn());
}

void Coordinates::operator = (const Coordinates& COORDINATES) {
  
  row = COORDINATES.getRow();
  column = COORDINATES.getColumn();
}
