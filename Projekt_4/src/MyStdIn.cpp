#include "../include/MyStdIn.hpp"


int MyStdIn::readNextInt() {
  
  int number = 0;
  std::string inputLine;
  bool isValid;

  do {
      
    isValid = true;
    std::getline(std::cin, inputLine);
	
    try {
	  
      number = std::stoi(inputLine);
    }
	
    catch (const std::exception& e) {
	  
      std::cerr << e.what() << "\n";
      std::cerr << "ERROR. Wpisany argument nie jest typu int.\n";
      std::cerr << "Twoj wybor: ";
      isValid = false;
    }
  } 
  while (isValid == false);

  return number;
}

int MyStdIn::readNextIntFromValidScope(const int BOTTOM, const int TOP) {
  
  int number = 0;
  bool isValid;

  do {
      
    isValid = true;
    number = readNextInt();
	
    if(number < BOTTOM || number > TOP) {
	  
      std::cerr << "ERROR. Wpisana liczba musi byc typu int od " << BOTTOM << " do " << TOP << ".\n";
      std::cerr << "Twoj wybor: ";
      isValid = false;
    }

  } 
  while (isValid == false);

  return number;
}

char MyStdIn::readNextCharWithValidation(const std::vector<char> VALID_CHARS) {
  
  std::string inputLine;
  bool isValid;

  do {
      
    isValid = true;
    std::getline(std::cin, inputLine);
    if (isVectorContainChar(VALID_CHARS, inputLine[0]) == false ) {
	  
      std::cerr << "ERROR. Wpisany znak musi byc jednym z: [ ";
      for (unsigned int i = 0; i < VALID_CHARS.size(); i++) {
	      
	std::cerr << VALID_CHARS[i] << " ";
      }
	    
      std::cerr << "].\n";
      std::cerr << "Twoj wybor: ";
      isValid = false;
    }
  } 
  while (isValid == false);

  return inputLine[0];
}

bool MyStdIn::isVectorContainChar(const std::vector<char> VEC, const char CHARACTER) {
  
  for (unsigned int i = 0; i < VEC.size(); i++) {
      
    if (VEC[i] == CHARACTER) {
	  
      return true;
    }
  }
  return false;
}
