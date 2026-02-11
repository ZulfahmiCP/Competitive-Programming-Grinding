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
ttm<ttp T> void debug(set<T> c){cerr<<"[ ";for(auto v:c){prd(v);cerr<<' ';}cerr<<"]\n";}
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

struct DiffArr2D { 
    int N, M;
    vector<vector<ll>> pref;

    DiffArr2D(int n, int m) : N(n), M(m), pref(N+2, vector<ll>(M+2, 0)) {}

    void add(int r1, int c1, int r2, int c2, int v) { // 0-based
        r1++, c1++, r2++, c2++;
        pref[r1][c1] += v;
        if(r2+1 <= N) pref[r2+1][c1] -= v;
        if(c2+1 <= M) pref[r1][c2+1] -= v;
        if(r2+1 <= N && c2+1 <= M) pref[r2+1][c2+1] += v;
    }

    void process() {
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= M; j++){
                pref[i][j] += pref[i][j-1];
            }
        }

        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= M; j++){
                pref[i][j] += pref[i-1][j];
            }
        }
    }

    ll operator()(int r, int c) { // 0-based
        return pref[r+1][c+1];
    }
};

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n, m = 2000; cin >> n;
    vector<int> U(n), D(n), L(n), R(n);
    DiffArr2D diff(m, m), num(m, m);
    int emp = 0;
    
    for(int i = 0; i < n; i++){
        cin >> U[i] >> D[i] >> L[i] >> R[i];
        U[i]--, D[i]--, L[i]--, R[i]--;
        diff.add(U[i], L[i], D[i], R[i], 1);
        num.add(U[i], L[i], D[i], R[i], i);
    }
    
    diff.process();
    num.process();

    vector<int> ans(n, 0);

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            if(diff(i, j) == 0)
                emp++;
            else if(diff(i, j) == 1){
                ans[num(i, j)]++;
            }
        }
    }

    for(int i = 0; i < n; i++)
        cout << emp + ans[i] << endl;
    
    return 0;
}
