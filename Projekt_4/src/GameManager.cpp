#include "../include/GameManager.hpp"
#include <SFML/Graphics.hpp>
#include "SFML.hpp"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

#define x 10


const std::string GameManager::EIGHT_SPACE_BARS = "        ";

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::getInstance() {
  
  if(instance == nullptr) {
      
    instance = new GameManager();
  }
  return instance;
}

void GameManager::run() {
  
  std::cout<<"Witaj w grze 'Kolko i krzyzyk'!\n";
  std::cout<<"Przed rozpoczeciem rozgrywki zajrzyj do opcji. Mozesz tam zmienic wielkosc planszy oraz ilosc znakow potrzebna do wygranej.\n";
  std::cout<<"Powodzenia!\n\n";


  MainMenuDecision mainMenuDecision;
  OptionMenuDecision optionsMenuDecision;
  do {
      
    printMainMenu();
    mainMenuDecision = getMainMenuDecision( MyStdIn::readNextIntFromValidScope(1,3) );
    switch (mainMenuDecision) {
	  
    case PLAY:
      gameLoop();
      break;

    case OPTIONS:
      do {		  
	printOptionsMenu();
	optionsMenuDecision = getOptionMenuDecision( MyStdIn::readNextIntFromValidScope(1,5) );
	executeOptionsDecision(optionsMenuDecision);
      }
      
      while (optionsMenuDecision != EXIT_OPTIONS);
      break;

    case EXIT:
      std::cout << "Do zobaczenia!\n";
      break;

    default:
      break;
    }
  } while (mainMenuDecision != EXIT); 
}


void GameManager::printMainMenu() const {
  
  std::cout << "     MENU: \n";
  std::cout << "1.Rozpocznij gre\n";
  std::cout << "2.Opcje\n";
  std::cout << "3.Wyjscie\n";
  std::cout << "Twój wybór: ";
}

GameManager::MainMenuDecision GameManager::getMainMenuDecision(const int DECISION_INDEX) const {
  
  if (DECISION_INDEX < this->MAIN_MENU_FIRST_OPTION_INDEX || DECISION_INDEX > this->MAIN_MENU_LAST_OPTION_INDEX) {
      
    throw std::invalid_argument("Nie rozpoznano znaku w menu!\n");
  }
  return static_cast<GameManager::MainMenuDecision> (DECISION_INDEX);
}


GameManager::OptionMenuDecision GameManager::getOptionMenuDecision(const int DECISION_INDEX) const {
  
  if( DECISION_INDEX < this->OPTION_MENU_FIRST_INDEX || DECISION_INDEX > this->OPTION_MENU_LAST_INDEX) {
      
    throw std::invalid_argument("Nie rozpoznano znaku w opcjach!\n");
  }
  return static_cast<GameManager::OptionMenuDecision> (DECISION_INDEX);
}

void GameManager::gameLoop() {
  
  bool decision;
  do {
      
    Participant winner = displayBoard();
    // Participant winner = playGame();
    boardManager->resetEverySlot();
    printCheers(winner);
    decision = askAndReadToPlayAgain();
  } 
  while (decision == true);
}


Participant GameManager::displayBoard() {

  const int a = gameOptionsManager->getBoardSize();

  // std::cout<<"wielkosc planszy: \n";
  // std::cin>>a;
  
  int b = 70+10*(a-3);
  int c = (a*b)+((a+1)*x);
  int g = b-x*2;
  
  std::string NAZWA = "Blue";
  bool isFirstMove = true;
  bool** checkedOff = new bool*[a];
  bool** checkIfCircle = new bool*[a];
  bool** tabFlag = new bool*[a];

  for(int i=0; i<a; i++) {
    checkedOff[i] = new bool[a];
    checkIfCircle[i] = new bool[a];
    tabFlag[i] = new bool[a];
  }

  sf::Font font;
  if(!font.loadFromFile("arial.ttf")) {
    std::cout<<"ERROR loading font\n";
    system("pause");
  }
  
  bool humanMove;
  bool isEndGame = false;
  // boardManager->printBoard();
  
  for(int i = 0; i<a; i++) {
    for(int j = 0; j<a; j++) {
      
      checkedOff[i][j] = false;
      tabFlag[i][j] = false;
      checkIfCircle[i][j] = false;
    }
  }

  sf::RenderWindow window(sf::VideoMode(c, c), "KOLKO I KRZYZYK", sf::Style::Default);    
  
  //////////Inicjacja lini//////////
  
  sf::RectangleShape line(sf::Vector2f((c-(2*x)), x));

  //============================================================================PRZEROBIC NA WEKTORY!!!!!!!!!!!!!!!!
  
  //////////Inicjacja boxow//////////
  sf::RectangleShape** square = new sf::RectangleShape*[a];
    
  //////////Inicjacja kolka//////////

  sf::CircleShape** circle = new sf::CircleShape*[a];

  for(int i=0; i<a; i++) {
    square[i]  = new sf::RectangleShape[a];
    circle[i]= new sf::CircleShape[a];
  }
  
  Cross cross;
  Coordinates decision(0,0);
  Participant winner;

  
  while (window.isOpen()) {

    sf::Event event;
    
    //////////Petla eventow//////////
    
    while (window.pollEvent(event)) {

      switch(event.type) {
	
      case sf::Event::Closed:

	window.close();
	
	break;
	  	  
      default:
	
	break;
	  
      }
    }

    ////////// KONIEC PETLI EVENTOW//////////

    window.clear(sf::Color::Black);
	
    //////////Rysowanie pionowych lini//////////
      
    line.setPosition(0.f, 0.f);
    line.rotate(90.f);  
    for(int i=1; i<a; i++) {
      line.setPosition(x, 0.f);
      line.move((x+b)*i, x);
      window.draw(line);
    }
      
    //////////Rysowanie poziomych lini//////////
      
    line.setPosition(0.f, x);  
    line.rotate(-90.f);
  
    for(int i=1; i<a; i++) {
      line.setPosition(0.f, 0.f);
      line.move(x, (x+b)*i);
      window.draw(line);
    }

    //////////Rysowanie checkboxow//////////
    
    for(int i=0; i<a; i++) {
      for(int j=0; j<a; j++) {
	square[i][j].setSize(sf::Vector2f(g, g));
	square[i][j].setFillColor(sf::Color::Transparent);
	square[i][j].setPosition(0, 0);  
	square[i][j].move((2*x)+((3*x)+(g))*i, (2*x)+((3*x)+(g))*j);
	window.draw(square[i][j]);
      }
    }

    //////////Rysowanie kolek//////////	    
	    
    for(int i=0; i<a; i++) {
      for(int j=0; j<a; j++) {
		
	if(checkedOff[i][j] && checkIfCircle[i][j]) { //boardManager->printcharFromBoard(i, j) == gameOptionsManager->getCharAssignedTo(Participant::HUMAN)
	  circle[i][j].setRadius((b/2)-x);
	  circle[i][j].setFillColor(sf::Color::Transparent);
	  circle[i][j].setOutlineThickness(-x);
	  circle[i][j].setOutlineColor(sf::Color::Red);
	  circle[i][j].setPosition(0, 0);
	  circle[i][j].move((x*2)+(b+x)*i, (x*2)+(b+x)*j);
	  window.draw(circle[i][j]);
	}
      }
    }

    //////////Rysowanie krzyzykow//////////

    for(int i=0; i<a; i++) {
      for(int j=0; j<a; j++) {

	if(checkedOff[i][j] && !checkIfCircle[i][j]) { //boardManager->printcharFromBoard(i, j) == gameOptionsManager->getCharAssignedTo(Participant::COMPUTER)
	  cross.makeCross(i, j, b);
	  cross.setColor(NAZWA);
	  window.draw(cross.quad1);
	  window.draw(cross.quad2);
	}
      }
    }

    if(!isEndGame) {
      if(isFirstMove) {

	if(gameOptionsManager->getGameStartingPlayer() == Participant::COMPUTER) {
	  humanMove = false;
	  isFirstMove = false;
	  // std::cout<<"1.ruch komputera\n";
	}
	else if(gameOptionsManager->getGameStartingPlayer() == Participant::HUMAN) {
	  humanMove = true;
	  isFirstMove = false;
	  // std::cout<<"1.ruch czlowieka\n";
	}
      }

    
      sf::Vector2f Mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
      
      for(int i=0; i<a; i++) {
	for(int j=0; j<a; j++) {

	  if(!checkedOff[i][j]) {
	  
	    if(square[i][j].getGlobalBounds().contains(Mouse)) {
	    
	      square[i][j].setOutlineThickness(x-3);
	      square[i][j].setOutlineColor(sf::Color::Yellow);
	      window.draw(square[i][j]);
	    
	      if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {	      

		tabFlag[i][j] = true;
		decision.column = i;
		decision.row = j;

		// std::cout<<"col: "<<decision.column<<std::endl<<"row: "<<decision.row<<std::endl;
		// if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		//   // tabFlag[i][j] = false;
		//   std::cout<<"Stop\n";
		// }
	      }
	    }
	  
      
	    if(!square[i][j].getGlobalBounds().contains(Mouse)) {

	      tabFlag[i][j] = false;
	      square[i][j].setOutlineThickness(x-3);
	      square[i][j].setOutlineColor(sf::Color::Transparent);
	      window.draw(square[i][j]); 
	    }
	  }
	
	  else if(checkedOff[i][j]) {

	    square[i][j].setOutlineThickness(x-3);
	    square[i][j].setOutlineColor(sf::Color::Transparent);
	    window.draw(square[i][j]);
	  }      
	}
      }

      // std::cout<<"+"<<col<<"+"<<row<<"+\n";
    
      for(int i=0; i<a; i++) {
	for(int j=0; j<a; j++) {

	  if(tabFlag[i][j] == true) {
	  
	    if(humanMove && !sf::Mouse::isButtonPressed(sf::Mouse::Left) && !checkedOff[i][j]) {

	      // std::cout<<"ruch czlowieka \n";
	      humanMove = false;
	      checkedOff[i][j] = true;
	      checkIfCircle[i][j] = true;	    

	      boardManager->addNewCharacter(decision, Participant::HUMAN);

	      // boardManager->printBoard();
        
	      winner = boardManager->findWinner();
	    
	      if ( boardManager->isAnyEmptySlot() == false || winner != Participant::NONE ) {

		isEndGame = true;
		isFirstMove = true;

	      }
	    
	      if(!isEndGame) {
	      
		// tabFlag[i][j] = false;
		// std::cout<<"ruch komputera \n";
		humanMove = true;
	      
		decision = minMaxManager->executeTheBestComputerMove();
	      
		checkedOff[decision.column][decision.row] = true;
		checkIfCircle[decision.column][decision.row] = false;
	      
		// boardManager->printBoard();
	      
		winner = boardManager->findWinner();
	      
		if (boardManager->isAnyEmptySlot() == false || winner != Participant::NONE) {
		
		  isEndGame = true;
		  isFirstMove = true;
		
		}
	      }
	    }
	  }
	}
      }
    }

    if(isEndGame) {

      //inicjalizjaca koncowych napisow
      sf::Text text;
      
      text.setFont(font);
      text.setString("KONIEC GRY");
      text.setCharacterSize(b/2);
      text.setFillColor(sf::Color::Green);

      sf::Text subtext;

      subtext.setFont(font);
      
      if(winner == Participant::HUMAN)
	subtext.setString("WYGRAL: GRACZ");
      else if(winner == Participant::COMPUTER)
	subtext.setString("WYGRAL: KOMPUTER");
      else if(winner == Participant::NONE)
	subtext.setString("REMIS!");
	subtext.setCharacterSize(b/4);
	subtext.setFillColor(sf::Color::Yellow);
      
      //centrowanie tekstu
      sf::FloatRect textRect = text.getLocalBounds();
      text.setOrigin(textRect.left + textRect.width/2.0f,
		     textRect.top + textRect.height/2.0f);
      text.setPosition(sf::Vector2f(c/2.0f,c/2.0f));

      sf::FloatRect subtextRect = subtext.getLocalBounds();
      subtext.setOrigin(subtextRect.left + subtextRect.width/2.0f,
		     subtextRect.top + subtextRect.height/2.0f);
      subtext.setPosition(sf::Vector2f(c/2.0f,(c-g)/2.0f));

      text.setOutlineColor(sf::Color::Red);
      subtext.setOutlineColor(sf::Color::Red);

      text.setOutlineThickness(5);
      subtext.setOutlineThickness(5);
      
      window.draw(text);
      window.draw(subtext);
    }
    
    window.display();	
  }
  
    return winner;
}

Coordinates GameManager::askAndReadValidHumanCoordinatesDecision() const {
  
  int lastValidIndex = gameOptionsManager->getBoardSize()-1;
  int row = 0, column = 0;
  bool isValid = false;

  do {
      
    std::cout << "Numer WIERSZA: ";  
    row = MyStdIn::readNextIntFromValidScope(0, lastValidIndex);

    std::cout << "Numer KOLUMNY: ";
    column = MyStdIn::readNextIntFromValidScope(0, lastValidIndex);

    if (boardManager->isSlotEmpty(Coordinates(row, column))) {
	  
      isValid = true;
    } 
    else {
	  
      isValid = false;
      std::cerr << "ERROR. Wybrane wspolrzedne sa zajete!\n";
      std::cerr << "Wpisz ponownie: \n";
    }
  } 
  while ( isValid == false );

  return Coordinates(row, column);
}

bool GameManager::askAndReadToPlayAgain() const {
  
  std::vector<char> validChars {'T', 't', 'N', 'n'};
  std::cout << "Czy chcesz zagrac ponownie? T/t = Tak lub N/n = Nie\nTwoj wybor: ";
  char enteredChar = MyStdIn::readNextCharWithValidation( validChars );

  return (enteredChar == 'T' || enteredChar == 't') ? true : false;
}

void GameManager::printCheers(const Participant& winner) const {
  
  switch (winner) {
      
  case Participant::HUMAN:
    std::cout<<  "+========================+\n";
    std::cout << "| Brawo! Wygrana Gracza! |\n";
    std::cout<<  "+========================+\n";
    break;

  case Participant::NONE:
    std::cout<<  "+========+\n";
    std::cout << "| Remis! |\n";
    std::cout<<  "+========+\n";
    break;

  case Participant::COMPUTER:
    std::cout<<  "+=====================================+\n";
    std::cout << "| Wygrana Komputera! Sprobuj ponownie |\n";
    std::cout<<  "+=====================================+\n";
    break;

  default:
    break;
  }
}

void GameManager::printOptionsMenu() const {
  
  std::string gameStartingplayer = "";
  (gameOptionsManager->getGameStartingPlayer() == Participant::HUMAN) ? gameStartingplayer = "HUMAN" : gameStartingplayer = "COMPUTER";

  std::cout << "\n" << EIGHT_SPACE_BARS << "Opcje:\n";
  // std::cout << EIGHT_SPACE_BARS << "1. Zamien symbol gracza ( Obecny symbol: Gracz [" 
  // 	    << gameOptionsManager->getCharAssignedTo(Participant::HUMAN) << "] Komputer [" 
  // 	    << gameOptionsManager->getCharAssignedTo(Participant::COMPUTER) << "] )\n";
    
  // std::cout << EIGHT_SPACE_BARS << "2. Wybierz pierwszenstwo rozpoczecia rozgrywki ( Obecnie: " << gameStartingplayer << " )\n";
  std::cout << EIGHT_SPACE_BARS << "3. Zmien rozmiar tablicy ( Obecny rozmiar: " << gameOptionsManager->getBoardSize() << " )\n";
  std::cout << EIGHT_SPACE_BARS << "4. Zmien ilosc znakow potrzebna do wygranej ( Obecna liczba znakow: " << gameOptionsManager->getPointsRequiredForVictory() << " )\n";
  std::cout << EIGHT_SPACE_BARS << "5. Wyjscie\n";
  std::cout << EIGHT_SPACE_BARS << "Twoj wybor: ";
}

void GameManager::executeOptionsDecision(const GameManager::OptionMenuDecision& DECISION) {
  
  const int MIN_BOARD_SIZE = gameOptionsManager->getMinBoardSize();
  const int MAX_BOARD_SIZE = gameOptionsManager->getMaxBoardSize();

  const int MIN_POINTS_FOR_VICTORY = gameOptionsManager->getMinPointsForVictory();
  const int MAX_POINTS_FOR_VICTORY = gameOptionsManager->getBoardSize();

  switch (DECISION) {
	  
  // case SWITCH_SYMBOLS:
  //   gameOptionsManager->switchHumanAndComputerChar();
  //   break;

  // case SWITCH_STARTING_PLAYER:
  //   gameOptionsManager->setGameStartingPlayer(
  // 					      gameOptionsManager->getOppositePlayer(
  // 										    gameOptionsManager->getGameStartingPlayer()
  // 										    )
  // 					      );
  //   break;

  case SET_BOARD_SIZE:
    std::cout << "\n" << EIGHT_SPACE_BARS << EIGHT_SPACE_BARS 
	      << "Minimalny rozmiar tablicy: " << MIN_BOARD_SIZE 
	      << " maksymalny rozmiar tablicy: " << MAX_BOARD_SIZE << "\n";
    std::cout << EIGHT_SPACE_BARS << EIGHT_SPACE_BARS << "Twoj wybor: "; 
    boardManager->resetEverySlotAndSetSize( MyStdIn::readNextIntFromValidScope( MIN_BOARD_SIZE, MAX_BOARD_SIZE ) );
    break;

  case SET_POINTS_FOR_VICTORY:
    std::cout << "\n" << EIGHT_SPACE_BARS << EIGHT_SPACE_BARS 
	      << "Minimalna liczba znakow: " << MIN_POINTS_FOR_VICTORY 
	      << " maksymalna liczba znakow: "<< MAX_POINTS_FOR_VICTORY << "\n";
    std::cout << EIGHT_SPACE_BARS << EIGHT_SPACE_BARS << "Twoj wybor: ";
    gameOptionsManager->setPointsRequiredForVictory( 
						    MyStdIn::readNextIntFromValidScope(MIN_POINTS_FOR_VICTORY, MAX_POINTS_FOR_VICTORY) );
    break;

  case EXIT_OPTIONS:
    break;

  default:
    break;
  }
}


//=============================================================
//POPRZEDNIA FUNKCJA ODPOWIEDZIALNA ZA ROZGRYWKE PRZEZ TERMINAL
//=============================================================

// Participant GameManager::playGame() {
  
//   Coordinates decision(0,0);
//   Participant winner;
//   boardManager->printBoard();

//   if (gameOptionsManager->getGameStartingPlayer() == Participant::COMPUTER) {
      
//     std::cout << "\nComputer move:\n";
//     minMaxManager->executeTheBestComputerMove();
//     boardManager->printBoard();
//   }

//   while (true) {
      
//     std::cout << "(Playing as: [" << gameOptionsManager->getCharAssignedTo(Participant::HUMAN) 
// 	      << "], Points for win: [" << gameOptionsManager->getPointsRequiredForVictory() 
// 	      << "]) Your turn: \n";
        
//     decision = askAndReadValidHumanCoordinatesDecision();

//     boardManager->addNewCharacter(decision, Participant::HUMAN);

//     boardManager->printBoard();
        
//     winner = boardManager->findWinner();
//     if ( boardManager->isAnyEmptySlot() == false || winner != Participant::NONE ) {
	  
//       return winner;
//     }
        
//     std::cout << "\nComputer move:\n";

//     minMaxManager->executeTheBestComputerMove();

//     boardManager->printBoard();

//     winner = boardManager->findWinner();
//     if (boardManager->isAnyEmptySlot() == false || winner != Participant::NONE) {
	  
//       return winner;
//     }
//   }
// }
