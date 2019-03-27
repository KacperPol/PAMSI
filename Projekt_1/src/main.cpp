#include "list.hh"
#include "map.hh"
#include "stack.hh"
#include "queue.hh"
#include "priorityqueue.hh"
#include <iostream>

//---Biblioteki STL---
#include <queue>
#include <stack>
#include <list>
#include <iterator>
#include <map>

//---Funkcja wyswietlajaca liste STL
void display_list(std::list<int> tlist){
  
  std::list<int>::iterator I;
  for(I = tlist.begin(); I != tlist.end(); ++I)
    std::cout<<*I<<" ";
  std::cout<<std::endl;
}

//---Funkcja wyswietlajaca stos STL
void display_stack(std::stack<int> tym){

  while(!tym.empty()){
    std::cout<<tym.top()<<"\n";
    tym.pop();
  }
}

//---Funkcja wyswietlajaca kolejke STL
void display_queue(std::queue<int> temp){

  while(!temp.empty()){
    std::cout<<temp.front()<<" ";
    temp.pop();
  }
  std::cout<<std::endl;
}

//---Funkcja wyswietlajaca kolejke priorytetowa STL
void display_priority_queue(std::priority_queue<int> ptemp){

  while(!ptemp.empty()){
    std::cout<<ptemp.top()<<" ";
    ptemp.pop();
  }
  std::cout<<std::endl;
}

//---Funkcja wyswietlajaca hashmape STL
void display_map(std::map<std::string, int> mapSTL){
for (auto itr = mapSTL.begin(); itr != mapSTL.end(); ++itr){
  std::cout<<"Klucz: "<<itr->first<<std::endl;
  std::cout<<"Wartosc: "<<itr->second<<std::endl;
  std::cout<<std::endl;
 }
}


int main(){

  std::cout<<"\n=================================\n";

  //===Lista - projekt===
  List<int> list;
  
  std::cout<<"=====Lista - projekt:=====\n";

  list.pushBack(1);

  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja pushBack(1)----\n";
  std::cout<<"--------------------------\n";

  std::cout<<list[0]<<std::endl;

  list.pushBack(12);

  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja pushBack(12)---\n";
  std::cout<<"--------------------------\n";

  std::cout<<list[0]<<" "<<list[1]<<std::endl;

  list.pushFront(3);
    
  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja pushFront(3)---\n";
  std::cout<<"--------------------------\n";

  std::cout<<list[0]<<" "<<list[1]<<" "<<list[2]<<std::endl;

  list.pushFront(9);

  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja pushFront(9)---\n";
  std::cout<<"--------------------------\n";

  std::cout<<list[0]<<" "<<list[1]<<" "<<list[2]<<" "<<list[3]<<std::endl;
  
  list.insert(2,2);

  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja insert(2,2)----\n";
  std::cout<<"--------------------------\n";
  
  std::cout<<list[0]<<" "<<list[1]<<" "<<list[2]<<" "<<list[3]<<" "<<list[4]<<std::endl;

  list.remove(1);

  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja remove(1)-----\n";
  std::cout<<"--------------------------\n";

  std::cout<<list[0]<<" "<<list[1]<<" "<<list[2]<<" "<<list[3]<<std::endl<<std::endl<<std::endl;

  
  //===Lista - STL===
  std::list<int> listSTL;
 
  std::cout<<"=======Lista - STL:=======\n";

  listSTL.push_back(1);

  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja pushBack(1)----\n";
  std::cout<<"--------------------------\n";

  display_list(listSTL);
  
  listSTL.push_back(12);

  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja pushBack(12)---\n";
  std::cout<<"--------------------------\n";

  display_list(listSTL);
  
  listSTL.push_front(3);
    
  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja pushFront(3)---\n";
  std::cout<<"--------------------------\n";

  display_list(listSTL);
  
  listSTL.push_front(9);

  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja pushFront(9)---\n";
  std::cout<<"--------------------------\n";

  display_list(listSTL);
  
  std::list<int>::iterator it;
  it = listSTL.begin();
  ++it;
  ++it;
  listSTL.insert(it,2);

  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja insert(2,2)----\n";
  std::cout<<"--------------------------\n";
  
  display_list(listSTL);
  
  listSTL.remove(3);

  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja remove(3)-----\n";
  std::cout<<"--------------------------\n";

  display_list(listSTL);
  
  std::cout<<std::endl;
  
  std::cout<<std::endl;
  
  std::cout<<"=================================\n";

  //===Kolejka - projekt===
  Queue<int> que;
   
  std::cout<<"====Kolejka - projekt:====\n";
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja dequeue()-----\n";
  std::cout<<"--------------------------\n";
  
  que.dequeue();
  
  que.display();
  que.enqueue(1);
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja enqueue(1)----\n";
  std::cout<<"--------------------------\n";
  
  que.display();
  
  que.enqueue(49);
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja enqueue(49)---\n";
  std::cout<<"--------------------------\n";
  
  que.display();
    
  que.enqueue(2);
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja enqueue(2)----\n";
  std::cout<<"--------------------------\n";
  
  que.display();

  que.dequeue();
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja dequeue()-----\n";
  std::cout<<"--------------------------\n";
  
  que.display();
  
  que.dequeue();
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja dequeue()-----\n";
  std::cout<<"--------------------------\n";
  
  que.display();
    
  que.enqueue(15);
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja enqueue(15)---\n";
  std::cout<<"--------------------------\n";
  
  que.display();
  
  que.enqueue(8);
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja enqueue(8)----\n";
  std::cout<<"--------------------------\n";
  
  que.display();

  std::cout<<std::endl<<std::endl;

  
  //===Kolejka - STL===
  std::queue<int> queSTL;
   
  std::cout<<"======Kolejka - STL:======\n";
  
  queSTL.push(1);

  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja enqueue(1)----\n";
  std::cout<<"--------------------------\n";
  
  display_queue(queSTL);
		
  queSTL.push(49);
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja enqueue(49)---\n";
  std::cout<<"--------------------------\n";
  
  display_queue(queSTL);
  
  queSTL.push(2);
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja enqueue(2)----\n";
  std::cout<<"--------------------------\n";
  
  display_queue(queSTL);
  
  queSTL.pop();
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja dequeue()-----\n";
  std::cout<<"--------------------------\n";
  
  display_queue(queSTL);
  
  queSTL.pop();
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja dequeue()-----\n";
  std::cout<<"--------------------------\n";
  
  display_queue(queSTL);
  
  queSTL.push(15);
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja enqueue(15)---\n";
  std::cout<<"--------------------------\n";
  
  display_queue(queSTL);
  
  queSTL.push(8);
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja enqueue(8)----\n";
  std::cout<<"--------------------------\n";
  
  display_queue(queSTL);
    
  std::cout<<std::endl<<std::endl;

  std::cout<<"=================================\n";


  //===Kolejka priopytetowa - proj===
  PriorityQueue<int> quep;
  
  std::cout<<"==Kolejka (prio) - proj:==\n";
    
  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja dequeue()------\n";
  std::cout<<"--------------------------\n";
   
  quep.dequeue();
  
  quep.display();

  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja enqueue(6,2)---\n";
  std::cout<<"--------------------------\n";
   
  quep.enqueue(6,2);
  
  quep.display();  

  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja enqueue(1,7)---\n";
  std::cout<<"--------------------------\n";
   
  quep.enqueue(1,7);
  
  quep.display();
  
  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja enqueue(10,4)--\n";
  std::cout<<"--------------------------\n";
   
  quep.enqueue(10,4);
  
  quep.display();
  
  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja dequeue()------\n";
  std::cout<<"--------------------------\n";
   
  quep.dequeue();
  
  quep.display();

  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja dequeue()------\n";
  std::cout<<"--------------------------\n";
   
  quep.dequeue();
  
  quep.display();

  std::cout<<std::endl<<std::endl;

  
  //===Kolejka priopytetowa - STL===
  std::priority_queue<int> quepSTL;
  
  std::cout<<"==Kolejka (prio) - STL:===\n";
    
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja enqueue(6)----\n";
  std::cout<<"--------------------------\n";
   
  quepSTL.push(6);

  display_priority_queue(quepSTL);
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja enqueue(1)----\n";
  std::cout<<"--------------------------\n";
   
  quepSTL.push(1);
  
  display_priority_queue(quepSTL);
    
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja enqueue(10)---\n";
  std::cout<<"--------------------------\n";
   
  quepSTL.push(10);
    
  display_priority_queue(quepSTL);
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja dequeue()-----\n";
  std::cout<<"--------------------------\n";
   
  quepSTL.pop();
  
  display_priority_queue(quepSTL);
  
  std::cout<<"--------------------------\n";
  std::cout<<"----Funkcja dequeue()-----\n";
  std::cout<<"--------------------------\n";
   
  quepSTL.pop();
  
  display_priority_queue(quepSTL);
  
  std::cout<<std::endl<<std::endl;


  std::cout<<"=================================\n";
  
  //===Stos - projekt===
  Stack<int> stos;
  
  std::cout<<"======Stos - projekt:=====\n";
 
  std::cout<<"--------------------------\n";
  std::cout<<"------Funkcja pop()-------\n";
  std::cout<<"--------------------------\n";
   
  stos.pop();
  
  stos.display();
  stos.push(1);
  
  std::cout<<"--------------------------\n";
  std::cout<<"------Funkcja push(1)-----\n";
  std::cout<<"--------------------------\n";
     
  stos.display();   
  stos.push(10); 
  
  std::cout<<"--------------------------\n";
  std::cout<<"------Funkcja push(10)----\n";
  std::cout<<"--------------------------\n";
  
  stos.display();
  stos.push(100);
  
  std::cout<<"--------------------------\n";
  std::cout<<"------Funkcja push(100)---\n";
  std::cout<<"--------------------------\n";
   
  stos.display();   
  stos.pop();
  
  std::cout<<"--------------------------\n";
  std::cout<<"------Funkcja pop()-------\n";
  std::cout<<"--------------------------\n";
   
  stos.display();

  std::cout<<std::endl<<std::endl;
  
    
  //===Stos - STL===
  std::stack<int> stosSTL;
  
  std::cout<<"========Stos - STL:=======\n";

  stosSTL.push(1);
  
  std::cout<<"--------------------------\n";
  std::cout<<"------Funkcja push(1)-----\n";
  std::cout<<"--------------------------\n";
     
  display_stack(stosSTL);
  
  stosSTL.push(10); 
  
  std::cout<<"--------------------------\n";
  std::cout<<"------Funkcja push(10)----\n";
  std::cout<<"--------------------------\n";
  
  display_stack(stosSTL);
    
  stosSTL.push(100);
  
  std::cout<<"--------------------------\n";
  std::cout<<"------Funkcja push(100)---\n";
  std::cout<<"--------------------------\n";
   
  display_stack(stosSTL);
  
  stosSTL.pop();
  
  std::cout<<"--------------------------\n";
  std::cout<<"------Funkcja pop()-------\n";
  std::cout<<"--------------------------\n";
   
  display_stack(stosSTL);
  
  std::cout<<std::endl<<std::endl;

  std::cout<<"=================================\n";

  //===Hashmapa - projekt===
  Map<std::string,int> map;
      
  std::cout<<"====Hashmapa - projekt:===\n";
  
  map.insert("kot",5);

  std::cout<<"--------------------------\n";
  std::cout<<"--Funkcja insert(kot, 5)--\n";
  std::cout<<"--------------------------\n";

  std::cout<<"Klucz: kot\n";
  map.display("kot");

  map.insert("pies",15);
  
  std::cout<<"--------------------------\n";
  std::cout<<"-Funkcja insert(pies, 15)-\n";
  std::cout<<"--------------------------\n";

  std::cout<<"Klucz: pies\n";
  map.display("pies");
      
  std::cout<<"--------------------------\n";
  std::cout<<"---Biezacy stan Hashmapy--\n";
  std::cout<<"--------------------------\n";

  std::cout<<map["kot"]<<" "<<map["pies"]<<std::endl;
  
  map.remove("pies");
    
  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja remove(pies)---\n";
  std::cout<<"--------------------------\n";

  std::cout<<map["kot"]<<" "<<map["pies"]<<std::endl;

  std::cout<<std::endl<<std::endl;


  //===Hashmapa - projekt===
  std::map<std::string,int> mapSTL;

  std::cout<<"====Hashmapa - projekt:===\n";

  mapSTL.insert(std::pair<std::string,int>("kot", 5));

  std::cout<<"--------------------------\n";
  std::cout<<"--Funkcja insert(kot, 5)--\n";
  std::cout<<"--------------------------\n";

  display_map(mapSTL);

  mapSTL.insert(std::pair<std::string,int>("pies", 15));
  
  std::cout<<"--------------------------\n";
  std::cout<<"-Funkcja insert(pies, 15)-\n";
  std::cout<<"--------------------------\n";

  display_map(mapSTL);
      
  std::cout<<"--------------------------\n";
  std::cout<<"---Biezacy stan Hashmapy--\n";
  std::cout<<"--------------------------\n";

  display_map(mapSTL);
  
  mapSTL.erase("pies");
    
  std::cout<<"--------------------------\n";
  std::cout<<"---Funkcja erase(pies)---\n";
  std::cout<<"--------------------------\n";

  display_map(mapSTL);

  std::cout<<std::endl<<std::endl;

  
  std::cout<<"=================================\n";

  return 0;
}
