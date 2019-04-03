#ifndef MERGESORT_HH
#define MERGESORT_HH
#include <iostream>
#include <vector>

//Funkcja Merge scala dwie posortowane tablice (przedzialy) (pierwszy od first do middle, drugi od middle+1 do last).
//-----------------------------------------------------------------
void Merge(std::vector<int> &tab, int first, int middle, int last){

  int i = first, j = middle+1, k = 0, size = (last - first)+1;
  std::vector<int> temp(size);

  while(i <= middle && j <= last){
    
    if(tab[i] <= tab[j])
      temp[k++] = tab[i++];
    
    else
      temp[k++] = tab[j++];
  }
  while(i <= middle)
    temp[k++] = tab[i++];
  
  while(j <= last)
    temp[k++] = tab[j++];
  
  for(k=0, i=first; i<=last; ++i, ++k)
    tab[i] = temp[k];
}

//Wlasciwa funkcja sortowania przez scalanie.
//Dzielimy w niej tablice na dwie czesci wedlug zmiennej middle.
//Nastepnie wywyolujemy sortowanie (MergeSortie()) na obu tablicach (jedna po drugiej).
//Na koniec scalamy je w jedna tablice za pomoca funkcji Merge().
//-----------------------------------------------------------------
void MergeSortie(std::vector<int> &tab, int first, int last){

  if(first < last){  
    int middle = (first + last)/2; //dzielenie tablicy na dwie czesci
    MergeSortie(tab, first, middle); //sortowanie dla 1.czesci tablicy
    MergeSortie(tab, middle+1, last); //sortowanie dla 2.czesci tablicy
    Merge(tab, first, middle, last); //scalanie tablic (przedzialow)
  }
}

//Funkcja wywolujaca wlasciwe sortowanie (funkcje MergeSortie()).
//Do funkcji MergeSortie() oprócz tablicy, podajemy także informacje o poczatku (0) i koncu (tab.size()-1).
//-----------------------------------------------------------------
void MergeSort(std::vector<int> &tab){
  int n = tab.size();
  MergeSortie(tab, 0, n-1);
}

#endif
