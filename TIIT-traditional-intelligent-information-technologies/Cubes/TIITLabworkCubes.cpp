#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, k; // n — число вершин в первой доле(буквы введенного слова), k - во второй доле(кубики с буквами)
vector < vector<int> > g; //список рёбер из вершины v первой доли (т.е. список номеров вершин, в которые ведут эти рёбра из v)
vector<bool> used; //массив used - массив "посещённостей" вершин в обходе в глубину

vector<int> mt;
// массив mt — содержит в себе информацию о текущем паросочетании
// для вершин второй доли: mt[i] - это номер вершины первой доли, связанной ребром с вершиной i второй доли
// (или -1, если никакого ребра паросочетания из i не выходит).



bool bfs(int v)
{
    if (used[v])
        return false;

    used[v] = true;
    for (size_t i = 0; i < g[v].size(); i++)
    {
        int t = g[v][i];

        if (mt[t] == -1 || bfs(mt[t]))
        {
            mt[t] = v;
            return true;
        }
    }
    return false;
}


int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // input
    string word, cube;
    cin >> k >> word;
    n = word.size();
    if (k < n)
    {
        cout << "NO" << "\n";
        return 0;
    }

    for (int i = 0; i < k; i++)
    {
        vector <int> nodes;
        g.push_back(nodes);
    }

    for (int i = 0; i < k; i++)
    {
        cin >> cube;
        for (size_t c = 0; c < cube.size(); c++)
        {
            for (int w = 0; w < n; w++)
            {
                if (cube[c] == word[w])
                {
                    int was = 0;
                    for (size_t e = 0; e < g[i].size(); e++)
                    {
                        if (g[i][e] == w)
                        {
                            was = 1;
                            break;
                        }
                    }
                    if (was == 0)
                        g[i].push_back(w);
                }
            }
        }

    }

    // check
    /*for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < g[i].size(); j++)
            cout << g[i][j] + 1<< " ";
        cout << "\n";
    }
    cout << "\n";*/

    // algorithm
    mt.assign(n, -1);
    for (int v = 0; v < k; v++)
    {
        used.assign(k, false);
        bfs(v);
    }

    // output
    int h = 0;
    for (int i = 0; i < n; i++)
        if (mt[i] > -1)
            h++;

    if (h == n)
    {
        cout << "YES" << "\n";
        for (int i = 0; i < n; i++)
            cout << mt[i] + 1 << " ";
        cout << "\n";
    }
    else
        cout << "NO" << "\n";
    return 0;
}
