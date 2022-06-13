/*
  Andreas Josef C. Diaz
  Marc Jefferson B. Obeles
  Justin Gabriel M. Sy

  ENGG 151.01 - A
  Project 1: Normalized Crosscorrelation
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "fileIO.h"
#include "DEBUG.h"

using namespace std;

bool isValidLine(string s, int& start, double& signalValue)
{
  stringstream ss;
  ss << s;

  if(ss >> start)
  {
    if(!(ss >> signalValue))
    {
      signalValue = start;
      start = 0;
    }
    else
    {
      // Reload 's' into stringstream
      ss.clear();
      ss.str("");
      ss << s;

      double tmp;
      ss >> tmp;

      if(tmp == start + ((start > 0) ? signalValue
                         : -1 * signalValue))
      {
        start = 0;
        signalValue = tmp;
      }
    }
    return true;
  }
  return false;
}

void readFirstLine(ifstream& xFile, ifstream& yFile, int& xStart,
                   int& yStart, vector<double>& x,
                   vector<double>& y, bool * fileCheck)
{
  string line;
  double signalValue;

  getline(xFile, line);
  fileCheck[0] = isValidLine(line, xStart, signalValue);
  x.push_back(signalValue);

  getline(yFile, line);
  fileCheck[1] = isValidLine(line, yStart, signalValue);
  y.push_back(signalValue);
}

void readLines(ifstream& xFile, ifstream& yFile, vector<double>& x,
              vector<double>& y)
{
  string line;
  int start;
  double signalValue;

  while(getline(xFile, line))
  {
    if(!isValidLine(line, start, signalValue)) break;

    x.push_back(signalValue);
  }

  while(getline(yFile, line))
  {
    if(!isValidLine(line, start, signalValue)) break;

    y.push_back(signalValue);
  }

  xFile.close();
  yFile.close();
}

void generateOutputFile(string fileName, double* p, int lEnd,
                        int lStart)
{
  ofstream oFile;
  oFile.open(fileName);

  oFile << lStart << " ";
  for(int i = 0; i <= (lEnd - lStart); i++)
    oFile << p[i] << "\n";

  oFile.close();

  #ifdef DEBUG
    cout << endl << "Normalized crosscorrelation file " << fileName
         << " generated" << endl;
  #endif
}
