#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

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

struct edge
{
    int v, w;
    edge(int v, int w) : v(v), w(w) {}
};

struct node
{
    int u, dist;
    node(int u, int dist) : u(u), dist(dist) {}
    bool operator<(const node &x) const { return dist > x.dist; }
};

vector<edge> e[30010];
priority_queue<node> q;
int dist[30010];
bool isV[30010];

vector<int> front[30010];
int S, D;
int n = 0, m = 0;

void addEdge(int u, int v, int w)
{
    e[u].emplace_back(edge(v, w));
    e[v].emplace_back(edge(u, w));
};

void Dijkstra()
{
    dist[S] = 0;
    q.emplace(node(S, 0));
    while (!q.empty())
    {
        node tmp = q.top();
        q.pop();
        if (isV[tmp.u])
            continue;
        isV[tmp.u] = true;
        auto len = e[tmp.u].size();
        for (int i = 0; i < len; i++)
        {
            if (dist[e[tmp.u][i].v] > dist[tmp.u] + e[tmp.u][i].w)
            {
                dist[e[tmp.u][i].v] = dist[tmp.u] + e[tmp.u][i].w;
                front[e[tmp.u][i].v].clear();
                front[e[tmp.u][i].v].emplace_back(tmp.u);
                if (!isV[e[tmp.u][i].v])
                    q.emplace(node(e[tmp.u][i].v, dist[e[tmp.u][i].v]));
            }
            else if (dist[e[tmp.u][i].v] == dist[tmp.u] + e[tmp.u][i].w)
            {
                dist[e[tmp.u][i].v] = dist[tmp.u] + e[tmp.u][i].w;
                front[e[tmp.u][i].v].emplace_back(tmp.u);
            }
        }
    }
}

void del(int i)
{
    if (dist[i] != 0)
    {
        int num1 = front[i].size();
        for (int j = 0; j < num1; j++)
        {
            int num2 = e[i].size();
            for (int k = 0; k < num2; k++)
            {
                if (e[i][k].v == front[i][j])
                {
                    e[i].erase(e[i].begin() + k);
                    int num3 = e[front[i][j]].size();
                    for (int a = 0; a < num3; a++)
                    {
                        if (e[front[i][j]][a].v == i)
                        {
                            e[front[i][j]].erase(e[front[i][j]].begin() + a);
                            break;
                            break;
                        }
                    }
                }
            }
            del(front[i][j]);
        }
    }
}

void PrintSP(int S, int D)
{
    if (D != S)
    {
        PrintSP(S, front[D].front());
        printf("%d\n", D);
    }
}

void ans(int S, int D)
{
    printf("start\n%d\n", S);
    PrintSP(S, D);
    printf("end\n");
    printf("%d\n", dist[D]);
}

int main()
{
    n = read(), m = read();
    for (int i = 0; i < n; i++)
        dist[i] = 0x7fffffff;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        u = read(), v = read(), w = read();
        addEdge(u, v, w);
    }
    S = read(), D = read();
    Dijkstra();
    ans(S, D);

    del(D);
    for (int i = 0; i < n; i++)
    {
        dist[i] = 0x7fffffff;
        isV[i] = false;
    }
    Dijkstra();
    if (dist[D] != 0x7fffffff)
        ans(S, D);
    return 0;
}