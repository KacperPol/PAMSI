#ifndef MACIERZ_HH
#define MACIERZ_HH
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <fstream>
#include <math.h>

#include "lista.hh"

//-----------------------------------------------------------------------
//Klasa grafu na macierzy dziedziczaca po klasie variables
class GraphMat: public variables {
  int **matrix;

public:

  //Funkcja tworzaca pusty graf
  GraphMat() {
    vertex = 0;
    density = 0;
    connections = 0;
  }

  //Funkcja tworzaca graf o danej liczbie wiercholkow i danej gestosci
  GraphMat(int vert, float dens) {
    vertex = vert;
    density = dens;
    connections = density * vertex * (vertex - 1) / 2;

    matrix = new int *[vertex];
    for (int i = 0; i < vertex; i++)
      matrix[i] = new int[vertex];

    for (int i = 0; i < vertex; i++)
      for (int j = 0; j < vertex; j++)
        matrix[i][j] = 0;
  }

  //Funkcja wyswietlajaca graf i jego dane
  void ShowGraph() {
   std::cout << "Twoj graf:" << std::endl;
   std::cout << vertex << " wierzcholkow" << std::endl;
   std::cout << density << " wypelnienia" << std::endl;
   std::cout << connections << " polaczen" << std::endl;

   std::cout << "Macierz wag polaczen: " << std::endl;
    for (int i = 0; i < vertex; i++) {
      for (int j = 0; j < vertex; j++) {
       std::cout << matrix[i][j] << " \t";
      }
     std::cout << "\n";
    }
  }

  //Funkcja wypelniajaca graf
  void FillGraph() {
    int temp = connections;
    srand((int)time(0));
    
    if (density < 1) {
      while (temp) {
        int i = rand() % vertex;
        int j = rand() % vertex;
	if(i != j) {
          if (j > i && !matrix[i][j]) {
            temp--;
            matrix[i][j] = 1 + rand() % 500;
	    matrix[j][i] = matrix[i][j];
          }
          else if (i > j && !matrix[j][i]) {
            temp--;
            matrix[j][i] = 1 + rand() % 500;
	    matrix[i][j] = matrix[j][i];
          }
	}
      }
    }
    else {
      for (int i = 0; i < vertex; i++)
        for (int j = 0; j < vertex; j++)
          if (j > i)
            matrix[i][j] = 1 + rand() % 500;
    }

    int con_new = 0;
    for (int i = 0; i < vertex; i++) {
      for (int j = 0; j < vertex; j++) {
        if (matrix[i][j])
          con_new++;
      }
    }
    connections = con_new;
  }

  //Funkcja usuwajacay caly graf
  void RemoveAll() {
    for (int i = 0; i < vertex; i++)
      for (int j = 0; j < vertex; j++)
        matrix[i][j] = 0;
  }

  //Funkcja dodajaca polaczenie wierzcholkow o danej wartosci w
  void AddCon(int i, int j, int w) {
    if (!matrix[i][j])
      connections++;
    
      matrix[i][j] = w;
      matrix[j][i] = w;
  }

  //Funkcja dodajaca polaczenie wierzcholkow o losowej wartosci
  void AddCon(int i, int j) {
    if (!matrix[i][j])
      connections++;

	matrix[j][i] = 1 + rand() % 500;
	matrix[i][j] = matrix[j][i];
  }

  //Funkcja usuwajaca polaczenie miedzy dwoma wierzcholkami i oraz j
  void RemoveCon(int i, int j) {
    if (matrix[i][j])
      connections--;

      matrix[i][j] = 0;
      matrix[j][i] = 0;
  }

  //Funkcja wykorzystywana przez Complete()
  void Visited(std::vector<bool> &vis, int i) {
    vis[i] = true;

    for (int j = 0; j < vertex; j++)
      if (matrix[i][j] && !vis[j])
        Visited(vis, j);
  }

  //Funkcja sprawdzajaca spojnosc grafu
  bool Complete() {
    bool result = true;
    std::vector<bool> vis;
    for (int i = 0; i < vertex; i++)
      vis.push_back(false);
    Visited(vis, 0);

    for (int i = 0; i < vertex; i++)
      result &= vis[i];

    return result;
  }

  //Funkcja zapisujaca graf do pliku .txt o konkretnej nazwie
  void Save(char *name) {
    std::fstream plik;
    plik.open(name, std::ios::out);
    if (plik.good()) {
      for (int i = 0; i < vertex; i++) {
        for (int j = 0; j < vertex; j++) {
          plik << matrix[i][j] << " ";
        }
        plik << "\n";
      }
      //std::cout << "Zapisano pomyslnie" << std::std::endl;
    } else
      std::cout << "Blad zapisu" << std::endl;

    plik.close();
  }
  
  //Funkcja szybkiego sortowania uzywana przez algorytm Dijkstry
  int Split(std::vector<node> &tab, int first, int last) {
    
    int k = tab[first].len;
    int i = first;
    int j = last;
    int temp = 0;
    
    while(true) {
      while (tab[i].len < k)
        i++;
      
      while (tab[j].len > k)
        j--;
      
      if (i < j) {
        temp = tab[i].nr1;
        tab[i].nr1 = tab[j].nr1;
        tab[j].nr1 = temp;

        temp = tab[i].nr2;
        tab[i].nr2 = tab[j].nr2;
        tab[j].nr2 = temp;

        temp = tab[i].len;
        tab[i].len = tab[j].len;
        tab[j].len = temp;

        i++;
        j--;
      }
     else return j;
    } 
  //   //   for(unsigned int l = 0; l < tab.size(); ++l)
  //   //     std::cout<<tab[l].nr1<<' '; 
  //   //   std::cout<<std::endl;
  }
  
  void QuickSortie(std::vector<node> &tab, int first, int last){
    
    if(first < last){
      int middle = Split(tab, first, last); //dzielenie tablicy na dwie czesci
      QuickSortie(tab, first, middle); //Sortowanie szybkie dla 1.czesci tablicy
      QuickSortie(tab, middle+1, last); //Sortowanie szybkie dla 2.czesci tablicy
    }
  }

  //Funkcja wywolujaca funkcje sortowania
  void Sort(std::vector<node> &tab) {
    if (tab.size())
      QuickSortie(tab, 0, tab.size() - 1);
  }

  //Funkcja wyswietlajaca dane wektora
  void ShowVec(std::vector<int> &v) {
    int k = v.size();

    for (int i = 0; i < k; i++)
      std::cout << i << ".  " << v[i] << std::endl;
    std::cout << "\n";
  }

//========================================================================
  //Algorytm Dijkstry
  int Dijkstra(int vert) {
    // lista odleglosci
    std::vector<int> len;

    for (int i = 0; i < vertex; i++) {
      len.push_back(1000000); // nieskonczonosc
    }
    len[vert] = 0;

    std::vector<node> prior;
    node temp;

    for (int i = 0; i < vertex; i++) {
      temp.len = len[i];
      temp.nr1 = i;
      temp.nr2 = -1;
      prior.push_back(temp);
    }
    Sort(prior);

    do {
      temp = prior[0]; // usun pierwszy element (najmniejsza waga)
      prior.erase(prior.begin());

      for (int i = 0; i < vertex; i++) { // dla wszystkich sasiadow tego
	
        if (matrix[i][temp.nr1])
          if ((len[temp.nr1] + matrix[i][temp.nr1]) < len[i]) {
            len[i] = len[temp.nr1] + matrix[i][temp.nr1];
          }

        if (matrix[temp.nr1][i])
          if ((len[temp.nr1] + matrix[temp.nr1][i]) < len[i]) {
            len[i] = len[temp.nr1] + matrix[temp.nr1][i];
          }
      }

    } while (prior.size());

    std::cout << "Dlugosc najkrotszej drogi od wierzcholka: " << vert << ":" << std::endl;
    ShowVec(len);
    return 0;
  }
//========================================================================
  //Funkcja Relax wykorzystywana przez algorytm Bellmana-Forda
  void Relax(int u, int v, int wage, std::vector<int> &d, std::vector<int> &p) {
    if (d[v] > d[u] + wage) {
      d[v] = d[u] + wage;
      p[v] = u;
    }
  }

//========================================================================
  //Algorytm Bellmana-Forda
  void BellmanFord(int vert) {
    std::vector<int> d; // odleglosci
    std::vector<int> p; // poprzedni

    for (int i = 0; i < vertex; i++) {
      d.push_back(1000001); // nieskonczonosc
      p.push_back(-1); 
    }
    d[vert] = 0;

    std::vector<node> edges; // lista krawedzi
    node temp;

    for (int i = 0; i < vertex; i++)
      for (int j = 0; j < vertex; j++) {
        if (matrix[i][j]) {
          temp.len = matrix[i][j];
          temp.nr1 = i;
          temp.nr2 = j; 
          edges.push_back(temp);
        }
      }

    for (int i = 0; i < vertex; i++) {
      for (unsigned int j = 0; j < edges.size(); j++) {
        Relax(edges[j].nr1, edges[j].nr2, edges[j].len, d, p);
        Relax(edges[j].nr2, edges[j].nr1, edges[j].len, d, p);
      }
    }

    std::cout << "Lisa odleglosci od wierzcholka " << vert << std::endl;
    for (unsigned int i = 0; i < d.size(); i++)
      std::cout << i << ".  " << d[i] << std::endl;
  }
//========================================================================
};

#endif
//------------------------------------------------------------------------
