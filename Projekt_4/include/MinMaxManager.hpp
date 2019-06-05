#ifndef MINMAX_MANAGER_H
#define MINMAX_MANAGER_H

#include "BoardManager.hpp"
#include <algorithm> //dla funkcji std::max
#include <chrono>  //do obliczania czasu wykonania algorytmu

class MinMaxManager {
  
  friend class MinMaxManagerTestSuite;
  
public:
  static MinMaxManager* getInstance();
  ~MinMaxManager() {};
    
  Coordinates executeTheBestComputerMove();

private:
  int howManyFunctionCalls = 0;
  const int HIGHEST_SCORE = 1000;
  const int LOWEST_SCORE = -1000; 

  Coordinates theBestMoveCoordinates; 

  GameOptionsManager *gameOptionsManager = GameOptionsManager::getInstance();
  BoardManager *boardManager = BoardManager::getInstance();
    
  // Singleton
  static MinMaxManager *instance;
  MinMaxManager() : theBestMoveCoordinates(0,0) {}
  MinMaxManager(const MinMaxManager&) = delete;
  MinMaxManager& operator=(const MinMaxManager&) = delete;
    
  int calculateTheBestMoveFor(const Participant& TURN_TAKING_PLAYER, int depth, int alpha, int beta);

  int scoreGameFromComputerPOV(const int DEPTH) const; 
  int getMaxValueIndex(const std::vector<int>& VEC) const;
  int getMinValueIndex(const std::vector<int>& VEC) const;
};

#endif
