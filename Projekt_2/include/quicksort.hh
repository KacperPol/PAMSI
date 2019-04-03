#ifndef QUICKSORT_HH
#define QUICKSORT_HH
#include <iostream>
#include <vector>

//Funkcja Split dzieli tablice na dwie czesci.
//Jedna czesc mniejsza badz rowna tab[first], a druga wieksza od tab[first].
//-----------------------------------------------------------------
int Split(std::vector<int> &tab, int first, int last){

  int k = tab[first];
  int i = first, j = last, temp = 0;
  
  while(true){
    
    while(tab[j] > k)
      j--;
    
    while(tab[i] < k)
      i++;
    
    if(i < j) { //liczby zmieniamy miejscami gdy i < j
      temp = tab[i];
      tab[i] = tab[j];
      tab[j] = temp;
      i++;
      j--;
    }
    else return j;
  }
}

//Wlasciwa funkcja sortowania szybkiego.
//Dzielimy w niej tablice na dwie czesci wedlug zmiennej middle, za pomoca funkcji Split().
//Wywolujemy sortowanie dla czesci tablicy od zmiennej first do middle a nastepnie dla tablicy od zmiennej middle+1 do last.
//-----------------------------------------------------------------
void QuickSortie(std::vector<int> &tab, int first, int last){

  if(first < last){
    int middle = Split(tab, first, last); //dzielenie tablicy na dwie czesci
    QuickSortie(tab, first, middle); //Sortowanie szybkie dla 1.czesci tablicy
    QuickSortie(tab, middle+1, last); //Sortowanie szybkie dla 2.czesci tablicy
  }
}

//Funkcja wywolujaca wlasciwe sortowanie (funkcje QuickSortie()).
//Do funkcji QuickSortie() oprócz tablicy, podajemy także informacje o poczatku (0) i koncu (tab.size()-1).
//-----------------------------------------------------------------
void QuickSort(std::vector<int> &tab){
  int n = tab.size();
  QuickSortie(tab, 0, n-1);
}

#endif
