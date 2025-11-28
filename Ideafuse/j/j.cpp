#include <bits/stdc++.h>
using namespace std;

#define fi first 
#define se second
#define ll long long
#define pb push_back
#define ppb pop_back 
#define pf push_front
#define ppf pop_front
#define all_range(x) (x).begin(), (x).begin()
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define sz(x) (int)x.size()
#define endl '\n'
#define ttm  template
#define ttp typename

#ifndef ONLINE_JUDGE 
ttm<ttp T> void prd(T x) {cerr << x;}
ttm<ttp T, ttp U> void prd(pair<T, U> x) {cerr << "("; prd(x.fi); cerr<<", "; prd(x.se); cerr<<")";}
ttm<ttp T, ttp ... A> void prd(T x, A... a) {prd(x); cerr << ", "; prrd(a...); }
ttm<ttp... A> void debug(A... a) {cerr << "["; prd(a...); cerr <<"]\n";}
ttm<ttp T> void debug(vector<T> c) {cerr <<"["; for(auto v : c) debug(v); cerr << '\n';} 
ttm<ttp T> void debug(vector<vector<T>> c) {cerr <<"["; for(auto v : c) debug(v); cerr << '\n';} 
#define deb(...) debug(__VA_ARGS__)
#define newl cerr << '\n'
#else 
#define deb(...)
#define newl
#endif

void solve() {
    ll n;
    cin >> n;
    vector<ll> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    vector<ll> a, b, c;
    a.push_back(0);
    b.push_back(0);
    c.push_back(0);
    for (int i = 0; i < n-1; i++) {
        if (i % 3 == 0) {
            ll selisih = s[i+1] - s[i];
            a.push_back(a[a.size() - 1] + selisih);
        } else if (i % 3 == 1) {
            ll selisih = s[i+1] - s[i];
            b.push_back(b[b.size() - 1] + selisih);
        } else {
            ll selisih = s[i+1] - s[i];
            c.push_back(c[c.size() - 1] + selisih);
        }
    }
    int sa_min = 0;
    int sb_min = 0;
    int sc_min = 0;
    int sa_max = 0;
    int sb_max = 0;
    int sc_max = 0;
    for (int i : a) {
        if (i < sa_min) {
            sa_min = i;
        }
        if (i > sa_max) {
            sa_max = i;
        }
    }

    for (int i : b) {
        if (i < sb_min) {
            sb_min = i;
        }
        if (i > sb_max) {
            sb_max = i;
        }
    }

    for (int i : c) {
        if (i < sc_min) {
            sc_min = i;
        }
        if (i > sc_max) {
            sc_max = i;
        }
    }

    int a_min = 1 - sa_min;
    int b_min = 1 - sb_min;
    int c_min = 1 - sc_min;
    vector<int> ha(n+2);
    ha[2] = c_min;
    ha[1] = b_min;
    ha[0] = s[0] - c_min - b_min;
    if (ha[0] + sa_max > 2000) {
        int sel = ha[0] + sa_max - 2000;
        ha[0] -= sel;
        ha[1] += sel;
        if (ha[1] + sb_max > 2000) {
            int sel2 = ha[1] + sb_max - 2000;
            ha[1] -= sel2;
            ha[2] += sel2;
        }
    }
    // if (ha[0] < a_min) {
    //     cout << -1 << endl;
    //     return;
    // }
    for (int i = 3; i < n+2; i++) {
        ha[i] = s[i-2] - ha[i-1] - ha[i-2];
    }
    for (int i : ha) {
        cout << i << ' ';
    }
    cout << endl;
}

int main() {

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    
    return 0;
}