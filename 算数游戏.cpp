#include <cstdio>

int prime[4] = {2, 3, 5, 7};

int main()
{
    int cnt[4] = {0};
    long long n;
    scanf("%lld", &n);
    if (n == 0)
    {
        printf("-1");
        return 0;
    }
    if (n == 1)
    {
        printf("1");
        return 0;
    }
    for (int i = 0; i < 4; i++)
    {
        while (n % prime[i] == 0)
        {
            n /= prime[i];
            cnt[i]++;
        }
    }
    if (n != 1)
        printf("-1");
    else
    {
        int num4=0, num6=0, num8=0, num9=0;
        num8 = cnt[0] / 3;
        cnt[0] %= 3;
        num9 = cnt[1] / 2;
        cnt[1] %= 2;
        if ((cnt[0] == 2) && (cnt[1] == 1))
        {
            num6++;
            cnt[0]--;
            cnt[1]--;
        }
        num4 = cnt[0] / 2;
        cnt[0] %= 2;
        if ((cnt[0] == 1) && (cnt[1] == 1))
        {
            num6++;
            cnt[0]--;
            cnt[1]--;
        }
        for (int i = 0; i < cnt[0]; i++)
            printf("2");
        for (int i = 0; i < cnt[1]; i++)
            printf("3");
        for (int i = 0; i < num4; i++)
            printf("4");
        for (int i = 0; i < cnt[2]; i++)
            printf("5");
        for (int i = 0; i < num6; i++)
            printf("6");
        for (int i = 0; i < cnt[3]; i++)
            printf("7");
        for (int i = 0; i < num8; i++)
            printf("8");
        for (int i = 0; i < num9; i++)
            printf("9");
    }
    return 0;
}