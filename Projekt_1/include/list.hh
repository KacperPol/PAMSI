#ifndef LIST_HH
#define LIST_HH
#include <iostream>

//===LISTA===

template <typename T>
class List{

private:
//-----------------------------------------------
  class Node{
    
  public:
    T value;
    Node *next;
    Node *prev;
    
    //Konstruktor
    Node(){
      value = 0;
      next = nullptr;
      prev = nullptr;
    };
    
    Node(const T& newElement){
      value = newElement;
    }
  };
  
//------------------------------------------------
    Node *first;
    Node *last;
  
//------------------------------------------------  
  class Iterator{
    
    Node *ptr;
    
  public:
    
    Iterator operator++(){
      ptr = ptr->next;
      return *this;
    };
    Iterator operator--(){
      ptr = ptr->prev;
      return *this;
    };
    bool operator==(Iterator I){
      return (ptr == I.ptr);
    }
    bool operator!=(Iterator I){
      return (ptr == I.ptr);
    }
    T* operator->(){
      return &(ptr->value);
    };
    T& operator*(){
      return ptr->value;
    };
    void set(Node *temp){
      ptr = temp;
    };
    Node* GetPointer(){
      return ptr;
    };
  };
  
//------------------------------------------------
  class ConstIterator{
    
    const Node *cptr;
    
  public:
    ConstIterator operator++(){
      cptr = cptr->next;
      return *this;
    };
    ConstIterator operator--(){
      cptr = cptr->prev;
      return *this;
    };
    bool operator==(Iterator I){
      return (cptr == I.cptr);
    }
    bool operator!=(Iterator I){
      return (cptr == I.cptr);
    }
    const T* operator->(){
      return &(cptr->value);
    };
    T operator*(){
      return cptr;
    };
    void set(Node *temp){
      cptr = temp;
    };
  };
  
//------------------------------------------------
public:
  // List(){
  //   first = nullptr;
  //   last = nullptr;
  // };
  void pushBack(const T& newElement); //nowy element na koncu
  void pushFront(const T& newElement); //nowy element na poczatku
  void insert(const T& newElement ,int index); //dodanie nowego elementu
  void remove(int index); //usuniecie wybranego elementu (wybieramy indeks nie dana liczbe)
  Iterator  begin (); 
  Iterator  end();
  ConstIterator  cbegin () const;
  ConstIterator  cend() const;
  T& operator[](int index);
  List(){
    first = nullptr;
    last = nullptr;
  };
};
//-------------------------------------------------

//Funkcja dodajaca element na koncu listy
//-------------------------------------------------
template <typename T>
void List<T>::pushBack(const T& newElement){

  Node *temp = new Node(newElement);
  
  if(first == nullptr)
    first = temp;
  
  if(last == nullptr)
    last = temp;

  else{
    temp->next = nullptr;
    temp->prev = last;
    last->next = temp;
    last = temp;
  }
}

//Funkcja dodajaca element na poczatku listy
//-------------------------------------------------
template <typename T>
void List<T>::pushFront(const T& newElement){

  Node *temp = new Node(newElement);
  
  if(last == nullptr)
    last = temp;

  if(first == nullptr)
    first = temp;

  else{
    temp->prev = nullptr;
    temp->next = first;
    last->prev = temp;
    first = temp;
  }
}

//Fukcja dodajaca element w wybranym miejscu listy (element, miejsce w liscie)
//-------------------------------------------------
template <typename T>
void List<T>::insert(const T& newElement ,int index){

  Node *pre = new Node();
  Node *cur = new Node();
  Node *temp = new Node();

  cur = first;
  
  for(int i=0; i<index; i++){
    pre = cur;
    cur = cur->next;
  }
  temp->value = newElement;
  pre->next = temp;
  temp->next = cur;
}

//Funkcja usuwajaca element z konkretnego miejsca listy (miejsce w liscie)
//-------------------------------------------------
template <typename T>
void List<T>::remove(int index){

  Node *cur = new Node();
  Node *pre = new Node();

  cur = first;
  for(int i=0; i<index;i++){
    pre = cur;
    cur = cur->next;
  }
  pre->next = cur->next;
}

//Analogiczne funkcje begin i end dla iteratora oraz const iteratora

//-------------------------------------------------
template <typename T>
typename List<T>::Iterator List<T>::begin (){
  
  List<T>::Iterator I;
  I.set(first);
  return I;
}
  
//-------------------------------------------------
template <typename T>
typename List<T>::Iterator List<T>::end(){

  List<T>::Iterator I;
  I.set(last);
  return I;
}
  
//-------------------------------------------------
template <typename T>
typename List<T>::ConstIterator List<T>::cbegin () const{
  
  List<T>::ConstIterator cI;
  cI.set(first);
  return cI;
}
  
//-------------------------------------------------
template <typename T>
typename List<T>::ConstIterator List<T>::cend() const{
  
  List<T>::ConstIterator cI;
  cI.set(last);
  return cI;
}
  
//-------------------------------------------------
template <typename T>
T& List<T>::operator[](int index){

  Node *ptr = first;
  for(int i=0; i<index; ++i){
    
    if(ptr->next != nullptr)
      ptr = ptr->next;
    
    else break;
  }
  return ptr->value;
}

//-------------------------------------------------

#endif
