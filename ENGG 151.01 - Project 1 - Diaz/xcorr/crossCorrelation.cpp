/*
  Andreas Josef C. Diaz
  Marc Jefferson B. Obeles
  Justin Gabriel M. Sy

  ENGG 151.01 - A
  Project 1: Normalized Crosscorrelation
*/

#include <iostream>
#include <vector>
#include <cmath>

#include "crossCorrelation.h"
#include "DEBUG.h"

using namespace std;

void showSignals(vector<double> x, vector<double> y, int xStart,
                 int yStart, bool DC)
{
  cout << endl;
  if(DC == true) cout << "removed DC content ";
  cout << "x signals" << endl;

  cout << xStart <<  " ";
  for(int i = 0; i < x.size(); i++)
    cout << x[i] << endl;

  cout << endl;
  if(DC == true) cout << "removed DC content ";
  cout << "y signals" << endl;

  cout << yStart <<  " ";
  for(int i = 0; i < y.size(); i++)
    cout << y[i] << endl;
}

void removeDC(vector<double>& x, vector<double>& y)
{
  double xSum = 0;
  double ySum = 0;

  for(int i = 0; i < x.size(); i++)
    xSum += x[i];

  for(int i = 0; i < y.size(); i++)
    ySum += y[i];

  double xAverage = xSum / x.size();
  double yAverage = ySum / y.size();
  double result;

  for(int i = 0; i < x.size(); i++)
  {
    result = x[i] - xAverage;
    x[i] = result;
  }

  for(int i = 0; i < y.size(); i++)
  {
    result = y[i] - yAverage;
    y[i] = result;
  }
}

double getNormCoefficient(vector<double> x, vector<double> y)
{
  double xx = 0;
  double yy = 0;

  for(int i = 0; i < x.size(); i++)
    xx += pow(x[i], 2);

  for(int i = 0; i < y.size(); i++)
    yy += pow(y[i], 2);

  return sqrt(xx * yy);
}

double * crossCorrelation(vector<double> x, vector<double> y,
                      int xStart, int yStart, int& lStart,
                      int& lEnd)
{
  int xEnd = xStart + x.size() - 1;
  int yEnd = yStart + y.size() - 1;

  lStart = xStart - yEnd;
  lEnd = xEnd - yStart;
  double * r = new double [lEnd - lStart + 1];

  for(int i = lStart; i <= lEnd; i++)
  {
    double result = 0;

    for(int j = 0; j < y.size(); j++)
    {
      if((j - (xStart - yStart) + i) < 0 ||
         (j - (xStart - yStart) + i) >= x.size()) continue;

      result += x[j - (xStart - yStart) + i] * y[j];
    }

    r[(i - lStart)] = result;
  }
  return r;
}

void showNormCrossCorr(double* p, int lStart, int lEnd,
                       double normCoefficient)
{
  cout << endl << "normalized crosscorrelated signals" << endl;
  cout << "normalization coefficient: " << normCoefficient << endl;

  cout << lStart << " ";
  for(int i = 0; i <= (lEnd - lStart); i++)
    cout << p[i] << endl;
}

double * normCrossCorrelation(vector<double> x, vector<double> y,
                              int xStart, int yStart, int& lStart,
                              int& lEnd)
{
  removeDC(x, y);

  #ifdef DEBUG
    showSignals(x, y, xStart, yStart, true);
  #endif

  double normCoefficient =  getNormCoefficient(x, y);
  double * p = crossCorrelation(x, y, xStart, yStart, lStart, lEnd);

  for(int i = 0; i <= (lEnd - lStart); i++)
    p[i] = p[i] / normCoefficient;

  #ifdef DEBUG
    showNormCrossCorr(p, lStart, lEnd, normCoefficient);
  #endif
  return p;
}
