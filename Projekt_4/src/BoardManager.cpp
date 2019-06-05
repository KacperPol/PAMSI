#include "../include/BoardManager.hpp"

BoardManager* BoardManager::instance = nullptr;

BoardManager* BoardManager::getInstance() {
  
  if(instance == nullptr) {
      
    instance = new BoardManager();
  }
  return instance; 
}

BoardManager::BoardManager() {
  
  resetEverySlotAndSetSize(gameOptionsManager->getBoardSize());
}

void BoardManager::resetEverySlotAndSetSize(const int NEW_BOARD_SIZE)  {
  
  //Ustawienie nowego rozmiaru planszy
  gameOptionsManager->setBoardSize(NEW_BOARD_SIZE);

  //Czyszczenie planszy
  board.clear();
  quantityOfTakenSlots = 0;

  //Zapelnienie tablicy pustymi znakami
  std::vector<char> row;
  for(int i = 0; i < NEW_BOARD_SIZE; i++) {
      
    row.push_back( gameOptionsManager->getCharAssignedTo(Participant::NONE));
  }

  for(int i = 0; i < NEW_BOARD_SIZE; i++) {
      
    board.push_back(row);
  }
}

void BoardManager::resetEverySlot()  {
  
  resetEverySlotAndSetSize(gameOptionsManager->getBoardSize());
}

void BoardManager::resetSlot(const Coordinates& COORDINATES)  {
  
  const bool IS_VALID = (isSlotEmpty(COORDINATES) == false);
  if(IS_VALID) {
      
    board[COORDINATES.getRow()][COORDINATES.getColumn()] = gameOptionsManager->getCharAssignedTo(Participant::NONE);
    quantityOfTakenSlots--;
  }
}

bool BoardManager::addNewCharacter(const Coordinates& COORDINATES, const Participant& PLAYER) {
  
  if ( PLAYER != Participant::HUMAN && PLAYER != Participant::COMPUTER) {
    
    throw std::invalid_argument("Nieprawidlowy gracz.\n");
  }

  const bool IS_VALID = ( isSlotEmpty(COORDINATES) );
  if (IS_VALID) {
    
    const char NEW_CHARACTER = gameOptionsManager->getCharAssignedTo(PLAYER);
    board[COORDINATES.getRow()][COORDINATES.getColumn()] = NEW_CHARACTER;
    quantityOfTakenSlots++;
    return true;
  }
  return false;
}

bool BoardManager::isSlotEmpty(const Coordinates& COORDINATES) const {
  
  return ( board[COORDINATES.getRow()][COORDINATES.getColumn()] == gameOptionsManager->getCharAssignedTo(Participant::NONE) );
}

bool BoardManager::isAnyEmptySlot() const {
  
  return quantityOfTakenSlots < gameOptionsManager->getBoardSize() * gameOptionsManager->getBoardSize();
}

int BoardManager::getQuantityOfTakenSlots() const {
  
  return quantityOfTakenSlots;
}

std::vector<Coordinates> BoardManager::getEveryEmptySlotCoordinates() const {
  
  std::vector<Coordinates> emptySlots;
  const int BOARD_SIZE = gameOptionsManager->getBoardSize();

  for(int row = 0; row < BOARD_SIZE; row++) {      
    for(int col = 0; col < BOARD_SIZE; col++) {
	  
      if( isSlotEmpty(Coordinates(row, col)) ) {
	      
	emptySlots.push_back(Coordinates(row, col));
      }
    }
  }
  return emptySlots;
}

char BoardManager::printcharFromBoard(int i, int j) const {
  return board[i][j];
}

void BoardManager::printBoard() const {
  
  const int BOARD_SIZE = gameOptionsManager->getBoardSize();

  //Wypisanie indeksow nad plansza
  std::cout << "  "; 
  for (int i = 0; i < BOARD_SIZE; i++) {
      
    std::cout << " " << i ;
  }
  std::cout << std::endl;

  //Gorna linia planszy
  std::cout << " +";
  for (int i = 0; i < (2*BOARD_SIZE) +1 ; i++) {
    std::cout << "-";
  }
  std::cout << "+" << std::endl;

  //Srodek planszy
  for (int row = 0; row < BOARD_SIZE; row++) {
      
    std::cout << row << "|";
    for (int col = 0; col < BOARD_SIZE; col++) {
	  
      std::cout << " " << board[row][col];
    }
    std::cout << " |" << std::endl;
  }

  //Dolna linia planszy
  std::cout << " +";
  for (int i = 0; i < (2*BOARD_SIZE) +1 ; i++) {
      
    std::cout << "-";
  }
  std::cout << "+" << std::endl;
}

Participant BoardManager::findWinner() const {
  
  const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
  const int BOARD_SIZE = gameOptionsManager->getBoardSize();

  //Brak zwyciezcy przy takiej ( getQuantityOfTakenSlots() < (2 * POINTS_REQUIRED_FOR_VICTORY)-1 ) liczbie zajetych miejsc
  if( getQuantityOfTakenSlots() < (2 * POINTS_REQUIRED_FOR_VICTORY)-1 ) return Participant::NONE; 

  for(int row = 0; row < BOARD_SIZE; row++) {
    for(int col = 0; col < BOARD_SIZE; col++) {
	  
      Coordinates currentSlot(row,col);

      if(isSlotEmpty(currentSlot) == false) { // Wykonaj algorytm tylko jesli miejsce jest wybrane przez jednego z graczy
	//EAST:
	const bool EAST_RESULT = isPossibleToCheckEastSlots(currentSlot);
	if (EAST_RESULT) {
		  
	  if(areEastSlotsNotEmpty(currentSlot)) {
		      
	    if(areEastSlotsContainWinState(currentSlot)) {
			  
	      return gameOptionsManager->getEnumAssignedTo(board[row][col]);
	    }
	  }
	}

	//SOUTH:
	const bool SOUTH_RESULT = isPossibleToCheckSouthSlots(currentSlot);
	if(SOUTH_RESULT) {
		  
	  if(areSouthSlotsNotEmpty(currentSlot)) {
		      
	    if(areSouthSlotsContainWinState(currentSlot)) {
			  
	      return gameOptionsManager->getEnumAssignedTo(board[row][col]);
	    }
	  }
	}

	//EAST-SOUTH:
	if(EAST_RESULT && SOUTH_RESULT) {
		  
	  if(areEastSouthSlotsNotEmpty(currentSlot)) {
		      
	    if(areEastSouthSlotsContainWinState(currentSlot)) {
			  
	      return gameOptionsManager->getEnumAssignedTo(board[row][col]);
	    }
	  }
	}

	//WEST-SOUTH:
	const bool WEST_RESULT = isPossibleToCheckWestSlots(currentSlot);
	if(WEST_RESULT && SOUTH_RESULT) {
		  
	  if(areWestSouthSlotsNotEmpty(currentSlot)) {
		      
	    if(areWestSouthSlotsContainWinState(currentSlot)) {
			  
	      return gameOptionsManager->getEnumAssignedTo(board[row][col]);
	    }
	  }
	}
      }
    }
  }
  return Participant::NONE;
}

// EAST:

bool BoardManager::isPossibleToCheckEastSlots(const Coordinates& COORDINATES) const {
  
  return (COORDINATES.getColumn() + gameOptionsManager->getPointsRequiredForVictory()
	  <= 
	  gameOptionsManager->getBoardSize());
}

bool BoardManager::areEastSlotsNotEmpty(const Coordinates& COORDINATES) const {
  
  const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
  const int ROW = COORDINATES.getRow();
  const int COLUMN = COORDINATES.getColumn();

  for(int col = 1; col < POINTS_REQUIRED_FOR_VICTORY; col++) {
      
    if (isSlotEmpty(Coordinates(ROW, COLUMN+col)) == true) {
	  
      return false;
    }
  }
  return true;
}

bool BoardManager::areEastSlotsContainWinState(const Coordinates& COORDINATES) const {
  
  const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
  const int ROW = COORDINATES.getRow();
  const int COLUMN = COORDINATES.getColumn();
  int howManyEqualPairs = 0;

  for(int col = 1; col < POINTS_REQUIRED_FOR_VICTORY; col++) {
      
    if(board[ROW][COLUMN] == board[ROW][COLUMN+col] ) {
	  
      howManyEqualPairs++;
    }
  }
  return howManyEqualPairs == (POINTS_REQUIRED_FOR_VICTORY - 1);
}

// SOUTH:

bool BoardManager::isPossibleToCheckSouthSlots(const Coordinates& COORDINATES) const {
  
  return (COORDINATES.getRow() + gameOptionsManager->getPointsRequiredForVictory()
	  <=
	  gameOptionsManager->getBoardSize());
}

bool BoardManager::areSouthSlotsNotEmpty(const Coordinates& COORDINATES) const {
  
  const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
  const int ROW = COORDINATES.getRow();
  const int COLUMN = COORDINATES.getColumn();

  for(int row = 1; row < POINTS_REQUIRED_FOR_VICTORY; row++) {
      
    if(isSlotEmpty(Coordinates(ROW+row, COLUMN)) == true) {
	  
      return false;
    }
  }
  return true;
}

bool BoardManager::areSouthSlotsContainWinState(const Coordinates& COORDINATES) const {
  
  const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
  const int ROW = COORDINATES.getRow();
  const int COLUMN = COORDINATES.getColumn();
  int howManyEqualPairs = 0;

  for(int row = 1; row < POINTS_REQUIRED_FOR_VICTORY; row++) {
      
    if(board[ROW][COLUMN] == board[ROW+row][COLUMN] ) {
      howManyEqualPairs++;
    }
  }
  return howManyEqualPairs == (POINTS_REQUIRED_FOR_VICTORY - 1);
}

// EAST-SOUTH:

bool BoardManager::areEastSouthSlotsNotEmpty(const Coordinates& COORDINATES) const {
  
  const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
  const int ROW = COORDINATES.getRow();
  const int COLUMN = COORDINATES.getColumn();

  for(int i = 1; i < POINTS_REQUIRED_FOR_VICTORY; i++) {
      
    if(isSlotEmpty(Coordinates(ROW+i, COLUMN+i)) == true) {
	  
      return false;
    }
  }
  return true;
}

bool BoardManager::areEastSouthSlotsContainWinState(const Coordinates& COORDINATES) const {
  
  const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
  const int ROW = COORDINATES.getRow();
  const int COLUMN = COORDINATES.getColumn();

  int howManyEqualPairs = 0;
  for(int i = 1; i < POINTS_REQUIRED_FOR_VICTORY; i++) {
      
    if(board[ROW][COLUMN] == board[ROW+i][COLUMN+i]) {
	  
      howManyEqualPairs++;
    }
  }
  return howManyEqualPairs == (POINTS_REQUIRED_FOR_VICTORY - 1);
}

// WEST-SOUTH:

bool BoardManager::isPossibleToCheckWestSlots(const Coordinates& COORDINATES) const {
  
  return (COORDINATES.getColumn() - gameOptionsManager->getPointsRequiredForVictory() >= -1
	  && 
	  COORDINATES.getColumn() < gameOptionsManager->getBoardSize());
}

bool BoardManager::areWestSouthSlotsNotEmpty(const Coordinates& COORDINATES) const {
  
  const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
  const int ROW = COORDINATES.getRow();
  const int COLUMN = COORDINATES.getColumn();

  for(int i = 1; i < POINTS_REQUIRED_FOR_VICTORY; i++) {
      
    if(isSlotEmpty(Coordinates(ROW+i, COLUMN-i)) == true) {
      return false;
    }
  }
  return true;
}

bool BoardManager::areWestSouthSlotsContainWinState(const Coordinates& COORDINATES) const {
  
  const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
  const int ROW = COORDINATES.getRow();
  const int COLUMN = COORDINATES.getColumn();
  int howManyEqualPairs = 0;

  for(int i = 1; i < POINTS_REQUIRED_FOR_VICTORY; i++) {
      
    if(board[ROW][COLUMN] == board[ROW+i][COLUMN-i]) {
	  
      howManyEqualPairs++;
    }
  }
  return howManyEqualPairs == (POINTS_REQUIRED_FOR_VICTORY - 1);
}
