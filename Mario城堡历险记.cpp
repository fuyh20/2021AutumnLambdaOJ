#include <iostream>
#include <queue>

using namespace std;

int Lx, Ly;
bool map[1010][1010];
short visted[1010][1010][4];
int step = 0;
vector<short> ans;

struct State
{
    int x, y;
    int towards;

    State(int x = 0, int y = 0, int towards = 0) : x(x), y(y), towards(towards) {}

    bool operator!=(const State &s)
    {
        return !(s.x == this->x && s.y == this->y && s.towards == this->towards);
    }
};

struct State START, END;
queue<State> q;

void BFS()
{
    while (!q.empty())
    {
        int x = q.front().x, y = q.front().y, towards = q.front().towards;
        q.pop();

        if ((x == END.x) && (y == END.y) && (towards == END.towards))
        {
            return;
        }

        int flag = 0;
        switch (towards)
        {
        case 1:
            if (y - 1 >= 0 && map[x][y - 1] == 0 && visted[x][y - 1][towards] == 0)
            {
                q.emplace(x, y - 1, towards);
                visted[x][y - 1][towards] = 1;
                flag = 1;
            }
            break;

        case 2:
            if (x - 1 >= 0 && map[x - 1][y] == 0 && visted[x - 1][y][towards] == 0)
            {
                q.emplace(x - 1, y, towards);
                visted[x - 1][y][towards] = 1;
                flag = 1;
            }
            break;

        case 3:
            if (map[x][y + 1] == 0 && visted[x][y + 1][towards] == 0 && y + 1 < Ly)
            {
                q.emplace(x, y + 1, towards);
                visted[x][y + 1][towards] = 1;
                flag = 1;
            }
            break;

        case 4:
            if (map[x + 1][y] == 0 && visted[x + 1][y][towards] == 0 && x + 1 < Lx)
            {
                q.emplace(x + 1, y, towards);
                visted[x + 1][y][towards] = 1;
                flag = 1;
            }
            break;

        default:
            break;
        }

        if (flag)
        {
            switch (towards)
            {
            case 1:
                if (y - 2 >= 0 && map[x][y - 2] == 0 && visted[x][y - 2][towards] == 0)
                {
                    q.emplace(x, y - 2, towards);
                    visted[x][y - 2][towards] = 2;
                }
                break;

            case 2:
                if (x - 2 >= 0 && map[x - 2][y] == 0 && visted[x - 2][y][towards] == 0)
                {
                    q.emplace(x - 2, y, towards);
                    visted[x - 2][y][towards] = 2;
                }
                break;

            case 3:
                if (map[x][y + 2] == 0 && visted[x][y + 2][towards] == 0 && y + 2 < Ly)
                {
                    q.emplace(x, y + 2, towards);
                    visted[x][y + 2][towards] = 2;
                }
                break;

            case 4:
                if (map[x + 2][y] == 0 && visted[x + 2][y][towards] == 0 && x + 2 < Lx)
                {
                    q.emplace(x + 2, y, towards);
                    visted[x + 2][y][towards] = 2;
                }
                break;

            default:
                break;
            }
        }

        int tmp = (towards + 1) > 4 ? 1 : (towards + 1);
        if (visted[x][y][tmp] == 0)
        {
            q.emplace(x, y, tmp);
            visted[x][y][tmp] = 3;
        }

        tmp = (towards - 1) > 0 ? (towards - 1) : 4;
        if (visted[x][y][tmp] == 0)
        {
            q.emplace(x, y, tmp);
            visted[x][y][tmp] = 4;
        }
    }
}

void recall()
{
    State tmp = END;
    while (tmp != START)
    {
        step++;
        int t = 0;
        switch (visted[tmp.x][tmp.y][tmp.towards])
        {
        case 1:
            ans.emplace_back(1);
            if (tmp.towards == 1)
                tmp = State(tmp.x, tmp.y + 1, tmp.towards);
            else if (tmp.towards == 2)
                tmp = State(tmp.x + 1, tmp.y, tmp.towards);
            else if (tmp.towards == 3)
                tmp = State(tmp.x, tmp.y - 1, tmp.towards);
            else if (tmp.towards == 4)
                tmp = State(tmp.x - 1, tmp.y, tmp.towards);
            break;

        case 2:
            ans.emplace_back(2);
            if (tmp.towards == 1)
                tmp = State(tmp.x, tmp.y + 2, tmp.towards);
            else if (tmp.towards == 2)
                tmp = State(tmp.x + 2, tmp.y, tmp.towards);
            else if (tmp.towards == 3)
                tmp = State(tmp.x, tmp.y - 2, tmp.towards);
            else if (tmp.towards == 4)
                tmp = State(tmp.x - 2, tmp.y, tmp.towards);
            break;

        case 3:
            ans.emplace_back(3);
            t = (tmp.towards - 1) > 0 ? (tmp.towards - 1) : 4;
            tmp = State(tmp.x, tmp.y, t);
            break;

        case 4:
            ans.emplace_back(4);
            t = (tmp.towards + 1) > 4 ? 1 : (tmp.towards + 1);
            tmp = State(tmp.x, tmp.y, t);
            break;

        default:
            break;
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin >> Lx >> Ly;
    for (int i = 0; i < Ly; i++)
        for (int j = 0; j < Lx; j++)
            cin >> map[j][i];
    cin >> START.x >> START.y >> START.towards >> END.x >> END.y >> END.towards;

    q.emplace(START);
    visted[START.x][START.y][START.towards] = 1;
    BFS();

    recall();
    cout << step << endl;
    int tmp = ans.size();
    for (int i = tmp - 1; i >= 0; i--)
    {
        switch (ans[i])
        {
        case 1:
            cout << "F" << endl;
            break;
        case 2:
            cout << "F2" << endl;
            break;
        case 3:
            cout << "L" << endl;
            break;
        case 4:
            cout << "R" << endl;
            break;
        default:
            break;
        }
    }
    return 0;
}