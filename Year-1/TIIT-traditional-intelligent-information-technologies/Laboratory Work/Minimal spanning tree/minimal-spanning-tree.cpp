#define _CRT_SECURE_NO_WARNINGS 
#include <iostream> 
#include <vector> 
#include <set> 
#include <fstream> 
#include <string> 
#include <algorithm>

using namespace std;

string INPUT_FILE = "input.txt";
string OUTPUT_FILE = "output.txt";

int n_;
vector<int> p(n_);

int dsu_get(int v) {
    return (v == p[v]) ? v : (p[v] = dsu_get(p[v]));
}

void dsu_unite(int a, int b) {
    a = dsu_get(a);
    b = dsu_get(b);
    if (rand() & 1)
        swap(a, b);
    if (a != b)
        p[a] = b;
}

// входные данные 
const int INF = 1e9; // значение "бесконечность" 

int main(int argc, char* argv[])
{
    freopen(INPUT_FILE.c_str(), "r", stdin);
    freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // create graph
    int n, m;
    cin >> n >> m; n_ = n;
    
    vector <pair <int, pair<int, int>>> g; // вес - вершина 1 - вершина 2
    int aa, bb, cc;
    for (int i = 0; i < m; i++) {
        cin >> aa >> bb >> cc;
        aa--; bb--;
        g.push_back(make_pair(cc, make_pair(aa, bb)));
    }

    // algo
    int cost = 0;
    vector < pair<int, int> > res;

    sort(g.begin(), g.end());
    p.resize(n);
    for (int i = 0; i < n; ++i)
        p[i] = i;
    for (int i = 0; i < m; ++i) {
        int a = g[i].second.first, b = g[i].second.second, l = g[i].first;
        if (dsu_get(a) != dsu_get(b)) {
            cost += l;
            res.push_back(g[i].second);
            dsu_unite(a, b);
        }
    }
    cout << cost;
}