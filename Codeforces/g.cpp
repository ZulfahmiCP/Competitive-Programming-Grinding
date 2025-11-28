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
        int can1 = -1, can2 = -1;
        int l, r;

        node() : l(-1), r(-1) {}
        node(int l, int r) : l(l), r(r) {}
    };

    int N;
    vector<int> arr, who;
    vector<node> tree;
    vector<vector<int>> pos;

    SegTree(int n) : N(n), arr(N), tree(4 * N), pos(N) {}

    #define lc(x) (x << 1)
    #define rc(x) (x << 1) | 1

    int count(int x, int l, int r) {
        r = upper_bound(all(pos[x]), r) - pos[x].begin();
        l = lower_bound(all(pos[x]), l) - pos[x].begin();
        return r - l;
    }

    node pull(node a, node b) {
        if(a.l == -1) return b;
        if(b.l == -1) return a;
        node c(a.l, b.r);

        vector<pair<int, int>> cand;

        for(int a : set<int>{a.can1, a.can2, b.can1, b.can2}) 
            if(a != -1)
                cand.pb({count(a, c.l, c.r), a});

        sort(All(cand));
        c.can1 = cand[0].se;
        if(sz(cand) > 1)
            c.can2 = cand[1].se;

        return c;
    }

    void build() {
        who = arr;
        uniq(who);

        for(int i = 0; i < N; i++){
            arr[i] = lower_bound(all(who), arr[i]) - who.begin();
            pos[arr[i]].pb(i);
        }

        build(1, 0, N - 1);
    }

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = node(l, l);
            tree[x].can1 = arr[l];
            return;
        }

        int m = (l + r) >> 1;
        build(lc(x), l, m);
        build(rc(x), m + 1, r);
        tree[x] = pull(tree[lc(x)], tree[rc(x)]);
    }

    pair<int, int> calc(int l, int r) {
        node x = process(1, 0, N - 1, l, r);
        assert(l <= r && x.l == l && x.r == r);
        return {x.can1, x.can2};
    }

    node process(int x, int l, int r, int ql, int qr) {
        if(qr < l || r < ql) return node();
        if(ql <= l && r <= qr) return tree[x];
        int m = (l + r) >> 1;
        return pull(process(lc(x), l, m, ql, qr), process(rc(x), m + 1, r, ql, qr));
    }
};

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t,n,q; cin >> t;

    while(t--){
        cin >> n >> q;
        SegTree seg(n);

        for(int &a : seg.arr) cin >> a;

        seg.build();

        for(int i = 0, l,r; i < q; i++){
            cin >> l >> r, l--, r--;
            pair<int, int> can = seg.calc(l, r);
            
            vector<int> ans;
            if(can.fi != -1 && seg.count(can.fi, l, r) > (r - l + 1) / 3)
                ans.pb(can.fi);
            if(can.se != -1 && seg.count(can.se, l, r) > (r - l + 1) / 3)
                ans.pb(can.se);
                
            sort(all(ans));
        
            for(int &a : ans) cout << seg.who[a] << ' ';
            if(ans.empty()) cout << -1;
            cout << endl;
        }
    }
    
    return 0;
}
/*

(N^2+N) / 2 
1 (2 + 3)
misalkan S = 1 + 2 + ... + N = N(N+1) / 2
kita mau cari 1 <= x <= N dan x(S - x) perfect square

x(N(N+1)/2 - x) = c^2
xN(N+1)/2 - x^2 = c^2
c^2 + x^2 - xS = 0
4c^2 + 4x^2 - 4xS = 0
(2c + 2x)^2 - 4xS - 8xc = 0 

c+x = xN
c-x = (N+1)/2
2x = xN - (N+1)/2
xN-2x = (N+1)/2
x = (N+1)/(2N-4)

*/
