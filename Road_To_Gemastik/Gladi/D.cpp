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

ll mod = 1e9 + 7;

int main() {

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    ll n, m;
    cin >> n >> m;
    ll hasil = 1;
    vector<int> mun(n+1, 0);
    for (int i = 0; i < m; i++) {
        int a;
        cin >> a;
        mun[a]++;
    }
    int d = 0;
    for (int i = n; i >= 1; i--) {
        if (mun[i] == 0) {
            hasil *= d;
            hasil %= mod;
        } else {
            d++;
        }
    }
    // cout << "TES 1";
    hasil %= mod;
    cout << hasil;
    return 0;
}
