#include <iostream>

#include "../include/GameManager.hpp"
// #include <SFML/Window.hpp>
// #include <SFML/Graphics.hpp>

int main() {
 
  GameManager *gameManager = GameManager::getInstance();
  gameManager->run();
  
  
  return 0;
}
