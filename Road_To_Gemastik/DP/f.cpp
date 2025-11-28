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
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
ttm<ttp T> void prd(T x){cerr<<x;}
ttm<ttp T, ttp U>void prd(pair<T, U> x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
ttm<ttp T, ttp... A>void prd(T x, A... a){prd(x);cerr<<", ";prd(a...);}

ttm<ttp... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
ttm<ttp T> void debug(vector<vector<T>> c){for(auto v: c)debug(v);cerr<<'\n';}
ttm<ttp K, ttp V> void debug(map<K, V> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";cerr<<'[';prd(v.fi);cerr <<", ";prd(v.se);cerr<<']';cm = 1;}cerr<<"]\n";}

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

ttm<const int &M = MOD> struct modi {
    int v;

    modi(ll x = 0) {if(x < 0) x = x % M + M; if(x >= M) x %= M; v = x;}

    modi& operator+=(const modi &b) {v += b.v; if(v >= M) v -= M; return *this;}

    friend modi operator+(const modi &a, const modi &b) {return modi(a) += b; } 
};
using mint = modi<>;

struct SegTree {
    int N;
    vector<mint> tree;

    SegTree(int n) : N(n), tree(4 * N) {}

    #define lc(x) (x << 1) 
    #define rc(x) (x << 1) | 1 

    void update(int j, int v) {
        modify(1, 0, N - 1, j, v);
    }

    void modify(int x, int l, int r, int j, int v) {
        if(l == r) {
            tree[x] += v;
            return;
        }

        int m = (l + r) >> 1;

        j <= m ? modify(lc(x), l, m, j, v) : modify(rc(x), m + 1, r, j, v);

        tree[x] = tree[lc(x)] + tree[rc(x)];
    }

    int calc(int l, int r) {
        return process(1, 0, N - 1, l, r).v;
    }

    mint process(int x, int l, int r, int ql, int qr) {
        if(qr < l || r < ql)
            return 0;

        if(ql <= l && r <= qr) 
            return tree[x];

        int m = (l + r) >> 1;

        return process(lc(x), l, m, ql, qr) + process(rc(x), m + 1, r, ql, qr);
    }
};

int main() {

    FastIO();
    int n; cin >> n;
    vector<int> A(n), num;

    for(int &a : A) cin >> a;

    num = A;
    uniq(num);

    SegTree dp(n + 1);

    for(int &a : A){
        a = lower_bound(all(num), a) - num.begin() + 1;
        dp.update(a, dp.calc(0, a - 1) + 1);
    }
    
    cout << dp.calc(1, n) << endl;
    
    return 0;
}
