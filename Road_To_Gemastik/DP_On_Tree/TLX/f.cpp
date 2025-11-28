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

#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T> using ord_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct Graph {
    int N;
    vector<vector<int>> adj;
    vector<ord_set<int>> st;
    vector<int> deg;

    Graph(int n) : N(n), adj(N), deg(N, 0), st(N) {}

    void add_edge(int u, int v) {
        adj[v].pb(u);
        deg[u]++;
    }

    int mex(const ord_set<int> &s) {
        if(s.find(0) == s.end()) return 0;

        int l = 0, r = sz(s), m;
        while(r - l > 1){
            m = (l + r) >> 1;
            if(*s.find_by_order(m) == m)
                l = m;
            else 
                r = m;
        }

        return r;
    }

    void merge(int i, int j) {
        st[i].insert(mex(st[j]));
        if(sz(st[i]) < sz(st[j])) st[i].swap(st[j]);
        for(int a : st[j]) st[i].insert(a);
    }

    bool solve() {
        queue<pair<int, int>> bfs;

        for(int u = 0; u < N; u++){
            if(deg[u] > 0) continue;
            bfs.push({u, -1});
        }

        if(bfs.empty()) return !(N & 1);

        while(!bfs.empty()){
            auto [u, p] = bfs.front();
            bfs.pop();

            for(int &v : adj[u]){
                if(v == p) continue;
                merge(v, u);
                if(!(--deg[v])){
                    bfs.push({v, u});
                }
            }
        }

        int u = -1;

        for(int v = 0; v < N; v++)   
            if(deg[v] > 0) {u = v; break;}

        if(u == -1) return 1;

        int s = u, t;
        int score_s = mex(st[s]);
        auto sts = st[s];
        // return 1;

        while(true){
            int v = -1;
            t = u;

            for(int &w : adj[u])
                if(deg[w] > 0) 
                    v = w;

            merge(v, u);
            assert(v != -1);
            if(v == s) break;
            u = v;
        }

        
        st[s] = sts;
        merge(s, t);
        debug(s+1, score_s, mex(st[s]));
        for(auto a : sts) debug(a);
        debug(deg);
        return score_s == mex(st[s]);
    }
};

int main() {

    FastIO();
    int n; cin >> n;
    Graph graph(n);

    for(int u = 0, p; u < n; u++){
        cin >> p, p--;
        graph.add_edge(p, u);
    }

    cout << (graph.solve() ? "POSSIBLE" : "IMPOSSIBLE");
    
    return 0;
}

