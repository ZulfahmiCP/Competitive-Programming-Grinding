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

int main() {

    FastIO();
    ll n, t;
    cin >> n >> t;

    vector<bool> hasil(n, false);

    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == 'L') {
            int akhir = i - t;
            if (akhir >= 0) {
                hasil[akhir] = true;
            }
        } else {
            int akhir = i + t;
            if (akhir < n) {
                hasil[akhir] = true;
            }
        }
    }

    for (bool i : hasil) {
        if (i) {
            cout << "X";
        } else {
            cout << ".";
        }
    }

    return 0;
}