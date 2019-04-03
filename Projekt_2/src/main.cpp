#include <iostream>
#include <cstdlib>
#include <ctime> //biblioteka uzywana do generacji losowych liczb
#include <vector>
#include <chrono> //biblioteka uzywana do zliczania czasu trwania sortowania
#include <fstream> //biblioteka uzywana do zapisywania czasu trwania sortowania do pliku .txt
#include <string>

#include "bubblesort.hh" //sortowanie babelkowe
#include "mergesort.hh" //sortowanie przez scalanie
#include "quicksort.hh" //sortowanie szybkie
#include "heapsort.hh" //sortowanie przez kopcowanie



// Zapelnianie tablicy o rozmiarze n losowymi liczbami od 0 do max
//-----------------------------------------------------------------
void randNumb(std::vector<int> &tab, int max){

  srand((int)time(0));
  int n = tab.size();
  int i = 0;

  // int j = (3*n)/4;
  // int g = i+1;
  // while(j < n){     //Petla uzywana tylko do sprawdzenia pesymistycznego 
  //   tab[j] = g;     //przypadku dla sortowania szybkiego
  //   j++;
  // }
  
  while(i < n) {
    int r = (rand() % max) + 1;
    // std::cout<<i<<std::endl;
    // std::cout<<r<<std::endl;
    tab[i] = r;
    // std::cout<<tab[i]<<std::endl;
    i++;
  }
  
}

//Wypisywanie tablicy o rozmiarze n na terminalu
//-----------------------------------------------------------------
void displayTab(std::vector<int> tab){

  int n = tab.size(), i = 0;
  
  while(i < n) {
    std::cout<<tab[i]<<" ";
    i++;
  }
  std::cout<<std::endl;
}

//-----------------------------------------------------------------
int main(){

  int np, max;
  // std::vector<int> temp1;  //wekor sortowania babelkowego
  std::vector<int> temp2;  //wekor sortowania przez scalanie
  std::vector<int> temp3;  //wekor sortowania szybkiego
  std::vector<int> temp4;  //wekor sortowania przez kopcowanie

  // std::ofstream excel;
  // excel.open("babelkowe.txt"); //utworzenie pliku .txt tylko dla sortowania babelkowego (mniejszy rozmiar tablic, dlatego nie jest testowana z reszta tablic)
  
  // excel<<"nr przebiegu"<<";"<<"potega 10"<<";"<<"liczba elementow"<<";"<<"mergesort\n";
  // excel<<"nr przebiegu"<<";"<<"potega 10"<<";"<<"liczba elementow"<<";"<<"quicksort\n";
  // excel<<"nr przebiegu"<<";"<<"potega 10"<<";"<<"liczba elementow"<<";"<<"heapsort\n";

  std::string file[3] = {"merge.txt", "quick.txt", "heap.txt"};
  std::ofstream excel[3];
  for(int g = 0; g<3; g++){             //utworzenie plikow tekstowych do zapisywania wynikow obliczen dla pozostalych sortowan
    excel[g].open(file[g].c_str());
  }
  
  std::cout<<"Podaj rozmiar tablicy startowej: \n";
  std::cin>>np;
  std::cout<<"Podaj maksymalna liczbe, jaka bedzie mozna wpisac do tablicy: \n";
  std::cin>>max;

  for(int i = 0; i<6; ++i){ //petla zwiekszajaca tablice 10-krotnie od startowej wielkosci //i<7 lub i<6 (?)

    if(i != 0){
      np = np*10;
      // max = max*10; //dodatkowo mozna ustawic, ze maksymalna liczba wpisywana do tablicy, takze bedzie zwiekszana 10-krotnie
    }

    int n = np;
    std::cout<<i+1<<". przebieg - rozpoczety\n";

    for(int j = 0; j<4; ++j){ //petla zwiekszajaca tablice dla skali logarytmiczej np. 10->30->50->70 //j<4

      for(int k = 0; k<3; ++k){ //petla powtarzajaca algorytm sortowania dla takiej samej tablicy, ale roznych danych celem wyciagniecia sredniego czasu wykonywania algorymtu //k<3
	
	// temp1.resize(n); 
	temp2.resize(n);
	temp3.resize(n);    // zmiana rozmiaru tablic/wektorow do wybranej wielkosci przed wpisaniem losowych liczb
	temp4.resize(n);

	// randNumb(temp1, max);
	randNumb(temp2, max);
	randNumb(temp3, max);  //wpisanie losowych liczb do tablic/wektorow
	randNumb(temp4, max);

	// displayTab(temp);

//--------------------------------------------------------------------------------------------------------
	//Sortowanie babelkowe oraz przypadek pesymistyczny dla sortowania szybkiego powinny byc uruchamiane osobno
	//dla mniejszych tablic ze wzgledu na dlugi czas wykonywania algorytmu.
//--------------------------------------------------------------------------------------------------------

	// // =====SORTOWANIE BABELKOWE=====
	// std::cout<<"=====SORTOWANIE BABELKOWE=====\n"<<std::endl;

	// auto start0 = std::chrono::high_resolution_clock::now();  //start pomiaru
	// BubbleSort(temp1);       //pomiar czasu wykonywania algorymtu
	// auto stop0 = std::chrono::high_resolution_clock::now();  //stop pomiaru
	
	// auto duration0 = std::chrono::duration_cast<std::chrono::microseconds> (stop0 - start0); //obliczanie dlugosci wykonywania algorytmu
	// std::cout<<"Czas wykonywania algorytmu sortowania babelkowego: "<<duration0.count()<<"us\n"<<std::endl;
	// // excel<<j+1<<";"<<i+1<<";"<<n<<";"<<duration0.count()<<"\n";

	// displayTab(temp1);

//--------------------------------------------------------------------------------------------------------

	// =====SORTOWANIE PRZEZ SCALANIE=====
	std::cout<<"=====SORTOWANIE PRZEZ SCALANIE====="<<std::endl;

	auto start1 = std::chrono::high_resolution_clock::now(); //start pomiaru
	MergeSort(temp2);     //pomiar czasu wykonywania algorymtu
	auto stop1 = std::chrono::high_resolution_clock::now();  //stop pomiaru
	
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds> (stop1 - start1); //obliczanie dlugosci wykonywania algorytmu
	// std::cout<<"Czas wykonywania algorytmu sortowania przez scalanie: "<<duration1.count()<<"us\n"<<std::endl;
	excel[0]<<j+1<<";"<<i+1<<";"<<n<<";"<<duration1.count()<<"\n";

	// displayTab(temp2);
	
//--------------------------------------------------------------------------------------------------------
	
        // =====SORTOWANIE SZYBKIE=====
        std::cout<<"=====SORTOWANIE SZYBKIE====="<<std::endl;

	auto start2 = std::chrono::high_resolution_clock::now(); //start pomiaru
	QuickSort(temp3);     //pomiar czasu wykonywania algorymtu
	auto stop2 = std::chrono::high_resolution_clock::now();  //stop pomiaru
	
	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds> (stop2 - start2); //obliczanie dlugosci wykonywania algorytmu
	// std::cout<<"Czas wykonywania algorytmu sortowania szybkiego: "<<duration2.count()<<"ms\n"<<std::endl;
	// excel<<i<<";"<<n<<";"<<duration2.count()<<"\n";
	excel[1]<<j+1<<";"<<i+1<<";"<<n<<";"<<duration2.count()<<"\n";

	// displayTab(temp3);
	
// --------------------------------------------------------------------------------------------------------

	//=====SORTOWANIE PRZEZ KOPCOWANIE=====
	std::cout<<"=====SORTOWANIE PRZEZ KOPCOWANIE====="<<std::endl;

	auto start3 = std::chrono::high_resolution_clock::now(); //start pomiaru
	HeapSort(temp4);     //pomiar czasu wykonywania algorymtu
	auto stop3 = std::chrono::high_resolution_clock::now(); //stop pomiaru
	
	auto duration3 = std::chrono::duration_cast<std::chrono::microseconds> (stop3 - start3); //obliczanie dlugosci wykonywania alogrytmu
	// std::cout<<"Czas wykonywania algorytmu sortowania przez kopcowanie: "<<duration3.count()<<"ms\n"<<std::endl;
	excel[2]<<j+1<<";"<<i+1<<";"<<n<<";"<<duration3.count()<<"\n";

	// displayTab(temp4);
	
//--------------------------------------------------------------------------------------------------------
      }
      n = n + np*2;
    }
    std::cout<<i+1<<". przebieg - zakonczony\n";
  }
    for(int g = 0; g<3; g++){
      excel[g].close();  //zamkniecie i zapisanie plikow .txt
    }
  // excel.close(); //zamkniecie i zapisanie pliku txt dla sortowania babelkowego
  return 0;
}
