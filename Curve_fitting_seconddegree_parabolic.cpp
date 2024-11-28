#include <iostream>
#include <vector>

using namespace std;

void calculateSums(const vector<double> &x, const vector<double> &y,
                   double &sumX, double &sumY, double &sumX2, double &sumX3,
                   double &sumX4, double &sumXY, double &sumX2Y)
{
    sumX = 0;
    sumY = 0;
    sumX2 = 0;
    sumX3 = 0;
    sumX4 = 0;
    sumXY = 0;
    sumX2Y = 0;

    int n = x.size();
    for (int i = 0; i < n; i++)
    {
        double x2 = x[i] * x[i];
        double x3 = x2 * x[i];
        double x4 = x3 * x[i];

        sumX += x[i];
        sumY += y[i];
        sumX2 += x2;
        sumX3 += x3;
        sumX4 += x4;
        sumXY += x[i] * y[i];
        sumX2Y += x2 * y[i];
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

void parabolicFit(const vector<double> &x, const vector<double> &y, double &a, double &b, double &c)
{
    double sumX, sumY, sumX2, sumX3, sumX4, sumXY, sumX2Y;
    calculateSums(x, y, sumX, sumY, sumX2, sumX3, sumX4, sumXY, sumX2Y);

    vector<vector<double>> A = {
        {static_cast<double>(x.size()), sumX, sumX2},
        {sumX, sumX2, sumX3},
        {sumX2, sumX3, sumX4}};
    vector<double> B = {sumY, sumXY, sumX2Y};

    vector<double> coefficients = solveLinearSystem(A, B);
    a = coefficients[0];
    b = coefficients[1];
    c = coefficients[2];
}

void printEquation(double a, double b, double c)
{
    cout << "Fitted parabola equation: y = " << a << " + " << b << "x + " << c << "x^2" << endl;
}

int main()
{

    // solution
    // y = 1.42 - 1.07x + 0.55x^2

    vector<double> x = {0, 1, 2, 3, 4};
    vector<double> y = {1.42, 0.9, 1.48, 3.16, 5.96};

    double a, b, c;
    parabolicFit(x, y, a, b, c);
    printEquation(a, b, c);

    return 0;
}
