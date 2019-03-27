#ifndef QUEUE_HH
#define QUEUE_HH
#include <iostream>

//===KOLEJKA===

template <typename T>
class Queue{

private:
//--------------------------------------------------
  class Node{

  public:
    T value;
    Node *next;
    Node *prev;
    Node(const T& newElement){
      value = newElement;
      prev = nullptr;
      next = nullptr;
    };
  };
  
//--------------------------------------------------
  Node *rear, *front;
  int size;
  
public:

  //Konstruktor
  Queue(){
    size = 0;
    rear = nullptr;
    front = nullptr;
  };
  ~Queue();
  
  //Funkcja informujaca czy stos jest pusty
  bool isEmpty(){
    return (size == 0);
  };
  void enqueue(const T& newElement);
  void dequeue(); //T dequeue();
  void display();
};

//Destruktor
//--------------------------------------------------
template <typename T>
Queue<T>::~Queue(){

  while(!isEmpty())
    dequeue();
}

//Funckja usuwajaca element z kolejki
//--------------------------------------------------
template <typename T>
void Queue<T>::dequeue(){ //T Queue<T>...
  
  if(size != 0){
    size--;
//  if(front != nullptr){
    Node *temp = front;
    front = front->next;
    delete temp;
    if(front == nullptr)
      rear=nullptr;
  }
  else
    std::cout<<"Queue is empty.";
}
//Funkcja dodajaca element do kolejki
//--------------------------------------------------
template <typename T>
void Queue<T>::enqueue(const T& newElement){

  size++;
  Node *temp = new Node(newElement);

  if(// rear == nullptr || 
     front == nullptr){
    rear = temp;
    front = temp;
    rear->next = nullptr;
  }

  else{
    rear->next = temp;
    rear = temp;
  }
}

//Funkcja wyswietlajaca kolejke
//--------------------------------------------------
template <typename T>
void Queue<T>::display(){
  Node *temp = front;
  while(temp != nullptr){
    std::cout<<temp->value<<" ";
    temp = temp->next;
  }
  std::cout<<std::endl;
}

//--------------------------------------------------

#endif
