#include <bits/stdc++.h>
using namespace std;

void differenceTable(vector<double> &x, vector<double> &y, vector<vector<double>> &diffTable)
{
    int n = x.size();

    for (int i = 0; i < n; i++)
    {
        diffTable[i][0] = y[i];
    }

    for (int j = 1; j < n; j++)
    {
        for (int i = 0; i < n - j; i++)
        {
            diffTable[i][j] = diffTable[i + 1][j - 1] - diffTable[i][j - 1];
        }
    }

    // for (int j = 1; j < n; j++)
    // {
    //     for (int i = 0; i < n - j; i++)
    //     {
    //         cout<<diffTable[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
}

double forwardInterpolation(vector<double> &x, vector<double> &y, double x0)
{
    int n = x.size();
    vector<vector<double>> diffTable(n, vector<double>(n));

    differenceTable(x, y, diffTable);

    //showing the table
    //first row represents del values

    // for (auto row : diffTable)
    // {
    //     for (auto val : row)
    //     {
    //         cout << val << " ";
    //     }
    //     cout << endl;
    // }

    double h = x[1] - x[0];
    double s = (x0 - x[0]) / h;
    double value = diffTable[0][0];

    for (int i = 1; i < n; i++)
    {
        double term = diffTable[0][i];
        for (int j = 0; j < i; j++)
        {
            term *= (s - j) / (j + 1);
        }
        value += term;
    }

    return value;
}

int main()
{
    vector<double> x = {10, 20, 30, 40, 50};
    vector<double> y = {0.174, 0.342, 0.5, 0.643, 0.766};  
    //y=sin(x)

    double x0;
    cout << "Enter the value of x0: "<<endl;
   // cin >> x0;
x0 = 25;
    double result = forwardInterpolation(x, y, x0);
    cout << "The interpolated value at x = " << x0 << " is: " << setprecision(5) << fixed << result << endl;

    return 0;
}