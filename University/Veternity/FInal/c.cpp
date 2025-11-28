#include <bits/stdc++.h>

#define fi first 
#define se second 
#define ll long long 
#define pb push_back
#define ppb pop_back 
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define sz(x) (int)x.size()
#define endl '\n'

using namespace std;

const int INF = 2e9 + 7;

void FastIO() {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

struct DSU {
    int N;
    vector<int> par, size, mx, mn;
    stack<array<int, 3>> hist;
    stack<int> ver;

    DSU() {}
    DSU(int n) : N(n), par(N), size(N, 1), mx(N, 0), mn(N, INF) {
        iota(all(par), 0);
    }

    int find(int u) {
        return u == par[u] ? u : find(par[u]);
    }

    bool unite(int u, int v) {
        u = find(u), v = find(v);

        if(u == v) return 0;
        if(size[u] < size[v]) swap(u, v);

        hist.push({v, mn[u], mx[u]});
        size[u] += size[v];
        par[v] = u;
        mn[u] = min(mn[u], mn[v]);
        mx[u] = max(mx[u], mx[v]);

        return 1;
    }

    int query(int u) {
        u = find(u);
        return mx[u] - mn[u];
    }

    void persist() {
        ver.push(sz(hist));
    }

    void rollback() {
        int target = ver.top();

        for(; sz(hist) > target;){
            auto [u, minu, maxu] = hist.top();
            size[par[u]] -= size[u];
            mn[par[u]] = minu;
            mx[par[u]] = maxu;
            par[u] = u;
            hist.pop();
        }

        ver.pop();
    }
};  

struct DNC {
    int N, Q;
    vector<vector<pair<int, int>>> tree;
    pair<int, int> cur;
    vector<pair<int, int>> ans;
    DSU dsu;

    DNC(int n, int q) : N(n), Q(q + 1), tree(4 * Q + 1), dsu(N), ans(Q, {-1, -1}) {}

    #define lc(x) (x << 1)
    #define rc(x) (x << 1) | 1

    void update(int u, int v, int l, int r) {
        cur = {u, v};
        update(1, 0, Q - 1, l, r);
    }

    void update(int x, int l, int r, int ql, int qr) {
        if(qr < l || r < ql) return;

        if(ql <= l && r <= qr){
            tree[x].pb(cur); 
            return;
        }

        int m = (l + r) >> 1;

        update(lc(x), l, m, ql, qr);
        update(rc(x), m + 1, r, ql, qr);
    }

    void solve() {
        process(1, 0, Q - 1);
    }

    void process(int x, int l, int r) {
        dsu.persist();
        for(auto &[u, v] : tree[x])
            dsu.unite(u, v);
        
        if(l == r){
            if(ans[l].fi != -1)
                ans[l].se = dsu.query(ans[l].fi);
            dsu.rollback();
            return;
        }

        int m = (l + r) >> 1;
        process(lc(x), l, m);
        process(rc(x), m + 1, r);
        dsu.rollback();
    }
};

int main() {

    FastIO();
    int n,q; cin >> n >> q;
    vector<int> A(n);
    
    for(int &a : A) cin >> a;
    
    DNC dnc(n, q);
    dnc.dsu.mx = dnc.dsu.mn = A;

    map<pair<int, int>, int> pos;

    for(int i = 1, op,u,v; i <= q; i++){
        cin >> op;

        if(op == 1 || op == 2){
            cin >> u >> v, u--, v--;
            if(u > v) swap(u, v);
            if(op == 1 && pos.find({u, v}) != pos.end()) continue;
            pos[{u, v}] = i;
        } else if(op == 3) {
            cin >> u >> v, u--, v--;
            if(u > v) swap(u, v);
            dnc.update(u, v, pos[{u, v}], i - 1);
            pos.erase({u, v});
        } else if(op == 4) {
            cin >> u, u--;
            dnc.ans[i].fi = u;
        }
    }

    for(auto [p, i] : pos) dnc.update(p.fi, p.se, i, q);
    dnc.solve();
    for(auto &[u, a] : dnc.ans) 
        if(a != -1)
            cout << a << endl;

    return 0;
}

/*
3 7
10 20 40
1 1 2
4 1
2 2 3
4 3
3 2 3
4 3
4 3
*/