#include <cstdio>
#include <cstring>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
using namespace std;

int N;
int ans1, ans2;
int a[1000010];
int dp[12][4][2];

int sum()
{
    int tmp = 0;
    for (int i = 0; i < N; i++)
    {
        tmp += a[i];
    }
    return tmp;
}

void get_ans1()
{
    dp[0][1][1] = a[0];
    for (int i = 1; i < N; i++)
    {
        dp[i][1][0] = MAX(dp[i - 1][1][1], dp[i - 1][1][0]);
        dp[i][1][1] = MAX(dp[i - 1][1][1] + a[i], a[i]);
        dp[i][2][0] = MAX(dp[i - 1][2][1], dp[i - 1][2][0]);
        dp[i][2][1] = MAX(dp[i - 1][2][1], MAX(dp[i - 1][1][0], dp[i - 1][1][1])) + a[i];
        dp[i][3][0] = MAX(dp[i - 1][3][0], dp[i - 1][3][1]);
        dp[i][3][1] = MAX(dp[i - 1][3][1], MAX(dp[i - 1][2][1], dp[i - 1][2][0])) + a[i];
    }
    for (int i = 1; i < 4; i++)
    {
        ans1 = MAX(ans1, dp[N - 1][i][0]);
        ans1 = MAX(ans1, dp[N - 1][i][1]);
    }
}

void get_ans2()
{
    dp[0][1][1] = a[0];
    for (int i = 1; i < N; i++)
    {
        dp[i][1][0] = MIN(dp[i - 1][1][1], dp[i - 1][1][0]);
        dp[i][1][1] = MIN(dp[i - 1][1][1] + a[i], a[i]);
        dp[i][2][0] = MIN(dp[i - 1][2][1], dp[i - 1][2][0]);
        dp[i][2][1] = MIN(dp[i - 1][2][1], MIN(dp[i - 1][1][0], dp[i - 1][1][1])) + a[i];
        dp[i][3][0] = MIN(dp[i - 1][3][0], dp[i - 1][3][1]);
        dp[i][3][1] = MIN(dp[i - 1][3][1], MIN(dp[i - 1][2][1], dp[i - 1][2][0])) + a[i];
    }

    for (int i = 1; i < 4; i++)
    {
        ans2 = MIN(ans2, dp[N - 1][i][0]);
        ans2 = MIN(ans2, dp[N - 1][i][1]);
    }
    ans2 = sum() - ans2;
}

int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);

    get_ans1();
    memset(dp, 0, sizeof(dp));
    get_ans2();

    printf("%d\n", ans1 > ans2 ? ans1 : ans2);

    return 0;
}