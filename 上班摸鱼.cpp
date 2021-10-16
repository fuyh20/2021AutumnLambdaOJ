// 利用数组构建KDtree,每一个数组元素维护着从left~right的数据（它的子孙）
// 利用优先队列维护第k个最远点
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;

int root, cnt, split;

inline int read()
{
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
}

struct Node
{
    int data[2], id;
    bool operator<(const Node &x) const // 重载小于号，便于优先队列排序
    {
        return data[split] < x.data[split];
    }
} node[100010];

struct Tree
{
    int leftChild, rightChild, Max[2], Min[2], id; // 左子树，右子树，该树所在的范围，结点的id
    Node v;                                        // 该树的根节点
} T[100010];

struct Q
{
    int id;
    ll val;
    Q() {}
    Q(int a, ll b) : id(a), val(b) {}
    bool operator<(const Q &x) const
    {
        if (val == x.val)
            return id < x.id;
        return val > x.val;
    }
    bool operator>(const Q &x) const
    {
        if (val == x.val)
            return id < x.id;
        return val > x.val;
    }
};

priority_queue<Q> q;

void Up(int root) // 估计以root为根的树据范围（矩形边界）
{
    for (int i = 0; i < 2; i++)
    {
        T[root].Max[i] = T[root].Min[i] = T[root].v.data[i];
        if (T[root].leftChild)
        {
            T[root].Max[i] = max(T[root].Max[i], T[T[root].leftChild].Max[i]);
            T[root].Min[i] = min(T[root].Min[i], T[T[root].leftChild].Min[i]);
        }
        if (T[root].rightChild)
        {
            T[root].Max[i] = max(T[root].Max[i], T[T[root].rightChild].Max[i]);
            T[root].Min[i] = min(T[root].Min[i], T[T[root].rightChild].Min[i]);
        }
    }
}

void Build(int &root, int left, int right, int d) // 构造KDtree,root根节点,left数据的左边界，right数据的右边界
{
    if (left > right)
        return;
    root = ++cnt;
    int mid = left + right >> 1;
    split = d;
    nth_element(node + left, node + mid, node + right + 1);
    T[root].v = node[mid];
    T[root].id = node[mid].id;
    Build(T[root].leftChild, left, mid - 1, d ^ 1);
    Build(T[root].rightChild, mid + 1, right, d ^ 1);
    Up(root);
}

ll sqr(ll x) { return x * x; }

ll dist(int root, Node v)
{
    ll tmp = 0;
    for (int i = 0; i < 2; i++)
        tmp += sqr(max(abs(v.data[i] - T[root].Max[i]), abs(v.data[i] - T[root].Min[i])));
    return tmp;
}

ll dist(int x1, int y1, int x2, int y2)
{
    return (1ll * (x1 - x2) * (x1 - x2) + 1ll * (y1 - y2) * (y1 - y2));
}

void query(int root, Node v)
{
    Q tmp = Q(T[root].id, dist(v.data[0], v.data[1], T[root].v.data[0], T[root].v.data[1]));
    if (tmp > q.top())
    {
        q.pop();
        q.emplace(tmp);
    }

    ll leftDist = -2, rightDist = -2;
    if (T[root].leftChild)
        leftDist = dist(T[root].leftChild, v);
    if (T[root].rightChild)
        rightDist = dist(T[root].rightChild, v);

    if (leftDist < rightDist)
    {
        if (rightDist >= q.top().val)
            query(T[root].rightChild, v);
        if (leftDist >= q.top().val)
            query(T[root].leftChild, v);
    }
    else
    {
        if (leftDist >= q.top().val)
            query(T[root].leftChild, v);
        if (rightDist >= q.top().val)
            query(T[root].rightChild, v);
    }
}

int main()
{
    int n, m;
    n = read();
    m = read();
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 2; j++)
            node[i].data[j] = read();
        node[i].id = i - 1;
    }
    Build(root, 1, n, 0);
    while (m--)
    {
        int k;
        Node w;
        w.data[0] = read();
        w.data[1] = read();
        k = read();
        while (!q.empty())
            q.pop();
        while (k--)
            q.emplace(Q(0, -1));
        query(root, w);
        printf("%d\n", q.top().id);
    }
    return 0;
}