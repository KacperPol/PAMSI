#ifndef MY_STD_IN_H
#define MY_STD_IN_H

#include <iostream>
#include <vector>
#include <string>

class MyStdIn {
  
public:    
  static int readNextInt();
  static int readNextIntFromValidScope(const int BOTTOM, const int TOP);
    
  static char readNextCharWithValidation(const std::vector<char> VALID_CHARS);

private:
  static bool isVectorContainChar(const std::vector<char> VEC, const char CHARACTER);
};

#endif
