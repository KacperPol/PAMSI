#ifndef BUBBLESORT_HH
#define BUBBLESORT_HH
#include <iostream>

//Funkcja sortowania babelkowego. Przyjmuje wektor z danymi.
//Funkcja sprawdza po kolei, ktory z sasiadujacych
//elementow jest wiekszy i jesli "lewy jest wiekszy niz prawy" zamienia je miejscami.
//Po przejsciu przez cala tablice, funkcja zaczyna sortowac od poczatku.
//-----------------------------------------------------------------
void BubbleSort(std::vector<int> &tab){

  bool swapped; //flaga sprawdzajaca czy elementy musza zostac zamienione
  
  for(int i = 0, n = tab.size()-1; i<n; ++i){
    
    swapped = false;

    for(int j = 0, n = tab.size()-i-1; j<n; ++j){
      
      if(tab[j] > tab[j+1]){
	
	int temp = tab[j];
	tab[j] = tab[j+1];
	tab[j+1] = temp;
        
	swapped = true;
      }
    }
    if(swapped == false)
      break;
  }
}

#endif
