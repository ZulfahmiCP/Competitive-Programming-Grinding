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
    int n,x,y; cin >> n >> x >> y;
    vector<int> A(n);

    for(int &a : A) cin >> a;
    ll total = 0;
    for (int i : A) {
        total += i;
    }
    
    sort(All(A));
    ll hasil = 0;
    bool valid = true;
    for (ll i = 0; (i+1)*(x+y) <= n; i++) {
        if (!valid) {
            break;
        }
        for (int j = 0; j < y; j++) {
            if (i*(x+y) + x + j >= n) {
                valid = false;
                break;
            }
            hasil += A[i*(x+y) + x + j];
        }
    }

    cout << total -  hasil;

    return 0;
}