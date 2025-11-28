#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long 
#define pb push_back
#define ppb pop_back
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define sz(x) (int)x.size()
#define endl '\n'

int main() {

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, k;
    vector<vector<int>> tim;
    cin >> n >> k;
    vector<int> skor(n+1, 0);
    for (int i = 0; i < k; i++) {
        int m;
        cin >> m;
        for (int j = 0; j < m; j++) {
            vector<int> b;
            for (int l = 0; l < 3; l++) {
                int a;
                cin >> a;
                skor[a]++;
                b.push_back(a);
            }
            tim.push_back(b);
        }
    }
    vector<bool> sedia(n+1, true);

    int hasil = 0;

    for (int p = 0; p <= 500 && sz(tim) > 0; p++) {
        int idx_t = -1;
        int sko_ma = 1e9;
        for (int i = 1; i <= n; i++) {
            if (skor[i] > 0) {
                if (skor[i] < sko_ma) {
                    idx_t = i;
                    sko_ma = skor[i];
                }
            }
        }
        if (idx_t == -1) {
            break;
        }
        // cout << idx_t << endl;
        // for (int i = 1; i <= n; i++) {
        //     cout << skor[i] << ' ';
        // }
        // cout << endl;
        vector<bool> muncul(sz(tim), false);
        vector<int> l_t;
        for (int i = 0; i < sz(tim); i++) {
            for (int j = 0; j < 3; j++) {
                if (tim[i][j] == idx_t) {
                    l_t.push_back(i);
                    muncul[i] = true;
                } 
            }
        }

        int idx_tim = -1;
        int skor_tim = -2;
        for (int i : l_t) {
            int s_t = 0;
            for (int j = 0; j < 3; j++) {
                s_t += skor[tim[i][j]];
                if (tim[i][j] != idx_t) {
                    if (skor[tim[i][j]] == 1) {
                        s_t= -1;
                        break;
                    }
                }
            }
            if (s_t > skor_tim) {
                idx_tim = i;
                skor_tim = s_t;
            }
            if (s_t == skor[idx_t]) {
                idx_tim = i;
                break;
            }
        }
        hasil++;
        skor[idx_t] = 1;
        vector<vector<int>> tim_baru;
        for (int i = 0; i < sz(tim); i++) {
            if (i == idx_tim) {
                for (int j = 0; j < 3; j++) {
                    skor[tim[i][j]]--;
                }
            } else {
                tim_baru.push_back(tim[i]);
            }
        }
        tim = tim_baru;
        for (int i = 1; i <= n; i++) {
            if (skor[i] < 0) skor[i] = 0;
        }
    } 
    cout << hasil;
    return 0;
}
