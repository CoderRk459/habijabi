#include <iostream>
#include <vector>

using namespace std;

void calculateSums(const vector<double> &x, const vector<double> &y,
                   double &sumX, double &sumY, double &sumX2, double &sumX3,
                   double &sumX4, double &sumX5, double &sumX6,
                   double &sumXY, double &sumX2Y, double &sumX3Y)
{
    sumX = 0;
    sumY = 0;
    sumX2 = 0;
    sumX3 = 0;
    sumX4 = 0;
    sumX5 = 0;
    sumX6 = 0;
    sumXY = 0;
    sumX2Y = 0;
    sumX3Y = 0;

    int n = x.size();
    for (int i = 0; i < n; i++)
    {
        double x2 = x[i] * x[i];
        double x3 = x2 * x[i];
        double x4 = x3 * x[i];
        double x5 = x4 * x[i];
        double x6 = x5 * x[i];

        sumX += x[i];
        sumY += y[i];
        sumX2 += x2;
        sumX3 += x3;
        sumX4 += x4;
        sumX5 += x5;
        sumX6 += x6;
        sumXY += x[i] * y[i];
        sumX2Y += x2 * y[i];
        sumX3Y += x3 * y[i];
    }
}

vector<double> solveLinearSystem(vector<vector<double>> A, vector<double> B)
{
    int n = A.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double ratio = A[j][i] / A[i][i];
            for (int k = i; k < n; k++)
            {
                A[j][k] -= ratio * A[i][k];
            }
            B[j] -= ratio * B[i];
        }
    }

    vector<double> X(n);
    for (int i = n - 1; i >= 0; i--)
    {
        X[i] = B[i];
        for (int j = i + 1; j < n; j++)
        {
            X[i] -= A[i][j] * X[j];
        }
        X[i] /= A[i][i];
    }
    return X;
}

void cubicFit(const vector<double> &x, const vector<double> &y, double &a, double &b, double &c, double &d)
{
    double sumX, sumY, sumX2, sumX3, sumX4, sumX5, sumX6, sumXY, sumX2Y, sumX3Y;
    calculateSums(x, y, sumX, sumY, sumX2, sumX3, sumX4, sumX5, sumX6, sumXY, sumX2Y, sumX3Y);

    vector<vector<double>> A = {
        {static_cast<double>(x.size()), sumX, sumX2, sumX3},
        {sumX, sumX2, sumX3, sumX4},
        {sumX2, sumX3, sumX4, sumX5},
        {sumX3, sumX4, sumX5, sumX6}};
    vector<double> B = {sumY, sumXY, sumX2Y, sumX3Y};

    vector<double> coefficients = solveLinearSystem(A, B);
    a = coefficients[0];
    b = coefficients[1];
    c = coefficients[2];
    d = coefficients[3];
}

void printEquation(double a, double b, double c, double d)
{
    cout << "Fitted cubic equation: y = " << a << " + " << b << "x + " << c << "x^2 + " << d << "x^3" << endl;
}

int main()
{

    // solution y = 1.42 - 1.07x + 0.55x^2 + 0.15x^3

    vector<double> x = {0, 1, 2, 3, 4};
    vector<double> y = {1.42, 0.9, 1.48, 3.16, 5.96};

    double a, b, c, d;
    cubicFit(x, y, a, b, c, d);
    printEquation(a, b, c, d);

    return 0;
}
