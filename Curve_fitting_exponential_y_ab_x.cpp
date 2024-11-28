#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void calculateSums(vector<double> &x, const vector<double> &y, double &sumX, double &sumX2, double &sumY, double &sumXY)
{
    int n = x.size();
    for (int i = 0; i < n; i++)
    {
        double xi = x[i];
        double yi = y[i];
        sumX += xi;
        sumX2 += xi * xi;
        sumY += log(yi);
        sumXY += xi * log(yi);
    }
}

void exponentialFit(vector<double> &x, const vector<double> &y, double &a, double &b)
{
    double sumX = 0, sumX2 = 0, sumY = 0, sumXY = 0;
    calculateSums(x, y, sumX, sumX2, sumY, sumXY);
    int n = x.size();
    double B = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    double lnA = (sumY - B * sumX) / n;
    a = exp(lnA);
    b = exp(B);
}

void printEquation(double a, double b)
{
    cout << "Fitted exponential equation: y = " << a << " * " << b << "^x" << endl;
}

int main()
{
    //my class lecture example3
    vector<double> x = {1, 2, 3, 4, 5,6,7};
    vector<double> y = {87,97,113,124,202,195,193};
    double a, b;
    exponentialFit(x, y, a, b);
    printEquation(a, b);
    return 0;
}
