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

const ll INFL = 1e12;

int main() {

    FastIO();
    int n,y; cin >> n >> y;
    vector<array<int, 3>> A(n);

    for(int i = 0; i < n; i++){
        int a,b,c,d,e; cin >> a >> b >> c >> d >> e;
        A[i] = {b + c + d, e, a};
    }

    auto good = [&](ll x) -> bool {
        ll sum = 0;

        for(auto &p : A){
            ll a = p[0], b = p[1], c = p[2];
            ll j = (x + b) / (a + b);
            
            sum += 1LL * j * c;
        }

        return sum >= y;
    };

    // for(int i = 1; i <= 16; i++) debug(good(i));

    ll l = 0, r = INFL, m;
    while(r - l > 1){
        m = (l + r) >> 1;
        good(m) ? r = m : l = m;
    }

    cout << r << '\n';

    return 0;
}