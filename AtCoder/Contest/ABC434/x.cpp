#include <bits/stdc++.h>
using namespace std;

const int M = 1e6 + 5;
int tr[M][26], sz[M], tot;
bool endn[M];

void ins(string& s) {
    int u = 0;
    for (char c : s) {
        int i = c - 'a';
        if (!tr[u][i]) tr[u][i] = ++tot;
        u = tr[u][i];
    }
    endn[u] = true;
}

void dfs(int u) {
    sz[u] = endn[u];
    for (int i = 0; i < 26; i++) {
        if (tr[u][i]) {
            dfs(tr[u][i]);
            sz[u] += sz[tr[u][i]];
        }
    }
}

bool ask(string& t) {
    cout << "? " << t << endl;
    int r; cin >> r;
    return r;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        ins(s);
    }

    dfs(0);

    int u = 0;
    string cur = "";

    while (sz[u] > 1) {
        int big = -1, ch = -1;
        for (int i = 0; i < 26; i++) {
            int v = tr[u][i];
            if (v && sz[v] > big) {
                big = sz[v];
                ch = i;
            }
        }

        string q = cur + (char)(ch + 'a');
        if (ask(q)) {
            cur = q;
            u = tr[u][ch];
        } else {
            sz[u] -= sz[tr[u][ch]];
            tr[u][ch] = 0;
        }
    }

    while (!endn[u]) {
        for (int i = 0; i < 26; i++) {
            if (tr[u][i]) {
                cur += (char)(i + 'a');
                u = tr[u][i];
                break;
            }
        }
    }

    cout << "! " << cur << endl;
    return 0;
}