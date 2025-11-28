#include <bits/stdc++.h>
#define ll long long

using namespace std;

void solve() {
    ll b, t, h;
    cin >> b >> t >> h;
    double selisih = (t - b) / (double) h;
    ll hasil = 0;
    for (int i = 0; i < h; i++) {
        ll sisi = floor(b + i*selisih);
        hasil += sisi*sisi;
    }
    cout << hasil << endl;
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}