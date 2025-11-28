#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll mod = 1e9 + 7;

void solve() {
    ll n, m;
    cin >> n >> m;
    if (n == 1) {
        cout << 1 << endl;
        return;
    }
    if (m == 0) {
        ll hasil = ((n-1)*2)*((n-1)*2);
        hasil %= mod;
        cout << hasil << endl;
        return;
    }
    vector<pair<ll, ll>> b;
    for (ll i = 0; i < m; i++) {
        ll x, y;
        cin >> x >> y;
        b.push_back({y-1, x-1});
    }
    sort(b.begin(), b.end());
    ll kiri = 0;
    ll kanan = n-1;
    for (ll i = 1; i < m; i+=2) {
        if (b[i].first == (i/2) && b[i].second == 1) {
            kiri++;
        } else {
            break;
        }
    }
    for (ll i = 1; i < m; i+=2) {
        if (b[m-1-i].first == (n-1 - (i/2)) && b[m-1-i].second == 0) {
            kanan--;
        } else {
            break;
        }
    }

    ll last_i = -1;
    ll last_j = -1;
    ll p_mun = -1;
    ll l_mun = 0;
    if (kiri >= kanan) {
        cout << 1 << endl;
        return;
    }
    for (ll j = 0; j < m; j++) {
        if (b[j].first < kiri || b[j].first > kanan) {
            continue;
        }
        if (b[j].second == 0) {
            ll i = b[j].first;
            if (last_i == -1) {
                last_i = i;
                last_j = 0;
            } else {
                if ((i - last_i) % 2 == 0) {
                    if (last_j == 0) {
                        cout << 0 << endl;
                        return;
                    }
                } else {
                    if (last_j == 1) {
                        cout << 0 << endl;
                        return;
                    }
                }
            }
            last_i = i;
            last_j = 0;
            if (p_mun == -1) {
                p_mun = i;
            }
            l_mun = i;
        }

        if (b[j].second == 1) {
            ll i = b[i].first;
            if (last_i == i) {
                cout << 0 << endl;
                return;
            }
            if (last_i == -1) {
                last_i = i;
                last_j = 1;
            } else {
                if (i - last_i == 1) {
                    if ((i - last_i) % 2 == 0) {
                        if (last_j == 1) {
                            cout << 0 << endl;
                            return;
                        }
                    } else {
                        if (last_j == 0) {
                            cout << 0 << endl;
                            return;
                        }
                    }
                }
            }
            last_i = i;
            last_j = 1;
            if (p_mun == -1) {
                p_mun = i;
            }
            l_mun = i;
        }
    }

    ll hasil = 1;
    hasil *= 2;
    hasil *= max(1LL, (ll)p_mun - kiri);
    hasil *= max(1LL, (ll)kanan - l_mun);
    hasil %= mod;
    cout << hasil << endl;
}

int main() {    
    ll t;
    cin >> t;
    for (ll i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}