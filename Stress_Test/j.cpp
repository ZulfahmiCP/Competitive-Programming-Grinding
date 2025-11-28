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

struct SegTree {
    struct node {
        ll mn = INF;
        ll lz = 0;
    };

    int N;
    vector<node> tree;

    SegTree(int n) : N(n), tree(4 * N) {}

    #define lc(x) (x << 1) 
    #define rc(x) (x << 1) | 1

    node pull(node a, node b) {
        return {
            min(a.mn, b.mn)
        };
    }

    void push(int x, int l, int r) {
        if(!tree[x].lz) return;

        tree[x].mn += tree[x].lz;

        if(l != r){
            tree[lc(x)].lz += tree[x].lz;
            tree[rc(x)].lz += tree[x].lz;
        }

        tree[x].lz = 0;
    }

    void update(int l, int r, ll v) {
        modify(1, 0, N - 1, l, r, v);
    }

    void modify(int x, int l, int r, int ql, int qr, ll v) {    
        if(qr < l || r < ql) return;

        if(ql <= l && r <= qr){
            tree[x].lz = v;
            push(x, l, r);
            return;
        }

        int m = (l + r) >> 1;
        modify(lc(x), l, m, ql, qr, v);
        modify(rc(x), m + 1, r, ql, qr, v);
        tree[x] = pull(tree[lc(x)], tree[rc(x)]);
    }

    ll calc(int l, int r) {
        return process(1, 0, N - 1, l, r).mn;
    }

    node process(int x, int l, int r, int ql, int qr){
        if(qr < l || r < ql) return node();
        if(ql <= l && r <= qr) return tree[x];
        int m = (l + r) >> 1;
        return pull(process(lc(x), l, m, ql, qr), process(rc(x), m + 1, r, ql, qr));
    }
};

int main() {

    FastIO();
    int n; cin >> n;
    SegTree seg(n);

    vector<int> A(n), B(n);

    for(int &a : A) cin >> a, a--;

    ll inv = 0;

    for(int i = 0; i < n; i++){
        ll x = seg.calc(A[i] + 1, n - 1);
        seg.update(A[i], A[i], 1);
        inv += x;
        B[i] = x;
    }

    ll ans = inv;

    for(int i = 0; i < n; i++){
        seg.update(A[i], A[i], -seg.calc(A[i], A[i]));
        seg.update(A[i], A[i], i + 1 - 2 * B[i]);
    }

    debug(inv);

    for(int i = 0; i < n; i++){
        seg.update(0, n - 1, -1);
        seg.update(0, A[i] - 1, 2);
        ans = min(ans, inv + seg.calc(0, n - 1));
        debug(A[i], inv + seg.calc(0, n - 1));
    }

    cout << ans << endl;

    return 0;
}

