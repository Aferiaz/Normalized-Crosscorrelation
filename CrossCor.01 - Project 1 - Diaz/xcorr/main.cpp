/*
  Andreas Josef C. Diaz
  Marc Jefferson B. Obeles
  Justin Gabriel M. Sy

  ENGG 151.01 - A
  Project 1: Normalized Crosscorrelation
*/

#include <iostream>
#include <fstream>
#include <vector>

#include "crossCorrelation.h"
#include "fileIO.h"
#include "DEBUG.h"

using namespace std;

int main(int argc, char** argv)
{
  if(argc < 4 || argc > 4)
  {
    cout << "Syntax Erorr: [xdata] [ydata] [output file]" << endl;
  }
  else
  {
    ifstream xFile, yFile, outputFileCheck;
    bool * fileCheck = new bool [2];

    vector<double> x, y;
    int xStart, yStart, lStart, lEnd;

    xFile.open(argv[1]);
    yFile.open(argv[2]);
    if(!xFile.is_open() || !xFile.is_open())
    {
      cout <<  "Error: Unable to open file/s" << endl;
      return 0;
    }

    outputFileCheck.open(argv[3]);
    if(outputFileCheck.is_open())
    {
      cout << "Error: Output file already exists" << endl;
      outputFileCheck.close();
      return 0;
    }

    readFirstLine(xFile, yFile, xStart, yStart, x, y, fileCheck);
    if(!fileCheck[0] || !fileCheck[1])
    {
      cout << "Error: Invalid signal file/s" << endl;
      return 0;
    }

    readLines(xFile, yFile, x, y);

    #ifdef DEBUG
      showSignals(x, y, xStart, yStart, false);
    #endif

    double * p = normCrossCorrelation(x, y, xStart, yStart, lStart,
                                      lEnd);

    generateOutputFile(argv[3], p, lEnd, lStart);
  }
  return 0;
}
