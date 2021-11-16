#include <cstdio>

char P[1010][1010];
char S[1010], t[1010], ans[1010];
int is[1010];
int m, n, flag;

void Guass()
{
    for (int i = 0; i < n; i++)
        is[i] = 0;
    int r = 0;
    for (int i = 0; i < n; i++)
    {
        int k = r;
        while (!P[k][i] && k < n)
            k++;
        if (k != r && k < n)
        {
            for (int j = i; j < n; j++)
            {
                int tmp;
                tmp = P[r][j], P[r][j] = P[k][j], P[k][j] = tmp;
            }
            int tmp;
            tmp = t[r], t[r] = t[k], t[k] = tmp;
        }
        else if (k == n)
        {
            is[i] = 1;
            continue;
        }

        for (int a = r + 1; a < n; a++)
        {
            if (P[a][i])
            {
                for (int j = i; j < n; j++)
                {
                    P[a][j] = P[a][j] ^ P[r][j];
                }
                t[a] = t[a] ^ t[r];
            }
        }
        r++;
    }

    int j = n - 1;
    while (j >= 0 && is[j])
    {
        if (t[j])
        {
            flag = 1;
            return;
        }
        j--;
    }

    for (int i = n - 1; i > -1; i--)
    {
        if (is[i])
        {
            ans[i] = 0;
            continue;
        }
        char sum = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (P[i][j])
                sum ^= ans[j];
        }
        ans[i] = t[i] ^ sum;
    }
}

int main()
{
    scanf("%d", &m);
    while (m--)
    {
        flag = 0;
        int cnt = 0;
        scanf("%d", &n);
        char c = getchar();
        while (c != '0' && c != '1')
            c = getchar();
        while ((c == '0' || c == '1') && cnt < n)
        {
            S[cnt++] = c - '0';
            c = getchar();
        }

        cnt = 0;
        while (c != '0' && c != '1')
            c = getchar();
        while ((c == '0' || c == '1') && cnt < n)
        {
            t[cnt++] = c - '0';
            c = getchar();
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                P[i][j] = S[(j + i) % n];

        Guass();

        if (flag)
            printf("N\n");
        else
        {
            int f = 0, p = -1;
            printf("A");
            for (int i = 0; i < n; i++)
            {
                if (ans[i])
                {
                    f = i;
                    int num = (n + i - p) % n;
                    for (int j = 0; j < num; j++)
                    {
                        printf("A");
                    }
                    printf("B");
                    p = i;
                }
            }
            for (int j = 0; j < n - f; j++)
            {
                printf("A");
            }
            printf("\n");
        }
    }
    return 0;
}