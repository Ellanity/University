#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>

using namespace std;

const int inf = int(1e9) + 10;
const int MaxN = 1000;
const int MaxN1 = MaxN * 2 + 2;

int n, m, nn;
int ans, an;
int c[MaxN1 + 1][MaxN1 + 1];
int f[MaxN1 + 1][MaxN1 + 1];

int qw[MaxN + 1];
int fr[MaxN + 1];

int h, t;
int u[MaxN + 1];

void readData() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> c[1][i + 1];
    }

    for (int i = 1; i <= m; i++) {
        int q;
        cin >> q;

        for (int j = 1; j <= q; j++) {
            int x;
            cin >> x;

            c[x + 1][i + n + 1] = inf;
        }

        cin >> c[i + n + 1][m + 1 + n + 1];
    }

    nn = n;
    n = n + 1 + m + 1;
}

/************************************************
| Построение сети для решения в solve           |
| Поиск максимального потока в графе            |
| http://www.e-maxx-ru.1gb.ru/algo/edmonds_karp |
************************************************/

void solve() {
    int cr = 0;
    int x = 0;
    while (true) {
        h = 1;
        t = 1;
        qw[1] = 1;
        for (int i = 1; i <= MaxN; i++) {
            fr[i] = 0;
        }
        fr[1] = -1;

        while (h <= t && fr[n] == 0) {
            cr = qw[h];
            h++;

            for (int i = 1; i <= n; i++) {
                if (fr[i] == 0 && c[cr][i] - f[cr][i] > 0) {
                    fr[i] = cr;
                    if (i == n) {
                        break;
                    }
                    t++;
                    qw[t] = i;
                }
            }
        }

        if (fr[n] == 0) {
            break;
        }

        x = n;
        cr = inf;

        while (x != 1) {
            if (cr > c[fr[x]][x] - f[fr[x]][x]) {
                cr = c[fr[x]][x] - f[fr[x]][x];
            }

            x = fr[x];
        }

        x = n;
        while (x != 1) {
            f[fr[x]][x] += cr;
            f[x][fr[x]] = -f[fr[x]][x];

            x = fr[x];
        }
    }

    ans = 0;
    for (int i = 1 + nn + 1; i <= m + nn + 1; i++) {
        if (fr[i] == 0) {
            for (int j = 2; j <= nn + 1; j++) {
                if (c[j][i] == inf) {
                    u[j - 1] = 1;
                }
            }
            ans += c[i][n];
        }
    }

    an = 0;
    for (int i = 1; i <= nn; i++) {
        if (u[i]) {
            ans -= c[1][i + 1];
            an++;
        }
    }
}

void outputData() {
    cout << ans << "\n";
    cout << an << "\n";

    for (int i = 1; i <= nn; i++) {
        if (u[i]) {
            cout << i << " ";
        }
    }
}

int main() {
    freopen("gnome.in", "r", stdin);
    freopen("gnome.out", "w", stdout);
    readData();
    solve();
    outputData();
    return 0;
}