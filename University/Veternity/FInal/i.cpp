#include <bits/stdc++.h>
#define ll long long 
using namespace std;

ll power(int a, int b) {
    ll c = 1;
    for(int i = 0; i < b; i++)
        c *= a;
    return c;
}

int main() {

    int t; cin >> t;
    while(t--){
        int n,x; cin >> n >> x;
        vector<int> A(n);

        for(int &a : A) cin >> a;

        ll ans = 0;

        for(int i = 0; i < n; i++){
            ans += 1LL * A[i] * power(x, i + 1);
        }

        cout << ans << endl;
    }

    return 0;
}