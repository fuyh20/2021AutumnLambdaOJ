#include <cstdio>

int weights[30000], big[30000];
int ans(int i, int j)
{
    if (j - i == 1)
        return (weights[i] > weights[j] ? weights[i] : weights[j]);
    int a = ans(i, j - 2) + weights[j];
    int b = ans(i + 2, j) + weights[i];
    int c = ans(i + 1, j - 1) + (weights[i] > weights[j] ? weights[i] : weights[j]);
    return ((a > b ? a : b) > c ? (a > b ? a : b) : c);
}

int main()
{
    int N;
    scanf("%d", &N);
    scanf("%d", &weights[0]);
    for (int i = 1; i < N; i++)
    {
        scanf("%d", &weights[i]);
        int j = i - 1;
        big[j] = weights[i] > weights[j] ? weights[i] : weights[j];
    }

    for (int i = 3; i < N; i = i + 2)
    {
        for (int j = 0; j + i < N; j++)
        {
            int a = big[j] + weights[j + i];
            int b = big[j + 2] + weights[j];
            int c = big[j + 1] + (weights[j] > weights[j + i] ? weights[j] : weights[j + i]);
            big[j] = (a > b ? a : b) > c ? (a > b ? a : b) : c;
        }
    }

    printf("%d", big[0]);
    return 0;
}