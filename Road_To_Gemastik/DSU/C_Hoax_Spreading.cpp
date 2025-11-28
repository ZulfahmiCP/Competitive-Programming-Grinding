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

struct DSU {
    int N;
    vector<int> par, size;

    DSU(int n) : N(n), par(N), size(N, 1) {
        iota(all(par), 0);
    }

    int find(int u) {
        return u == par[u] ? u : par[u] = find(par[u]);
    }

    void unite(int u, int v) {
        u = find(u), v = find(v);

        if(u == v) return;
        if(size[u] < size[v]) swap(u, v);

        par[v] = u;
        size[u] += size[v];
    }

    int query(int u) {
        return size[find(u)];
    }
};

int main() {

    FastIO();
    int n,s,q; cin >> n >> s >> q;
    map<int, vector<array<int, 3>>> time;
    DSU dsu(n);

    for(int i = 0, t; i < n; i++){
        cin >> t;

        for(int j = 0, a,b; j < t; j++){
            cin >> a >> b, b++;
            time[a].pb({1, i, b});
            time[b].pb({0, i, b});
        }
    }

    set<pair<int, int>> st;

    for(auto [t, arr] : time){
        sort(all(arr));

        for(auto &[c, i, b] : arr){
            if(c){
                st.insert({i, b});
            } else {
                auto p = st.lower_bound(make_pair(i, -1));
                if(p != st.end() && p->fi == i)
                    st.erase(p);
            }
        }

        while(sz(st) > 1){
            auto p = st.begin();
            auto q = p; q++;

            // debug(t, p->fi, q->fi);
            dsu.unite(p->fi, q->fi);

            if(p->se > q->se){
                st.erase(q);
            } else {
                st.erase(p);
            }
        }
    }

    for(int i = 0, j; i < q; i++){
        cin >> j, j--;
        cout << dsu.query(j) << endl;
    }
    
    return 0;
}

