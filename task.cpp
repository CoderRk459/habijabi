#include <bits/stdc++.h>
using namespace std;

void calculateSums2ND(vector<double> &x, vector<double> &y, double &sumX, double &sumY, double &sumX2, double &sumX3, double &sumX4, double &sumXY, double &sumX2Y)
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

void calculateSums3RD(vector<double> &x, vector<double> &y,
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

void parabolicFit(vector<double> &x, vector<double> &y, double &a, double &b, double &c)
{
    double sumX, sumY, sumX2, sumX3, sumX4, sumXY, sumX2Y;
    calculateSums2ND(x, y, sumX, sumY, sumX2, sumX3, sumX4, sumXY, sumX2Y);

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
void cubicFit(vector<double> &x, vector<double> &y, double &a, double &b, double &c, double &d)
{
    double sumX, sumY, sumX2, sumX3, sumX4, sumX5, sumX6, sumXY, sumX2Y, sumX3Y;
    calculateSums3RD(x, y, sumX, sumY, sumX2, sumX3, sumX4, sumX5, sumX6, sumXY, sumX2Y, sumX3Y);

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

void printEquation3(double a, double b, double c, double d)
{
    cout << "cubic equation: y = " << a << " + " << b << "x + " << c << "x^2 + " << d << "x^3" << endl;
}
void printEquation2(double a, double b, double c)
{
    cout << "Equation: y = " << a << " + " << b << "x + " << c << "x^2" << endl;
}

// 16.9414 + 7.5247x + -0.971906x^2 + 0.0350945x^3
double func3(double x)
{
    return 16.9414 + 7.5247 * x + -0.971906 * x * x + 0.0350945 * x * x * x;
}
double func2(double x)
{
    return 21.7318 + 3.82223 * x + -0.287562 * x * x;
}

int main()
{
    vector<double> x = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    vector<double> y = {23.8, 26.6, 33.1, 35.3, 34.5, 34.1, 32.5, 32.2, 32.2, 31.3, 29.3, 27.1};

    double a, b, c, d;
    parabolicFit(x, y, a, b, c);
    printEquation2(a, b, c);

    cubicFit(x, y, a, b, c, d);
    printEquation3(a, b, c, d);

    vector<double> test = {27.1, 31.3, 33.0, 36.7, 35.7, 35.0, 33.1, 32.5, 32.1, 32.1, 30.0, 25.3};
    vector<double> error2(test.size());
    double sum = 0;

    for (int i = 0; i < test.size(); i++)
    {
        error2[i] = abs(func2(x[i]) - test[i]);
        sum += error2[i];
    }
    cout << "Second error : ";

    cout << sum / 12 << endl;

    vector<double> error3(test.size());
    sum = 0;

    for (int i = 0; i < test.size(); i++)
    {
        error3[i] = abs(func3(x[i]) - test[i]);
        sum += error3[i];
    }
    cout << "Third error : ";
    cout << sum / 12 << endl;

    vector<double> errorFinal(test.size());

    for (int i = 0; i < test.size(); i++)
    {
        errorFinal[i] = error2[i] - error3[i];
    }
    cout << endl;
    return 0;
}
