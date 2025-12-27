#include <bits/stdc++.h>

#define fi first 
#define se second 
#define ll long long 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define uniq(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'
#define endl '\n'
#define ttm template
#define ttp typename

using namespace std;
ttm<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
 
#ifndef ONLINE_JUDGE
ttm<ttp T> void prd(T x){cerr<<x;}
ttm<ttp T, ttp U>void prd(pair<T, U> x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
ttm<ttp T, ttp... A>void prd(T x, A... a){prd(x);cerr<<", ";prd(a...);}
ttm<ttp... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr<<"[ ";for(auto v:c){prd(v);cerr<<' ';}cerr<<"]\n";}
ttm<ttp T> void debug(vector<vector<T>> c){for(auto v: c)debug(v);cerr<<'\n';}
ttm<ttp K, ttp V> void debug(map<K, V> c){cerr<<"[ ";for(auto v:c){cerr<<'[';prd(v.fi);cerr <<", ";prd(v.se);cerr<<']';cerr<<' ';}cerr<<"]\n";}
#define deb(...) debug(__VA_ARGS__)
#define newl cerr << '\n'
#else 
#define deb(...)
#define newl
#endif

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

pair<int, int> split(int x) {
    int b = x / 2;
    int a = x - b;

    if(a == b) a++, b--;

    return {a, b};
}

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    ll t,n,x,y; cin >> t;
    
    while(t--){
        cin >> n >> x >> y;
        vector<int> P(n), C(n);

        for(int i = 0; i < n; i++){
            char c; cin >> c;
            C[i] = c == '1';
        }
        
        for(int i = 0; i < n; i++){
            cin >> P[i];
        }

        if(accumulate(all(P), 0LL) > x + y){
            cout << "NO\n";
            continue;
        }

        vector<ll> A(n, 0), B(n, 0);

        ll needA = 0, needB = 0;

        for(int i = 0; i < n; i++){
            auto pp = split(P[i]);

            if(C[i] == 0){
                A[i] = pp.fi, B[i] = pp.se;
                needA += pp.fi;
            } else {
                A[i] = pp.se, B[i] = pp.fi;
                needB += pp.fi;
            }
        }

        ll sumA = accumulate(all(A), 0LL);
        ll sumB = accumulate(all(B), 0LL);

        if(needA > x || needB > y){
            cout << "NO\n";
            continue;
        }

        int sumC = accumulate(all(C), 0);

        if(sumC != 0 && sumC != n){
            cout << "YES\n";
            continue;
        }

        if(sumC == n){
            swap(x, y);
            swap(sumA, sumB);
        }

        sumB += x - sumA;

        for(int i = 0; i < n; i++)
            if(!(P[i] & 1))
                sumB++;

        if(sumB >= y && x - n >= y)
            cout << "YES\n";
        else 
            cout << "NO\n";

    }
    
    return 0;
}
