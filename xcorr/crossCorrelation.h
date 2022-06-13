/*
  Andreas Josef C. Diaz
  Marc Jefferson B. Obeles
  Justin Gabriel M. Sy

  ENGG 151.01 - A
  Project 1: Normalized Crosscorrelation
*/

#ifndef CROSSCORRELATION_H_INCLUDED
#define CROSSCORRELATION_H_INCLUDED

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void showSignals(vector<double> x, vector<double> y, int xStart,
                 int yStart, bool DC);

void removeDC(vector<double>& x, vector<double>& y);

double getNormCoefficient(vector<double> x, vector<double> y);

double * crossCorrelation(vector<double> x, vector<double> y,
                      int xStart, int yStart, int& lStart,
                      int& lEnd);

void showNormCrossCorr(double* p, int lStart, int lEnd,
                       double normCoefficient);

double * normCrossCorrelation(vector<double> x, vector<double> y,
                              int xStart, int yStart, int& lStart,
                              int& lEnd);

#endif // CROSSCORRELATION_H_INCLUDED
