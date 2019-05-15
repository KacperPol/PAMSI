#ifndef MENU_HH
#define MENU_HH
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <fstream>
#include <math.h>

#include "lista.hh"
#include "macierz.hh"

//Struktura z danymi uzywana do pomiarow
struct pomiar {
  int v; //ilosc wierzcholkow
  float d; //gestosc
  int t; //czas
};

//Funkcja pokazujaca 
void ShowMenu() {
  std::cout << "\n 1. Dodaj polaczenie" <<std::endl;
  std::cout << " 2. Usun polaczenie" <<std::endl;
  std::cout << " 3. Sprawdz spojnosc grafu" <<std::endl;
  std::cout << " 4. Wyswietl graf z parametrami" <<std::endl;
  std::cout << " 5. Zapisz do pliku .txt" <<std::endl;
  std::cout << " 6. Wypelnij graf" <<std::endl;
  std::cout << " 7. Usun zawartosc grafu" <<std::endl;
  std::cout << "11. Algorytm Dijkstry" <<std::endl;
  std::cout << "12. Algorytm Bellmana-Forda" <<std::endl;
  std::cout << "20. Tryb pomiarow" <<std::endl;
  std::cout << "10. Wyswietl ponownie Menu" <<std::endl;
  std::cout << " 0. Koniec dzialania programu" <<std::endl;
}

//========================================================================

//Funkcja wywolujaca Pomiary algorytmow
void Pomiary(int &a) {

  // srand((int)time(NULL));

  int times = 0; 
  float dens[4] = {0.25, 0.5, 0.75, 1}; //wektor gestosci
  int vert[5] = {10, 50, 100, 500, 1000}; //wektor ilosci wierzcholkow

  std::vector<pomiar> dane1;
  std::vector<pomiar> dane2;
  
  std::vector<int> dur1;
  std::vector<int> dur2;

  std::cout<<"===POCZATEK POMIAROW\n===";
  
  for(int i = 0; i < 5; i++) {   //vert
    for(int j = 0; j < 4; j++) { //dens
      
      do {
	if(a==0) {
	  GraphList grafL(vert[i], dens[j]);
	  grafL.FillGraph();    //wypelnienie grafu losowymi liczbami
	  
	  if(grafL.Complete()){
	    int wierzcholek = rand() % vert[i];
	    
//-----------------------------------------------------------------------
	    
	    //===DIJKSTRA===
	    auto start1 = std::chrono::high_resolution_clock::now(); //start pomiaru
	    grafL.Dijkstra(wierzcholek);
	    auto stop1 = std::chrono::high_resolution_clock::now(); //koniec pomiaru
	    
	    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds> (stop1 - start1); 
	    dur1.push_back(duration1.count());
	    // std::cout<<"djik_czas: "<<duration3.count()<<std::endl;
	    
//-----------------------------------------------------------------------
	    
	    //===BELLMAN-FORD===
	    auto start2 = std::chrono::high_resolution_clock::now(); //start pomiaru
	    grafL.BellmanFord(wierzcholek);
	    auto stop2 = std::chrono::high_resolution_clock::now();  //koniec pomiaru
	    
	    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds> (stop2 - start2);
	    dur2.push_back(duration2.count());
	    // std::cout<<"bell_czas: "<<duration4.count()<<std::endl;
	  
//-----------------------------------------------------------------------
	    times++;  
	  } 
	}
	
	if(a==1) {
	  GraphMat grafM(vert[i], dens[j]);
	  grafM.FillGraph();
	  
	  if(grafM.Complete()) {
	    int wierzcholek = rand() % vert[i];
	    
//-----------------------------------------------------------------------
	    
	    //===DIJKSTRA===
	    auto start1 = std::chrono::high_resolution_clock::now(); //start pomiaru
	    grafM.Dijkstra(wierzcholek);
	    auto stop1 = std::chrono::high_resolution_clock::now(); //koniec pomiaru
	    
	    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds> (stop1 - start1); 
	    dur1.push_back(duration1.count());
	    // std::cout<<"djik_czas: "<<duration3.count()<<std::endl;
	    
//-----------------------------------------------------------------------
	    
	    //===BELLMAN-FORD===
	    auto start2 = std::chrono::high_resolution_clock::now(); //start pomiaru
	    grafM.BellmanFord(wierzcholek);
	    auto stop2 = std::chrono::high_resolution_clock::now();  //koniec pomiaru
	    
	    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds> (stop2 - start2);
	    dur2.push_back(duration2.count());
	    // std::cout<<"bell_czas: "<<duration4.count()<<std::endl;
	      
//-----------------------------------------------------------------------
	    times++;  
	  }
	}	   
      } while (times < 3);
      
      int avr1 = 0, avr2 = 0;
      
      for (int i = 0; i < times; ++i) {
	// std::cout<<"----------"<<std::endl;
	// std::cout<<"petla dur1[i]: "<<dur1[i]<<std::endl;
	// std::cout<<"petla avr1: "<<avr1<<std::endl;
	// std::cout<<"----------"<<std::endl;
	
	avr1+= dur1[i];
	avr2 += dur2[i];
      }
      
      dur1.clear();
      dur2.clear();
      
      pomiar temp1, temp2;
      // std::cout<<"----------"<<std::endl;
      // std::cout<<"avr1: "<<avr1<<std::endl;
      // std::cout<<"times: "<<times<<std::endl;
      // std::cout<<"----------"<<std::endl;
      temp1.t = avr1 / times;
      temp1.d = dens[j];
      temp1.v = vert[i];
      dane1.push_back(temp1);
      // std::cout<<"wpisano"<<std::endl;
      
      temp2.t = avr2 / times;
      temp2.d = dens[j];
      temp2.v = vert[i];
      dane2.push_back(temp2);
      
      times = 0;
    }
  }
  std::cout<<"===KONIEC POMIAROW\n===";
  
  if(a==0) {
    std::cout<<"_____DIJKSTRA - LISTA_____"<<std::endl;
    for(unsigned int k = 0; k < dane1.size(); k++) {
      std::cout << "Wierzcholki \t" << dane1[k].v << "; \tGestosc \t" << dane1[k].d << "; \tCzas \t" << dane1[k].t << std::endl;
    }
    
    std::cout<<"_____BELLMAN-FORD - LISTA_____"<<std::endl;
    for(unsigned int l = 0; l < dane2.size(); l++) {
      std::cout << "Wierzcholki \t" << dane2[l].v << "; \tGestosc \t" << dane2[l].d << "; \tCzas \t" << dane2[l].t << std::endl;
    }
  }
  
  if(a==1) {
    std::cout<<"_____DIJKSTRA - MACIERZ_____"<<std::endl;
    for(unsigned int k = 0; k < dane1.size(); k++) {
      std::cout << "Wierzcholki \t" << dane1[k].v << "; \tGestosc \t" << dane1[k].d << "; \tCzas \t" << dane1[k].t << std::endl;
    }
    
    std::cout<<"_____BELLMAN-FORD - MACIERZ_____"<<std::endl;
    for(unsigned int l = 0; l < dane2.size(); l++) {
      std::cout << "Wierzcholki \t" << dane2[l].v << "; \tGestosc \t" << dane2[l].d << "; \tCzas \t" << dane2[l].t << std::endl;
    }
  } 
}

//Funkcja wywolujaca opcje Menu
void Menu(int &b, GraphList &grafL, GraphMat &grafM) {

  int option;
  int i, j, w;
  ShowMenu();
  
  do {
    
    std::cout<<"Twoj wybor: ";
    std::cin>>option;

    switch(option) {
    case 1:
    
      std::cout<<"Jakie polaczenie dodac?\n";
      std::cout<<"Wierzcholek 1: ";
      std::cin >> i;
      std::cout<<std::endl;
      std::cout<<"Wierzcholek 2: ";
      std::cin >> j;
      std::cout<<std::endl;
      if (i == j) {
	std::cout<<"Nie ma takiego polaczenia!\n" << std::endl;
	break;
      }
      std::cout<<"O jakiej wadze? ";
      std::cin>>w;
      std::cout<<std::endl;
      if(b==0)
	grafL.AddCon(i, j, w);
      if(b==1)
	grafM.AddCon(i, j, w);
      std::cout<<"Polaczenie dodane!"<<std::endl;
      break;

    case 2:

      std::cout<<"Ktore polaczenie chcesz usunac?\n";
      std::cout<<"Wierzcholek 1: ";
      std::cin>>i;
      std::cout<<std::endl;
      std::cout<<"Wierzcholek 2: ";
      std::cin>>j;
      std::cout<<std::endl;
      if(b==0)
	grafL.RemoveCon(i, j);    
      if(b==1)
	grafM.RemoveCon(i, j);
      std::cout<<"Polaczenie usuniete!"<<std::endl;
      break;

    case 3:

      if(b==0)
	std::cout<<"Twoj graf jest: "<<grafL.Complete()<<std::endl;
      if(b==1)
	std::cout<<"Twoj graf jest: "<<grafM.Complete()<<std::endl;
      break;

    case 4:

      if(b==0)
	grafL.ShowGraph();
      if(b==1)
	grafM.ShowGraph();
      break;
    
    case 5:

      if(b==0)
	grafL.Save(const_cast<char *>("lista_dane.txt"));
      if(b==1)
	grafM.Save(const_cast<char *>("macierz_dane.txt"));
      break;

    case 6:
      
      if(b==0) {
	grafL.RemoveAll();
	grafL.FillGraph();
      }
      if(b==1) {
	grafM.RemoveAll();
	grafM.FillGraph();
      }
      
      break;

    case 7:

      if(b==0)
	grafL.RemoveAll();
      if(b==0)
	grafM.RemoveAll();
      break;

    case 11:

      if(b==0) {
	int x1;
	std::cout<<"Od ktorego wierzcholka? ";
	std::cin>>x1;
	std::cout<<std::endl;
	if(x1 < grafL.vertex && x1 >= 0)
	  grafL.Dijkstra(x1);
	else
	  std::cout<<"Zle dane!"<<std::endl;
      }
      if(b==1) {
	int x2;
	std::cout<<"Od ktorego wierzcholka? ";
	std::cin>>x2;
	std::cout<<std::endl;
	if(x2 < grafM.vertex && x2 >= 0)
	  grafM.Dijkstra(x2);
	else
	  std::cout<<"Zle dane!"<<std::endl;
      }
      break;

    case 12:

      if(b==0) {
	int y1;
	std::cout<<"Od ktorego wierzcholka? ";
	std::cin>>y1;
	if (y1 < grafL.vertex && y1 >= 0)
	  grafL.BellmanFord(y1);
	else
	  std::cout<<"Zle dane!"<<std::endl;
      }
      if(b==1) {
	int y2;
	std::cout<<"Od ktorego wierzcholka? ";
	std::cin>>y2;
	if (y2 < grafM.vertex && y2 >= 0)
	  grafM.BellmanFord(y2);
	else
	  std::cout<<"Zle dane!"<<std::endl;
      }
      break;
      
    case 20:

      int c;
      std::cout<<"Pomiar dla:\n";
      std::cout<<"0 - Listy sasiedztwa\n";
      std::cout<<"1 - Macierzy sasiedztwa\n";
      std::cin>>c;
      Pomiary(c);
      break;

    case 10:

      ShowMenu();
      break;

    default:
      break;
    }
  } while (option != 0);
}

#endif
