#include <bits/stdc++.h>

#define fi first 
#define se second 
#define ll long long 
#define pb push_back
#define ppb pop_back 
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define sz(x) (int)x.size()
#define endl '\n'

using namespace std;

void FastIO() {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

int main() {

    FastIO();
    ll n;
    string s;
    cin >> s;
    cin >> n;
    ll hasil = 0;
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        ll a = min(x, y);
        ll b = max(x, y);
        ll c = (b-a);
        ll basis = c+1;
        ll sisa = a % c;
        if (sisa == 0) {
            sisa = basis;
        }
        hasil ^= (basis + 2*(sisa-1));

    }
    if (s == "Veter") {
        if (hasil == 0) {
            cout << "Nity";
        } else {
            cout << "Veter";
        }
    } else {
        if (hasil == 0) {
            cout << "Veter";
        } else {
            cout << "Nity";
        }
    }
    cout << endl;
    return 0;
}