#pragma GCC optimize(3)
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

int N;
double m = 9999, prem = 0, eps = 0.0000001;
double A[1000][1000], B[1000][1000];
double v[1000], u[1000];

void P()
{
    for (int i = 0; i < N; i++)
    {
        v[i] = 0;
        for (int j = 0; j < N; j++)
            v[i] += A[i][j] * u[j];
    }
}

void S_P(double a)
{
    for (int i = 0; i < N; i++)
        u[i] = a * v[i];
}

void LU()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            double tmp = A[j][i] / A[i][i];
            for (int k = i; k < N; k++)
                A[j][k] -= tmp * A[i][k];
        }
    }
    for (int i = 0; i < N; i++)
    {
        double tmp = sqrt(A[i][i]);
        for (int j = i; j < N; j++)
        {
            A[i][j] /= tmp;
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            B[i][j] = A[j][i];
    }
}

void solve()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            B[i][j] = A[i][j];
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            double tmp = B[j][i] / B[i][i];
            for (int k = i; k < N; k++)
                B[j][k] -= tmp * B[i][k];
            u[j] -= tmp * u[i];
        }
    }

    for (int i = N - 1; i > -1; i--)
    {
        double tmp = u[i];
        for (int j = N - 1; j > i; j--)
            tmp -= v[j] * B[i][j];
        v[i] = tmp / B[i][i];
    }
}

void solve1()
{
    double w[1010] = {0};
    for (int i = 0; i < N; i++)
    {
        double tmp = u[i];
        for (int j = 0; j < i; j++)
            tmp -= w[j] * B[i][j];
        w[i] = tmp / B[i][i];
    }
    
    for (int i = N - 1; i > -1; i--)
    {
        double tmp = w[i];
        for (int j = N - 1; j > i; j--)
            tmp -= v[j] * A[i][j];
        v[i] = tmp / A[i][i];
    }
}

void Power()
{
    for (int i = 0; i < N; i++)
        u[i] = i;
    while (fabs(m - prem) / prem > eps)
    {
        prem = m;
        P();
        m = *max_element(v, v + N);
        S_P(1 / m);
    }
}

void I_Power()
{
    while (fabs(m - prem) / prem > eps)
    {
        prem = m;
        solve1(); 
        for (int i = 0; i < N; i++)

        m = *max_element(v, v + N);
        S_P(1 / m);
    }
}

int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%lf", &A[i][j]);
        }
    }
    Power();
    cout << setprecision(4) << m << ' ';
    m = 9999;
    prem = 0;
    for (int i = 0 ; i< N; i++)
        u[i] = A[i][i];
    LU();
    I_Power();
    cout << 1 / m;
    return 0;
}