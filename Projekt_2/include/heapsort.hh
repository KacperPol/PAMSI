#ifndef HEAPSORT_HH
#define HEAPSORT_HH
#include <iostream>

//Funkcja tworzaca poddrzewo z poczatkiem w indeksie i z tablicy.
//Drzewo reprezentowane jest za pomoca tabicy/wektora.
//Nastepnie odpowiednie poddrzewo jest sortowane.
//-----------------------------------------------------------------
void HeapSortie(std::vector<int> &tab, int n, int i){

  int max = i;
  int left = 2*i + 1;
  int right = 2*i + 2;

  if(left<n && tab[left]> tab[max])
    max = left;
  
  if(right<n && tab[right]>tab[max])
    max = right;

  if(max != i){
    
    int temp = tab[i];
    tab[i] = tab[max];
    tab[max] = temp;

    HeapSortie(tab, n, max); //sortujemy odpowiednie poddrzewo
  }
}

//Wlasciwa funkcja sortowania przez kopcowanie.
//Tworzymy w niej kopiec, nastepnie wywolujemy sortowanie (HeapSortie()).
//-----------------------------------------------------------------
void HeapSort(std::vector<int> &tab){

  int n = tab.size();
  
  for(int i = n/2-1; i >= 0; i--) //tworzymy kopiec
    HeapSortie(tab, n, i);
  
  for(int i = n-1; i >= 0; i--){ //wyciagamy element po elemencie z kopca

    int temp = tab[0];   //
    tab[0] = tab[i]; //ostatnim elementem kopca zastepujemy wiercholek
    tab[i] = temp;   //

    HeapSortie(tab, i, 0); //odtwarzamy porzadek kopca
  }
}

#endif
