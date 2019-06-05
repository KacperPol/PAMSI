#include "../include/MinMaxManager.hpp"

MinMaxManager* MinMaxManager::instance = nullptr;

MinMaxManager* MinMaxManager::getInstance() {
  
  if(instance == nullptr) {
    
    instance = new MinMaxManager();
  }
  return instance;
}

Coordinates MinMaxManager::executeTheBestComputerMove() {
  
  if (boardManager->isAnyEmptySlot() == false) throw;

  const int INITIAL_DEPTH = 0;

  //Jesli komputer zaczyna gre to zostaje wybrane pole (0, 0)
  if (boardManager->getQuantityOfTakenSlots() == 0) {
    
    theBestMoveCoordinates = Coordinates(0,0);
  }
  
  else {
    
    auto start = std::chrono::steady_clock::now();
    calculateTheBestMoveFor(Participant::COMPUTER, INITIAL_DEPTH, this->LOWEST_SCORE, this->HIGHEST_SCORE);
    auto end = std::chrono::steady_clock::now();

    std::cout<<std::endl<< "Czas, ktory uplynal w sekundach: "<<std::chrono::duration_cast<std::chrono::seconds>(end - start).count()<<" s\n";
    std::cout<<"Liczba rekurencyjnych wywolan funkcji: "<<this->howManyFunctionCalls<<std::endl;;
    this->howManyFunctionCalls = 0;
  }

  boardManager->addNewCharacter(theBestMoveCoordinates, Participant::COMPUTER);
  return theBestMoveCoordinates;
}


int MinMaxManager::calculateTheBestMoveFor(const Participant& TURN_TAKING_PLAYER, int currentDepth, int alpha, int beta) {
  
  const int RESULT = scoreGameFromComputerPOV(currentDepth);
  if (RESULT != 0 || (boardManager->isAnyEmptySlot() == false) 
      || currentDepth == gameOptionsManager->getDepthBound(gameOptionsManager->getBoardSize())) {
    
    return RESULT;
  }
    
  this->howManyFunctionCalls++;
  currentDepth++;
  std::vector<Coordinates> availableCoordinates = boardManager->getEveryEmptySlotCoordinates();
  std::vector<int> scores;
  int currentBestScore;

  //Ustalenie mozliwych ruchow i stanow gry celem wykonania najlepszego ruchu
  for(unsigned int i = 0; i < availableCoordinates.size(); i++) {
    
    boardManager->addNewCharacter(availableCoordinates[i], TURN_TAKING_PLAYER);
    const int CURRENT_BOARD_SCORE_FROM_COMPUTER_POV = calculateTheBestMoveFor(gameOptionsManager->getOppositePlayer(TURN_TAKING_PLAYER), currentDepth, alpha, beta);

    scores.push_back(CURRENT_BOARD_SCORE_FROM_COMPUTER_POV);
    boardManager->resetSlot(availableCoordinates[i]);

    // Algorytm alfa ...
    if (TURN_TAKING_PLAYER == Participant::COMPUTER) {
	
      currentBestScore = *std::max_element( std::begin(scores), std::end(scores) ); //std::max_element zwraca najwiekszy element od std::begin do std::end, mozna go zastapic petla, w ktorej wyszukujemy najwiekszego inta z podanego vectora
      
      alpha = std::max(currentBestScore, alpha); // Alpha zapewnia maksymalny zysk dla biezacego stanu (std::max zwraca wartosc wieksza sposrod dwoch podanych, mozna go zastapic zwyklym porownaniem intow)
      if (beta <= alpha) {
	    
	break;
      }  
      // ...beta
    } 
    else {
	
      currentBestScore = *std::min_element( std::begin(scores), std::end(scores) ); //std::min_element zwraca najmniejszy element od std::begin do std::end, mozna go zastapic petla, w ktorej wyszukujemy najwiekszego inta z podanego vectora
      
      beta = std::min(currentBestScore, beta); // Beta zapewnia minimalna strate dla biezacego stanu (std::min zwraca wartosc mniejsza sposrod dwoch podanych, mozna go zastapic zwyklym porownaniem intow)
      if (beta <= alpha) {
	    
	break;
      }
    }
  }

  //W tym miejscu podejmowana jest decyzja
  if(TURN_TAKING_PLAYER == Participant::COMPUTER) { //Komputer wybiera najlepsza sciezke ze swojego punktu widzenia
    
    const int MAX_SCORE_INDEX = getMaxValueIndex(scores);
    if(currentDepth == 1) { //Na koniec wykonujemy tylko jeden ruch mimo sprawdzenia nastepnych
      
      this->theBestMoveCoordinates = availableCoordinates[MAX_SCORE_INDEX]; 
    }
    return scores[MAX_SCORE_INDEX];

  }
  
  else if (TURN_TAKING_PLAYER == Participant::HUMAN) { //Czlowiek celuje w minimalna liczbe punktow z punktu wiedzenia komputera
    
    const int MIN_SCORE_INDEX = getMinValueIndex(scores);
    return scores[MIN_SCORE_INDEX];
  }
  return 0;
}

int MinMaxManager::scoreGameFromComputerPOV(const int DEPTH) const {
  
  const Participant WINNER = boardManager->findWinner();

  if (WINNER == Participant::COMPUTER) {
    
    return HIGHEST_SCORE - DEPTH;
  }
  
  else if (WINNER == Participant::NONE) {
    
    return 0;
  }
  
  else {
    return -HIGHEST_SCORE + DEPTH;
  }
}

int MinMaxManager::getMaxValueIndex(const std::vector<int>& VEC) const {
  
  if ( VEC.size() == 0 ) {
    
    throw std::invalid_argument("Nieprawidlowy argument, rozmiar wektora wynosi zero.\n");
  }

  int result = 0;
  int maxValue = VEC[0];
  for(unsigned int i = 1; i < VEC.size(); i++) {
    
    if(VEC[i] > maxValue) {
	
      maxValue = VEC[i];
      result = i;
    }
  }
  return result;
}

int MinMaxManager::getMinValueIndex(const std::vector<int>& VEC) const  {
  
  if ( VEC.size() == 0 ) {
    
    throw std::invalid_argument("Nieprawidlowy argument, rozmiar wektora wynosi zero.\n");
  }
    
  int result = 0;
  int minValue = VEC[0];
  for(unsigned int i = 1; i < VEC.size(); i++) {
    
    if(VEC[i] < minValue) {
	
      minValue = VEC[i];
      result = i;
    }
  }
  return result;
}
