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
    ll r, c, a, b, x, y;
    cin >> r >> c >> a >> b >> x >> y;
    if (a >= x) {
        cout << "TIDAK";
    } else {
        int s_x = abs(a-x);
        int s_y = abs(b - y);
        if (s_y > s_x) {
            cout << "TIDAK";
        } else {
            ll s_xy = abs(s_x - s_y);
            if (s_xy % 2 == 0) {
                cout << "YA";
            } else {
                cout << "TIDAK";
            }
        }
    }
    return 0;
}
