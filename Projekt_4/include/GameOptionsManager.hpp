#ifndef GAME_OPTIONS_MANAGER_H
#define GAME_OPTIONS_MANAGER_H

#include <string>
#include <stdexcept>


class GameOptionsManager {
  
public:
  enum GameParticipant {
    
    COMPUTER = -1, NONE = 0, HUMAN = 1
  };

  static GameOptionsManager* getInstance();
  ~GameOptionsManager() {};
    
  void switchHumanAndComputerChar();

  void setPointsRequiredForVictory(const int NEW_POINTS);
  void setBoardSize(const int NEW_BOARD_SIZE);
  void setGameStartingPlayer(const GameParticipant& PLAYER);

  int getPointsRequiredForVictory() const;
  int getBoardSize() const;

  int getMinBoardSize() const;
  int getMaxBoardSize() const;

  int getMinPointsForVictory() const;
  int getMaxPointsForVictory() const;

  int getDepthBound(const int BOARD_SIZE) const;

  char getCharAssignedTo(const GameParticipant& PLAYER) const;

  GameParticipant getEnumAssignedTo(const char CHAR) const;
  GameParticipant getOppositePlayer(const GameParticipant& PLAYER) const;
  GameParticipant getGameStartingPlayer() const;

private:
  const char EMPTY_SLOT_CHAR = '-';
  const char DEFAULT_HUMAN_CHAR = 'O';
  const char DEFAULT_COMPUTER_CHAR = 'X';

  const int MIN_BOARD_SIZE = 3;
  const int MAX_BOARD_SIZE = 10;

  const int MIN_POINTS_FOR_VICTORY = 3;

  const int DEPTH_BOUND_3x3 = 9;
  const int DEPTH_BOUND_4x4 = 9; 
  const int DEPTH_BOUND_5x5 = 7;
  const int DEPTH_BOUND_6x6 = 6;
  const int DEPTH_BOUND_7x7 = 5;
  const int DEPTH_BOUND_8x8 = 5;
  const int DEPTH_BOUND_9x9 = 4;
  const int DEPTH_BOUND_10x10 = 4;

  GameParticipant gameStartingPlayer = GameParticipant::HUMAN;

  int pointsRequiredForVictory = MIN_POINTS_FOR_VICTORY;
  int boardSize = MIN_BOARD_SIZE;

  char humanChar = DEFAULT_HUMAN_CHAR;
  char computerChar = DEFAULT_COMPUTER_CHAR;

  // Singleton
  static GameOptionsManager *instance;
  GameOptionsManager() {};
  GameOptionsManager(const GameOptionsManager&) = delete;
  GameOptionsManager& operator=(const GameOptionsManager&) = delete;
};

typedef GameOptionsManager::GameParticipant Participant;

#endif
