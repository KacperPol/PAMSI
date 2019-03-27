#ifndef PRIORITYQUEUE_HH
#define PRIORITYQUEUE_HH
#include <iostream>

//===KOLEJKA PRIORYTETOWA===

template <typename T>
class PriorityQueue{
  
private:
  
class Node {
  
public:
  T value;
  int priority;
  Node *next;
  Node(){
    value = 0;
    priority = 0;
    next = nullptr;
  };
};
  Node *front;
  int size;
  
public:
  
  //Konstruktor
  PriorityQueue(){
    size = 0;
    front = nullptr;
  };
  ~PriorityQueue();
  
  //Funkcja informujaca czy stos jest pusty
  bool isEmpty(){
    return (size == 0);
  };
  void enqueue(const T& newElement, int priority);
  void dequeue();
  void display();
};

//Funkcja dodajaca element to kolejki
//----------------------------------------------------------------
template <typename T>
void PriorityQueue<T>::enqueue(const T& newElement, int priority) {

  size++;
  Node *temp, *ptr;
  temp = new Node();
  
  temp->value = newElement;
  temp->priority = priority;
   
  if (front == NULL || priority < front->priority) {
    temp->next = front;
    front = temp;
  }

  else {
    ptr = front;
    while (ptr->next != NULL && ptr->next->priority <= priority)
    ptr=ptr->next;
    temp->next = ptr->next;
    ptr->next = temp;
  }
}

//Destruktor
//----------------------------------------------------------------
template <typename T>
PriorityQueue<T>::~PriorityQueue(){

  while(!isEmpty())
    dequeue();
}

//Funkcja usuwajaca element z kolejki
//----------------------------------------------------------------
template <typename T>
void PriorityQueue<T>::dequeue(){

  if(size != 0){
  size--;
  Node *temp;

  temp = front;
  front = front->next;
  free(temp);
  }
  else
    std::cout<<"Priority Queue is empty.";
}

//Funkcja wyswietlajaca kolejke
//----------------------------------------------------------------
template <typename T>
void PriorityQueue<T>::display(){
  
   Node *ptr;
   ptr = front;
   
     while(ptr != NULL) {
       std::cout<<"("<<ptr->value<<", "<<ptr->priority<<") ";
       ptr = ptr->next;
     }
     std::cout<<std::endl;
}

//----------------------------------------------------------------

#endif
