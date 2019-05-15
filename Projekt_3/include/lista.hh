#ifndef LISTA_HH
#define LISTA_HH

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <fstream>
#include <math.h>

//------------------------------------------------------------------------
//Struktura przechowujaca polaczenie miedzy dwoma wierzcholkami
//(numery wierzcholkow) i wartosc polaczenia.
struct node {
  int nr1;
  int nr2;
  int len;
};
//------------------------------------------------------------------------

//------------------------------------------------------------------------
//Klasa przechowujaca zmienne potrzebne do utworzenia grafu.
class variables {
public:
  int vertex;       //ilosc wierzcholkow
  float density;    //gestosc
  int connections;  //ilosc polaczen
};
//------------------------------------------------------------------------

//------------------------------------------------------------------------
//Klasa grafu na liscie, dziedziczaca po klasie variables
class GraphList: public variables {
  std::vector<std::vector<int>> list; 
  std::vector<std::vector<int>> wage;

public:

  //Funkcja tworzaca pusty graf
  GraphList() {
    vertex = 0;
    density = 0;
    connections = 0;
  }
  
  //Funkcja tworzaca graf o danej liczbie wierzcholkow i danej gestosci
  GraphList(int vert, float dens) {
    vertex = vert;
    density = dens;
    connections = density * vertex * (vertex - 1) / 2;
    std::vector<int> temp;

    for (int i = 0; i < vertex; i++)
      wage.push_back(temp);

    for (int i = 0; i < vertex; i++)
      list.push_back(temp);
  }
  
  //Funkcja wypelniajaca graf
  void FillGraph() {
    int temp = connections;
    int **matrix;
    // srand((int)time(0)); //losowe liczby
    matrix = new int *[list.size()];
    for (int i = 0; i < vertex; i++)
     matrix[i] = new int[vertex]{0};

    if (density < 1) {
      while (temp) {
        int i = rand() % vertex;
        int j = rand() % vertex;
        if (i != j) {
          if (j > i && !matrix[i][j]) {
            temp--;
            matrix[i][j] = 1 + rand() % 500;
          } else if (i > j && !matrix[j][i]) {
            temp--;
            matrix[j][i] = 1 + rand() % 500;
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
    for (int i = 0; i < vertex; i++)
      for (int j = 0; j < vertex; j++) {
        if (matrix[i][j]) {
          con_new++;
          list[i].push_back(j);
          list[j].push_back(i);
          wage[i].push_back(matrix[i][j]);
          wage[j].push_back(matrix[i][j]);
        }
      }
    connections = con_new;
    for (int i = 0; i < vertex; i++)
      delete matrix[i];
    delete matrix;
  }

  //Funkcja usuwajaca/czyszczaca caly graf
  void RemoveAll() {
    for (unsigned int i = 0; i < list.size(); i++) {
      list[i].clear();
      wage[i].clear();
    }
  }

  //Funkcja dodajaca polaczenie wierzcholkow o danej wartosci w
  void AddCon(int i, int j, int w) {
    if (vertex >= i && vertex >= j) {
      bool exist = false;
      for (unsigned int k = 0; k < list[i].size(); k++)
        if (list[i][k] == j)
          exist = true;

      if (!exist) {
        connections++;
        list[i].push_back(j);
        wage[i].push_back(w);

        list[j].push_back(i);
        wage[j].push_back(w);
      }
    }
  }
  
  //Funkcja dodajaca polaczenie wierzcholkow o losowej wartosci
  void AddCon(int i, int j) {
    if (vertex >= i && vertex >= j) {
      bool exist = false;
      for (unsigned int k = 0; k < list[i].size(); k++)
        if (list[i][k] == j)
          exist = true;

      if (!exist) {
        connections++;
        list[i].push_back(j);
        wage[i].push_back(1 + (rand() % 500));
      }
    }
  }

  //Funkcja usuwajaca polaczenie miedzy dwoma wierzcholkami i oraz j
  void RemoveCon(int i, int j) {
    for (unsigned int k = 0; k < list[i].size(); k++) {
      if (list[i][k] == j) {
        list[i].erase(list[i].begin() + k);
        wage[i].erase(wage[i].begin() + k);
      }
    }
    for (unsigned int k = 0; k < list[j].size(); k++) {
      if (list[j][k] == i) {
        list[j].erase(list[j].begin() + k);
        wage[j].erase(wage[j].begin() + k);
      }
    }
  }

  //Funkcja wykorzystywana przez Complete()
  void Visited(std::vector<bool> &vis, int i) {
    vis[i] = true;

    for (unsigned int j = 0; j < list[i].size(); j++) {
      if (!vis[list[i][j]])
        Visited(vis, list[i][j]);
    }
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

  //Funkcja wyswietlajaca graf oraz jego dane
  void ShowGraph() {
    std::cout << "Twoj graf:" << std::endl;
    std::cout << vertex << " wierzcholkow" << std::endl;
    std::cout << density << " wypelnienia" << std::endl;
    std::cout << connections << " polaczen" << std::endl;

    std::cout << " Lista polaczen: " << std::endl;
    for (unsigned int i = 0; i < list.size(); i++) {
      std::cout << i << "|  ";
      for (unsigned int j = 0; j < list[i].size(); j++) {
        std::cout << list[i][j] << " \t";
      }
      std::cout << "\n";
    }

    std::cout << " Lista wag: " << std::endl;
    for (unsigned int i = 0; i < wage.size(); i++) {
      std::cout << i << "|  ";
      for (unsigned int j = 0; j < wage[i].size(); j++) {
        std::cout << wage[i][j] << " \t";
      }
      std::cout << "\n";
    }
  }

  //Funkcja zapisujaca graf do pliku .txt o konkretnej nazwie
  void Save(char *name) {
    std::fstream plik;

    plik.open(name, std::ios::out);
    if (plik.good()) {
      for (int i = 0; i < vertex; i++) {
        for (unsigned int j = 0; j < list[i].size(); j++) {
          plik << i << " " << list[i][j] << " " << wage[i][j] << std::endl;
        }
      }

      //      std::cout << "Zapisano pomyslnie" << std::endl;
    } else
      std::cout << "Blad zapisu" << std::endl;

    plik.close();
  }

  //Funkcja wyswietlajaca dane wektora
  void ShowVec(std::vector<int> &v) {
    int k = v.size();

    for (int i = 0; i < k; i++)
      std::cout << i << ".  " << v[i] << std::endl;
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
  
//========================================================================
  //Algorytm Dijkstry
  int Dijkstra(int vert) {
    std::vector<int> len; //lista odleglosci

    for (int i = 0; i < vertex; i++) {
      len.push_back(1000001); // nieskonczonosc
    }
    len[vert] = 0;

    std::vector<node> prior;
    node temp;

    for (unsigned int i = 0; i < list.size(); i++) {
      temp.len = len[i];
      temp.nr1 = i;
      temp.nr2 = -1;
      prior.push_back(temp);
    }
    
    //BLAD PRAWDOPODOBNIE W TEJ PETLI BADZ W SORTOWANIU
    Sort(prior);
    do {
      temp = prior[0]; // usun pierwszy element (najmniejsza waga)
      prior.erase(prior.begin());

      for (unsigned int i = 0; i < list[temp.nr1].size(); i++) {

	
        if ((len[temp.nr1] + wage[temp.nr1][i]) < len[list[temp.nr1][i]])
          len[list[temp.nr1][i]] = len[temp.nr1] + wage[temp.nr1][i];
      }

    } while (prior.size());
    
    // TU PRAWDOPODOBNIE KONCZY SIE BLAD
    std::cout << "Dlugosc najkrotszej drogi od wierzcholka " << vert << ":" << std::endl;
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

//======================================================================= 
  //Algorytm Bellmana-Forda 
  void BellmanFord(int vert) {
    std::vector<int> d; //odleglosci
    std::vector<int> p; //poprzedni

    for (int i = 0; i < vertex; i++) {
      d.push_back(1000001); //nieskonczonosc
      p.push_back(-1); 
    }
    d[vert] = 0;

    std::vector<node> edges; //lista krawedzi
    node temp;

    for (unsigned int i = 0; i < list.size(); i++)
      for (unsigned int j = 0; j < list[i].size(); j++) {
        temp.len = wage[i][j];
        temp.nr1 = i;
        temp.nr2 = list[i][j];
        edges.push_back(temp);
      }

    for (unsigned int i = 0; i < list.size(); i++) {
      for (unsigned int j = 0; j < edges.size(); j++) {
        Relax(edges[j].nr1, edges[j].nr2, edges[j].len, d, p);
      }
    }
    std::cout << "Lista odleglosci od wierzcholka " << vert << std::endl;
    for (unsigned int i = 0; i < d.size(); i++)
      std::cout << i << ".  " << d[i] << std::endl;
  }
//========================================================================
  
};

#endif
//------------------------------------------------------------------------
