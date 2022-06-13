/*
  Andreas Josef C. Diaz
  Marc Jefferson B. Obeles
  Justin Gabriel M. Sy

  ENGG 151.01 - A
  Project 1: Normalized Crosscorrelation
*/

#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

bool isValidLine(string s, int& start, double& signalValue);

void readFirstLine(ifstream& xFile, ifstream& yFile, int& xStart,
                   int& yStart, vector<double>& x,
                   vector<double>& y, bool * fileCheck);

void readLines(ifstream& xFile, ifstream& yFile, vector<double>& x,
              vector<double>& y);

void generateOutputFile(string fileName, double* p, int lEnd,
                        int lStart);

#endif // FILEIO_H_INCLUDED
