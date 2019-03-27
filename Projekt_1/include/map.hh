#ifndef MAP_HH
#define MAP_HH
#include <iostream>
#include <string>

#define SIZE 30 //wielkosc hashmapy

//===HASH MAPA===

//Funkcja Hashujaca dla klucza typu int
//----------------------------------------------------------------
template <typename KeyType> int HashFunc(KeyType key);
template <> int HashFunc<int> (int key){

  // int a = key % SIZE;
  // std::cout<<"WWW"<<a<<std::endl;
  return key % SIZE;
}

//Funkcja Hashujaca dla klucza typu string
//----------------------------------------------------------------
template <typename KeyType> int HashFunc(KeyType key);
template<> int HashFunc<std::string> (std::string key){

  int result = 0;
  for(std::string::iterator I = key.begin(); I != key.end(); ++I){
    
    result += *I;
  }
  
  // int a = result % SIZE;
  // std::cout<<"MMM"<<a<<std::endl;
  return result % SIZE;
}

//----------------------------------------------------------------
template <typename KeyType, typename ValueType>
class Map{ //Tablica z haszowaniem
  
private:
  ValueType tab[SIZE];
  int index[SIZE];
  int quant = 0;
  
public:
  void insert(const KeyType& key, const ValueType& value);
  ValueType& operator[](const KeyType& key);
  void remove(const KeyType& key);
  void display(const KeyType& key);
};

//Funkcja dodajaca element do hashmapy
//----------------------------------------------------------------
template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value){

  tab[HashFunc(key)] = value;
  index[quant] = HashFunc(key);
  ++quant;
  // std::cout<<key<<std::endl;
  // std::cout<<"wart dod "<<tab[HashFunc(key)]<<std::endl;
}

//Funkcja wyswietlajaca hashmape
//----------------------------------------------------------------
template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::display(const KeyType& key){

  int i = HashFunc(key);
  std::cout<<"Wartosc: "<<tab[i]<<std::endl;
  std::cout<<"Miejsce w mapie: "<<i<<std::endl;
  std::cout<<std::endl;
}

//Przeciazony operator []
//----------------------------------------------------------------
template <typename KeyType, typename ValueType>
ValueType& Map<KeyType,ValueType>::operator[](const KeyType& key){

  index[quant] = HashFunc(key);
  ++quant;
  return tab[HashFunc(key)];
}

//Funkcje usuwajace element z hashmapy dla roznych typow wartosci

//----------------------------------------------------------------
template <> void Map<std::string,int>::remove(const std::string& key){

  tab[HashFunc(key)] = 0;
}

//----------------------------------------------------------------
template <> void Map<std::string,std::string>::remove(const std::string& key){

  tab[HashFunc(key)] = "Hashmap is empty.\n";
}

//----------------------------------------------------------------
template <> void Map<int,int>::remove(const int& key){

  tab[HashFunc(key)] = 0;
}


// ================FUNKCJA DISPLAY================
// =================CALA TABLICA==================
// template <typename KeyType, typename ValueType>
// void Map<KeyType, ValueType>::display(){

//   for(int i = 0; i<SIZE; ++i){
//     std::cout<<tab[i]<<" \n";
//   }
// }

//----------------------------------------------------------------
#endif
