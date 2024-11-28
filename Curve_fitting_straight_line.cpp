#include <iostream>
#include <vector>

using namespace std;

void calculateSums(const vector<double> &x, const vector<double> &y, double &sumX, double &sumY, double &sumX2, double &sumXY)
{
    sumX = 0;
    sumY = 0;
    sumX2 = 0;
    sumXY = 0;
    int n = x.size();
    for (int i = 0; i < n; i++)
    {
        sumX += x[i];
        sumY += y[i];
        sumX2 += x[i] * x[i];
        sumXY += x[i] * y[i];
    }
}

void linearFit(const vector<double> &x, const vector<double> &y, double &slope, double &intercept)
{
    double sumX, sumY, sumX2, sumXY;
    calculateSums(x, y, sumX, sumY, sumX2, sumXY);
    int n = x.size();
    slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    intercept = (sumY - slope * sumX) / n;
}

void printEquation(double slope, double intercept)
{
    cout << "Fitted line equation: y = " << slope << "x + " << intercept << endl;
}

int main()
{
    // class lecture example 1
    vector<double> x = {1, 2, 3, 4, 6, 8};
    vector<double> y = {2.4, 3, 3.6, 4, 5, 6};
    double slope, intercept;
    linearFit(x, y, slope, intercept);
    printEquation(slope, intercept);
    return 0;
}
