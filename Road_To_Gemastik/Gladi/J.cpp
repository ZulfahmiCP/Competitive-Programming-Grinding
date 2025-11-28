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
    int n;
    cin >> n;
    vector<int> x, y;
    map<pair<int, int>, int> mun;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        x.pb(a);
        y.pb(b);
        mun[{a, b}]++;
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    for (int i = 0; i < n/2; i++) {
        int x_min = x[i];
        int x_maks = x[n-1-i];
        int y_min = y[i];
        int y_maks = y[n-1-i];
        if (x_min == x_maks || y_min == y_maks) {
            cout << "TIDAK";
            return 0;
        }
        // cout << x_min << ' ' << x_maks << ' ' << y_min << ' ' << y_maks << endl;
        if (mun[{x_min, y_min}] == 1 && mun[{x_maks, y_maks}] == 1) {
            mun[{x_min, y_min}]--;
            mun[{x_maks, y_maks}]--;
            continue;
        }


        if (mun[{x_min, y_maks}] == 1 && mun[{x_maks, y_min}] == 1) {
            mun[{x_min, y_maks}]--;
            mun[{x_maks, y_min}]--;
            continue;
        }
        cout << "TIDAK";
        return 0;
    }
    cout << "YA";
} 
