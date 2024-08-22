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

// https://www.tutorialspoint.com/how-to-check-if-input-is-numeric-in-
// cplusplus
bool isNumeric(string s)
{
  for(int i = 0; i < s.length(); i++)
    if(isdigit(s[i]) == false && s[i] != '.' && s[i] != '-')
      return false;
  return true;
}

// https://stackoverflow.com/questions/18971533/c-comparison-of-two
// -double-values-not-working-properly
bool double_equals(double a, double b)
{
  double epsilon = 0.001;
  return abs(a - b) < epsilon;
}

bool isValidLine(string s, int& start, double& signalValue)
{
  stringstream ss;
  ss << s;

  if(ss >> start)
  {
    if(!(ss >> signalValue)) // e.g. integer string
    {
      // Reload 's' into stringstream
      ss.clear();
      ss.str("");
      ss << s;

      string tmp;
      ss >> tmp;

      // This fixes signal lines with strings appended to integers,
      // For example, "2asd 5 comment" where extracted start = 0 and
      // signalValue = 2; This code fixes the function to return false
      // because "2asd" is a string
      if(!isNumeric(tmp)) return false;

      signalValue = start;
      start = 0;
    }
    else // e.g. integer double OR double string
    {
      // Reload 's' into stringstream
      ss.clear();
      ss.str("");
      ss << s;

      double tmp;
      ss >> tmp;

      // This fixes signal values with decimal places; For example,
      // "2.44 9 comment" where extracted start = 2 and
      // signalValue = 0.44; This code fixes the values into start = 0
      // and signalValue = 2.44; However, the exception of
      // signalValue = 0 must be considered
      if(double_equals(tmp, start + ((start > 0) ? signalValue
                                     : -1 * signalValue))
                       && !double_equals(signalValue, 0))
      {
        start = 0;
        signalValue = tmp;
      }

      // Reload 's' into stringstream
      ss.clear();
      ss.str("");
      ss << s;

      int tmp2;
      string tmp3;
      ss >> tmp2;
      ss >> tmp3;

      // This fixes signal lines with strings appended to integers,
      // For example, "5 2asd comment" where extracted start = 5 and
      // signalValue = 2; This code fixes the function to return
      // start = 0 and signalValue = 5 because "2asd" is a string
      if(!isNumeric(tmp3))
      {
        start = 0;
        signalValue = tmp2;
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
