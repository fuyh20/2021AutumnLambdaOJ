#include <cstdio>

using namespace std;

int *left, *right; // 分别记录数的左右两侧
int N, M, K, L;
bool exist[200000] = {0};
void Insert(int x, int y, int direction) // 插入元素
{
    exist[x] = true;
    if (direction == 1) // x插在y的右侧
    {
        right[x] = right[y];
        left[right[y]] = x;
        right[y] = x;
        left[x] = y;
    }
    else if (direction == 0) // x插在y的左侧
    {
        left[x] = left[y];
        right[left[y]] = x;
        left[y] = x;
        right[x] = y;
    }
}

void Remove(int n) // 取出元素
{
    right[left[n]] = right[n];
    left[right[n]] = left[n];
    left[n] = right[n] = 0;
}

void Swap(int x, int y) // 交换元素
{
    int temp;
    if ((right[x] != y) && (left[x] != y))
    {
        left[right[x]] = y;
        right[left[x]] = y;
        left[right[y]] = x;
        right[left[y]] = x;
        temp = left[x];
        left[x] = left[y];
        left[y] = temp;
        temp = right[x];
        right[x] = right[y];
        right[y] = temp;

    }
    else if(right[x] == y)
    {
        right[left[x]] = y;
        left[right[y]] = x;
        left[y] = left[x];
        left[x] = y;
        right[x] = right[y];
        right[y] = x;
    }
    else if(left[x] == y)
    {
        right[left[y]] = x;
        left[right[x]] = y;
        left[x] = left[y];
        right[y] = right[x];
        right[x] = y;
        left[y] = x;
    }
}

void Reverse() // 翻转
{
    int *temp;
    temp = right;
    right = left;
    left = temp;
}

void Print()
{
    int cnt = 0, n = 0;
    for (int i = 1; i <= N; i++)
    {
        if (exist[i])
        {
            n = i;
            cnt++;
        }
    }
    if (cnt == 1)
        printf("%d ", n);
    for (int i = 1; i <= cnt; i++)
    {
        if ((left[i] == 0) && (right[i] != 0))
        {
            int n = i;
            while (n != 0)
            {
                printf("%d ", n);
                n = right[n];
            }
            break;
        }
    }
    printf("-1");
}
int main()
{
    scanf("%d%d%d%d", &N, &M, &K, &L);
    right = new int[N + 1]{0};
    left = new int[N + 1]{0};
    int sum = N + M + K + L;

    for (int i = 0; i < sum; i++)
    {
        int mode, x, y, direction, n;
        scanf("%d", &mode);
        switch (mode)
        {
        case 1:
            scanf("%d%d%d", &x, &y, &direction);
            Insert(x, y, direction);
            break;

        case -1:
            scanf("%d%d", &x, &y);
            Swap(x, y);
            break;

        case -2:
            Reverse();
            break;

        case 0:
            scanf("%d", &x);
            Remove(x);
            break;

        default:
            break;
        }
    }
    Print();
    delete left;
    delete right;
    return 0;
}