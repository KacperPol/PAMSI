#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H

#include <iostream>
#include <vector>

#include "Coordinates.hpp"
#include "GameOptionsManager.hpp"

class BoardManager {
  
  friend class BoardManagerTestSuite;
  
public:
  static BoardManager* getInstance();
  ~BoardManager() {};

  void resetEverySlotAndSetSize(const int NEW_BOARD_SIZE);
  void resetEverySlot();
  void resetSlot(const Coordinates& COORDINATES);

  bool addNewCharacter(const Coordinates& COORDINATES, const Participant& PLAYER);


  void printBoard() const;
  Participant findWinner() const;
  std::vector<Coordinates> getEveryEmptySlotCoordinates() const;
  int getQuantityOfTakenSlots() const;
  bool isAnyEmptySlot() const;
  bool isSlotEmpty(const Coordinates& COORDINATES) const;
  char printcharFromBoard(int i, int j) const;
  
private:

  int quantityOfTakenSlots;
  std::vector<std::vector<char>> board;    
  GameOptionsManager *gameOptionsManager = GameOptionsManager::getInstance();
    
  // Singleton
  static BoardManager *instance;
  BoardManager();
  BoardManager(const BoardManager&) = delete;
  BoardManager& operator=(const BoardManager&) = delete;
 
  // EAST:
  bool isPossibleToCheckEastSlots(      const Coordinates& COORDINATES ) const;
  bool areEastSlotsNotEmpty(            const Coordinates& COORDINATES ) const;
  bool areEastSlotsContainWinState(     const Coordinates& COORDINATES ) const;

  // SOUTH:
  bool isPossibleToCheckSouthSlots(     const Coordinates& COORDINATES ) const;
  bool areSouthSlotsNotEmpty(           const Coordinates& COORDINATES ) const;
  bool areSouthSlotsContainWinState(    const Coordinates& COORDINATES ) const;

  // EAST-SOUTH
  bool areEastSouthSlotsNotEmpty(       const Coordinates& COORDINATES ) const;
  bool areEastSouthSlotsContainWinState(const Coordinates& COORDINATES ) const;

  // WEST-SOUTH:
  bool isPossibleToCheckWestSlots(      const Coordinates& COORDINATES ) const;
  bool areWestSouthSlotsNotEmpty(       const Coordinates& COORDINATES ) const;
  bool areWestSouthSlotsContainWinState(const Coordinates& COORDINATES ) const;
};

#endif
