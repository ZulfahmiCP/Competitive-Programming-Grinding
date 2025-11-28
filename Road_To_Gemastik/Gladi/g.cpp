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
    int mins = 0;
    bool valid = true;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int i = 0; i < k-1; i++) {
            int a;
            cin >> a;
            mins = max(mins, a+1);
        }
        int a;
        cin >> a;
        if (a < mins) {
            valid = false;
        }
    }
    if (valid) {
        cout << mins;
    } else {
        cout << -1;
    }
    return 0;
}
