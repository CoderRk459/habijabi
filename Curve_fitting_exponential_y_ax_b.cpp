#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void calculateSums(const vector<double>& x, const vector<double>& y, double& sumX, double& sumX2, double& sumY, double& sumXY) {
    int n = x.size();
    for (int i = 0; i < n; i++) {
        double xi = x[i];
        double yi = y[i];
        sumX += log(xi);
        sumX2 += log(xi) * log(xi);
        sumY += log(yi);
        sumXY += log(xi) * log(yi);
    }
}

void powerLawFit(const vector<double>& x, const vector<double>& y, double& a, double& b) {
    double sumX=0, sumX2=0, sumY=0, sumXY=0;
    calculateSums(x, y, sumX, sumX2, sumY, sumXY);
    int n = x.size();
    double B = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    double lnA = (sumY - B * sumX) / n;
    a = exp(lnA);
    b = B;
}

void printEquation(double a, double b) {
    cout << "Fitted power law equation: y = " << a << " * x^" << b << endl;
}

int main() {
    vector<double> x = {1, 2, 3, 4, 5};
    vector<double> y = {0.5,2,4.5,8,12.5};
    double a, b;
    powerLawFit(x, y, a, b);
    printEquation(a, b);
    return 0;
}
