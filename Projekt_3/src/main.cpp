#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <fstream>
#include <math.h>
#include <chrono>

#include "lista.hh"
#include "macierz.hh"
#include "menu.hh"

int main() {

  int vertex;
  float density;
  int a;
  
  std::cout<<"Podaj liczbe wierzcholkow: "<<std::endl;
  std::cin>>vertex;

  std::cout<<"Podaj gestosc wypelnienia grafu (od 0.0 do 1.0): "<<std::endl;
  std::cin>>density;

  std::cout<<"Graf na liscie sasiedztwa (wybierz 0)\n"<<"Graf na macierzy sasiedztwa (wybierz 1)\n";
  std::cin>>a;

  GraphList grafL(vertex, density);
  GraphMat grafM(vertex, density);
    
  Menu(a, grafL, grafM);
  
  return 0;
}
