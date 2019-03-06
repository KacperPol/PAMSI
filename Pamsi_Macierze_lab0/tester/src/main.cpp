#include "pamsi_tester/Tester.hpp"
#include "spdlog/spdlog.h"
#include <fstream>
#include <numeric>
#include <vector>


// Struktura przechowujaca elementy macierzy w wektorze oraz liczbe kolumn i wierszy
struct Matrix   
{
  int nRows, nCols;
  std::vector<float> data;
};


std::ostream& operator<<(std::ostream& output, const Matrix& matrix)
{
  std::ostream_iterator<float> outIterator(output, " ");

  std::copy(matrix.data.begin(), matrix.data.end(), outIterator);
  
  return output;
}


// Struktura przechowujaca dwie macierze do zsumowania
struct MatrixSumInput 
{
  Matrix A;
  Matrix B;
};


// Klasa MatrixSumTester dziedziczaca po klasie Tester
class MatrixSumTester: public Tester<Matrix, MatrixSumInput>
{
protected:
  Matrix runAlgorithm(const MatrixSumInput& inputData) override;
  MatrixSumInput readSingleInput(std::istream& inputStream) override;
};


// Funkcja realizujaca dodawanie macierzy
Matrix MatrixSumTester::runAlgorithm(const MatrixSumInput& inputData)
{
  const auto nRows = inputData.A.nRows;
  const auto nCols = inputData.A.nCols;

  Matrix result;

  result.nRows = nRows;
  result.nCols = nCols;

  for(int i = 0; i < nCols*nRows; ++i)
    {
      result.data.push_back(inputData.A.data[i] + inputData.B.data[i]);
    }

  return result;
}


void readToMatrix(std::istream& inputStream, Matrix& matrix, int numOfElements)
{
  for(int i = 0; i < numOfElements; ++i)
    {
      float matrixElement = 0.f;
      inputStream >> matrixElement;

      matrix.data.push_back(matrixElement);
    }
}


// Funkcja napisana na podstawie readSingleInput z poprzedniego programu
MatrixSumInput MatrixSumTester::readSingleInput(std::istream& inputStream)
{
  int nRows = 0, nCols = 0;

  inputStream >> nRows >> nCols;

  MatrixSumInput input;

  input.A.nRows = nRows;
  input.B.nRows = nRows;
  input.A.nCols = nCols;
  input.B.nCols = nCols;

  readToMatrix(inputStream, input.A, nRows*nCols);
  readToMatrix(inputStream, input.B, nRows*nCols);

  return input;
}


int main(int /*argc*/, char* /*argv*/[])
{
    std::ifstream inputFile{"input.txt"};
    std::ofstream dataOutputFile{"output.txt"}, timeOutputFile{"times.csv"};

    MatrixSumTester tester;

    if(!inputFile)
    {
        spdlog::error("input.txt cannot be opened!");
        return -1;
    }

    tester.runAllTests(inputFile, dataOutputFile, timeOutputFile);
}
