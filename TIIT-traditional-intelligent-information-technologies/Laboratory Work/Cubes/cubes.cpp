#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, k; // n � ����� ������ � ������ ����(����� ���������� �����), k - �� ������ ����(������ � �������)
vector < vector<int> > g; //������ ���� �� ������� v ������ ���� (�.�. ������ ������� ������, � ������� ����� ��� ���� �� v)
vector<bool> used; //������ used - ������ "�������������" ������ � ������ � �������

vector<int> mt;
// ������ mt � �������� � ���� ���������� � ������� �������������
// ��� ������ ������ ����: mt[i] - ��� ����� ������� ������ ����, ��������� ������ � �������� i ������ ����
// (��� -1, ���� �������� ����� ������������� �� i �� �������).



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
