#ifndef SFML_H
#define SFML_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

#include "Coordinates.hpp"
#include "GameOptionsManager.hpp"
#include "BoardManager.hpp"
#include "GameManager.hpp"
#include "MinMaxManager.hpp"
#include "MyStdIn.hpp"

#define x 10


class Cross {

public:
  
  sf::VertexArray quad1;
  sf::VertexArray quad2;

  void makeCross1(int i, int j, int b) {

    quad1.resize(4);
    quad1.setPrimitiveType(sf::Quads);
    quad1[0].position = sf::Vector2f((2*x)+(b+x)*i, (2*x)+(b+x)*j);
    quad1[1].position = sf::Vector2f((3*x)+(b+x)*i, (2*x)+(b+x)*j);
    quad1[2].position = sf::Vector2f(b+(b+x)*i, b+(b+x)*j);
    quad1[3].position = sf::Vector2f((b-x)+(b+x)*i, b+(b+x)*j);

    for(int k = 0; k < 4; k++)
      quad1[k].color = sf::Color::Transparent;
    // return quad1;
  }
  
  void makeCross2(int i, int j, int b) {

    quad2.resize(4);
    quad2.setPrimitiveType(sf::Quads);
    quad2[0].position = sf::Vector2f((b)+(b+x)*i, (2*x)+(b+x)*j);
    quad2[1].position = sf::Vector2f((b-x)+(b+x)*i, (2*x)+(b+x)*j);
    quad2[2].position = sf::Vector2f((2*x)+(b+x)*i, b+(b+x)*j);
    quad2[3].position = sf::Vector2f((3*x)+(b+x)*i, b+(b+x)*j);

    for(int k = 0; k < 4; k++)
      quad2[k].color = sf::Color::Transparent;

    // return quad2;
  }
  
  void makeCross(int i, int j, int b) {
    
    makeCross1(i, j, b);
    makeCross2(i, j, b);
  }

  void setColor(std::string NAZWA) {

    if(NAZWA == "Blue") {
      for(int k = 0; k < 4; k++)
	quad1[k].color = sf::Color::Blue;
      
      for(int k = 0; k < 4; k++)
	quad2[k].color = sf::Color::Blue;
    }
  }
};


#endif
