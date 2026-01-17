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

struct SegTree {
    struct node {
        ll sum = 0, minv = INF, maxv = -INF, lz = 0;
    };  
    int N;
    vector<int> arr;
    vector<node> tree;  

    SegTree(int n) : N(n), arr(N), tree(4 * N) {}

    #define lc(x) (x << 1)
    #define rc(x) (x << 1) | 1

    node pull(node a, node b) {
        return {
            a.sum + b.sum,
            min(a.minv, b.minv),
            max(a.maxv, b.maxv),
            0
        };
    }

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = {arr[l], arr[l], arr[l], 0};
            return;
        }
        int m = (l + r) >> 1;
        build(lc(x), l, m);
        build(rc(x), m+1, r);
        tree[x] = pull(tree[lc(x)], tree[rc(x)]);
    }

    void apply(int x, int l, int r, ll v) {
        tree[x].sum -= v * (r - l + 1);
        tree[x].minv -= v;
        tree[x].maxv -= v;
        tree[x].lz += v;
    }

    void push(int x, int l, int r) {
        if (tree[x].lz == 0) return;
        int m = (l + r) >> 1;

        apply(lc(x), l, m, tree[x].lz);
        apply(rc(x), m+1, r, tree[x].lz);
        
        tree[x].lz = 0;
    }

    ll calc(int l, int r, int k) {
        ll sum = calc(1, 0, N-1, l, r).sum;
        modify(1, 0, N-1, l, r, k);
        sum -= calc(1, 0, N-1, l, r).sum;
        return sum;
    }

    void modify(int x, int l, int r, int ql, int qr, int k){
        if(qr < l || r < ql || tree[x].maxv == 0) return;

        if(ql <= l && r <= qr){
            if(tree[x].minv >= k){
                apply(x, l, r, k);
                return;
            }
        }

        if (l == r) {
            tree[x] = {0, 0, 0, 0};
            return;
        }

        push(x, l, r);
        int m = (l + r) >> 1;
        modify(lc(x), l, m, ql, qr, k);
        modify(rc(x), m+1, r, ql, qr, k);
        tree[x] = pull(tree[lc(x)], tree[rc(x)]);
    }   

    node calc(int x, int l, int r, int ql, int qr) {
        if(qr < l || r < ql) return node();
        if(ql <= l && r <= qr) return tree[x];
        push(x, l, r);
        int m = (l + r) >> 1;
        return pull(calc(lc(x), l, m, ql, qr), calc(rc(x), m+1, r, ql, qr));
    }
 };

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n; cin >> n;
    SegTree seg(n);

    for(auto &a : seg.arr) cin >> a;

    seg.build(1, 0, n-1);

    int q; cin >> q;
    while(q--){
        int l,r,k; cin >> l >> r >> k;
        l--, r--;   
        cout << seg.calc(l, r, k) << endl;
    }
    
    return 0;
}
