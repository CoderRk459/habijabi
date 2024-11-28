#include<bits/stdc++.h>
using namespace std;
int a[1005][1005];
int n;
void gauss_elimination()
{
    for (int j = 1;j < n;j++)
    {
        for (int i = n;i > j;i--)
        {
            if (a[i][j] == 0) continue;
            int lcm = a[j][j] * a[i][j] / __gcd(a[j][j], a[i][j]);
            int up = lcm / a[j][j], nic = lcm / a[i][j];
            for (int k = 1;k <= n + 1;k++) a[i][k] = up * a[j][k] - nic * a[i][k];
        }
    }
}
void Jordan_elimination()
{
    for (int j = n;j > 1;j--)
    {
        for (int i = 1;i < j;i++)
        {
            if (a[i][j] == 0) continue;
            int lcm = a[j][j] * a[i][j] / __gcd(a[j][j], a[i][j]);
            int nic = lcm / a[j][j], up = lcm / a[i][j];
            for (int k = 1;k <= n + 1;k++) a[i][k] = nic * a[j][k] - up * a[i][k];
        }
    }
}
void row_echelon()
{
    for (int i = 1;i <= n;i++) a[i][n + 1] /= a[i][i], a[i][i] = 1;
}
int main()
{
    n = 4;
    for (int i = 1;i <= n;i++)
        for (int j = 1;j <= n + 1;j++) cin >> a[i][j];
    gauss_elimination();
    Jordan_elimination();
    row_echelon();
    cout << endl;
    for (int i = 1;i <= n;i++)
    {
        for (int j = 1;j <= n + 1;j++) cout << a[i][j] << ' ';
        cout << endl;
    }

}
/*
1 2 -1 1 6
-1 1 2 -1 3
2 -1 2 2 14
1 1 -1 2 8
*/
/*
1 1 1 -1 4
1 3 1 -2 8
5 1 1 -3 4
5 -1 3 -1 2
*/
