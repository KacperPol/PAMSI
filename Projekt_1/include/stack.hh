#ifndef STACK_HH
#define STACK_HH

#include <iostream>

//===STOS===

template <typename T>
class Stack{
  
private:
//------------------------------------------
  class Node {
    
  public:
    T value;
    Node *next;
    
    Node(const T& newElement){ 
      value = newElement;
    }
    
  };
    Node *top;
  
//------------------------------------------
public:
  
  //Konstruktor
  Stack(){
    top = nullptr;
  }
  ~Stack();
  
  void push(const T& newElement);
  void pop(); // T pop();
  bool isEmpty();
  void display();
};

//Destruktor
//------------------------------------------
template <typename T>
Stack<T>::~Stack(){

  Node *temp, *next;
  temp = top;

  while(temp != NULL) {
    next = temp->next;
    delete temp;
    temp = next;
  }
}

//Funkcja dodajaca element do stosu
//------------------------------------------
template <typename T>
void Stack<T>::push(const T& newElement){

  Node *temp = new Node(newElement);

  if(isEmpty()){
    top = temp;
    temp->next = 0;
  }
  
  else{
    temp->next = top;
    top = temp;
  }
}

//Funkcja usuwajaca element ze stosu
//------------------------------------------
template <typename T>
void Stack<T>::pop(){ // T Stack<T>...

  if(top != NULL){
    Node *temp = top;
    top = top->next;
    delete temp;
  }

  else std::cout<<"Stack is empty.\n";
}

//Funkcja informujaca czy stos jest pusty
//------------------------------------------
template <typename T>
bool Stack<T>::isEmpty(){

  bool status;

  if(!top)
    status = true;
  
  else
    status = false;

  return status;
}

//Funkcja wyswietlajaca stos
//------------------------------------------
template <typename T>
void Stack<T>::display(){
  Node *temp = top;
  while(temp != nullptr){
    std::cout<<temp->value<<"\n";
    temp = temp->next;
  }
}

#endif
