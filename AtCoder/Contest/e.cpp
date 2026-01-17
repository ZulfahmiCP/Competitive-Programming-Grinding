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
        int sum = 0, sum_act = 0;
        bool act = 0, par_act = 0;

        void toggle_1() {
            act = 1;
            sum = sum_act;
        }

        void toggle_2() {
            if(act) return;
            par_act = 1;
            sum = 1;
        }
    };

    int N = 2e5 + 100, NNN;
    vector<node> tree;
    vector<int> val, sum;
    
    SegTree(int n) : tree(4 * N), NNN(n) {}

    #define lc(x) (x << 1)
    #define rc(x) (x << 1) | 1

    void build() {
        uniq(val);
        int m = sz(val);
        sum.resize(m);
        for(int i = 0; i < sz(val)-1; i++)
            sum[i] = val[i+1] - val[i];
        sum[m-1] = 1;
        deb(sum);
        build(1, 0, N - 1);
    }

    void build(int x, int l, int r) {
        if(l == r){
            if(l < sz(val))
                tree[x].sum_act = sum[l];
            return;
        }
        int m = (l + r) >> 1;
        build(lc(x), l, m);
        build(rc(x), m+1, r);
    }

    void update(int l, int r) {
        int il = lower_bound(all(val), l) - val.begin();
        int ir = lower_bound(all(val), r) - val.begin();
        deb(il, ir);

        if(il <= ir - 1)
            modify_act(1, 0, N-1, il, ir - 1);
        modify_par(1, 0, N-1, ir);
    }

    void modify_act(int x, int l, int r, int ql, int qr) {
        if(r < ql || l < qr) return;
        if(l <= ql && r <= qr){
            tree[x].toggle_1();
            return;
        }

        int m = (l + r) >> 1;
        modify_act(lc(x), l, m, ql, qr);
        modify_act(rc(x), m+1, r, ql, qr);
        tree[x].sum = max(tree[lc(x)].sum + tree[rc(x)].sum, tree[x].sum);
    }

    void modify_par(int x, int l, int r, int j) {
        if(l == r){
            tree[x].toggle_2();
            return;
        }

        int m = (l + r) >> 1;

        j <= m ? modify_par(lc(x), l, m, j) : modify_par(rc(x), m+1, r, j);
        tree[x].sum = max(tree[lc(x)].sum + tree[rc(x)].sum, tree[x].sum);
    }

    int query() {
        return NNN - tree[1].sum;
    }
};

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // 3 5 
    // 5 8 
    // 7 9 
    // 0 1 2 3 4 
    // 3 5 7 8 9 
    // 2 2 1 1 2

    int n,q; cin >> n >> q;
    SegTree seg(n);
    vector<pair<int, int>> op;

    for(int i = 0, l,r; i < q; i++){
        cin >> l >> r;
        seg.val.pb(l);
        seg.val.pb(r);
        op.pb({l, r});
    }

    seg.build();

    for(auto &[l, r] : op){
        seg.update(l, r);
        cout << seg.query() << endl;
    }
    
    return 0;
}
