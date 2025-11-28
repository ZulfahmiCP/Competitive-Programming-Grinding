#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second  
#define ll long long 
#define pb push_back
#define ppb pop_back
#define ld long double 
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define newl cerr << '\n'
#define sz(x) (int)x.size()

#define ttm template 
#define ttp typename 

void FastIO(){ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

ttm<ttp T> void prd(T x){cerr << x;}
ttm<ttp T, ttp U> void prd(pair<T, U> x){cerr<<"("; prd(x.fi); cerr<<", "; prd(x.se); cerr << ")";}
ttm<ttp T, ttp... Args> void prd(T x, Args... arg){prd(x); cerr<<", "; prd(arg...);}
ttm<ttp... Args> void debug(Args... arg){cerr<<"["; prd(arg...); cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr << "["; bool cm=0; for(auto v : c){if(cm); cerr<<", "; prd(v); cm=0;} cerr << "]\n";}

vector<ll> pangkat_2(25);

void solve() {
    ll n, k;
    cin >> n >> k;
    if (k == pangkat_2[n]) {
        cout << n << endl;
        return;
    }
    for (int i = 0; i < 25; i++) {
        if (pangkat_2[i] > k) {
            cout << i << endl;
            return;
        }
    }
}

int main() {


    FastIO();
    pangkat_2[0] = 1;
    for (int i = 1; i < 25; i++) {
        pangkat_2[i] = pangkat_2[i-1]*2;
    }
    int t;
    cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}