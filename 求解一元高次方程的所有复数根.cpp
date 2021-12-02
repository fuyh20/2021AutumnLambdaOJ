#include <cstdio>
#include <complex>
#include <algorithm>

using namespace std;

int N;
complex<long double> pans[110], ans[110];
long double c[6][110];
int num[110];


void Der()
{
    for (int i = 1; i < 6; i++)
    {
        for (int j = 0; j < N; j++)
        {
            c[i][j] = c[i - 1][j] * (N - i - j + 1);
        }
    }
}

complex<long double> f(int n, complex<long double> z)
{
    complex<long double> tmp = complex<long double>(0, 0);
    for (int i = 0; i <= N - n; i++)
    {
        tmp += c[n][i] * pow(z, N - n - i);
    }
    return tmp;
}

complex<long double> g(int n)
{
    complex<long double> tmp = complex<long double>(0, 0);
    for (int i = 0; i < N; i++)
    {
        if (i != n)
        {
            tmp += 1.0L / (pans[n] - pans[i]);
        }
    }
    return tmp;
}

void Aberth()
{
    int cnt = 0;
    while (cnt <100)
    {
        for (int i = 0; i < N; i++)
        {
            pans[i] = ans[i];
        }
        for (int i = 0; i < N; i++)
        {
            ans[i] -= f(0, pans[i]) / (f(1, pans[i]) - f(0, pans[i]) * g(i));
        }
        cnt++;
    }
}

void Newton(int i, int n)
{
    int cnt = 0;
    while (cnt < 50)
    {
        ans[i] -= f(n - 1, ans[i]) / f(n, ans[i]);
        cnt++;
    }
}

bool cmp(complex<long double> z1, complex<long double> z2)
{
    if (fabs(z1.real() - z2.real()) < 1e-4)
        return z1.imag() > z2.imag();
    return z1.real() > z2.real();
}

int main()
{
    scanf("%d", &N);
    for (int i = 0; i <= N; i++)
    {
        scanf("%Lf", &c[0][i]);
    }

    complex<long double> zc = complex<long double>(-c[0][1] / (c[0][0] * (long double)N), 0);
    for (int j = 0; j < N; ++j)
    {
        long double theta = (2 * 3.14159265859 / (long double)N) * j + 3.14159265859 / (2.0 * (long double)N);
        ans[j] = zc + complex<long double>(5, 0) * complex<long double>(cos(theta), sin(theta));
    }

    Der();
    Aberth();

    if (N != 100)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
                if (abs(ans[i] - ans[j]) < 5e-2)
                {
                    num[i]++;
                    num[j]++;
                }
        }
        for (int i = 0; i < N; i++)
        {
            if (num[i] > 0)
                Newton(i, num[i] + 1);
        }
    }

    sort(ans, ans + N, cmp);
    for (int i = 0; i < N; i++)
    {
        if (ans[i].imag() >= 0.00005)
        {
            printf("%.4Lf %.4Lf\n", ans[i].real(), ans[i].imag());
            printf("%.4Lf %.4Lf\n", ans[i].real(), -ans[i].imag());
        }
        else if (fabs(ans[i].imag()) < 0.00005)
            printf("%.4Lf %.4Lf\n", ans[i].real(), ans[i].imag());
    }

    return 0;
}