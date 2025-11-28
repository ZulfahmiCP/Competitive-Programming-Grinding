#include <bits/stdc++.h>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define Int unsigned int 
#define Long unsigned long long int
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& val);
template<typename T, typename... Args>void prd(const T& val, Args... args);
template<typename... Args>void debug(Args... args);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);
template<typename K, typename V>void debug(const map<K, V>& c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct DSU {
    int N, M;
    vector<int> parent, size;
    stack<int> history, version;

    DSU(int n) : N(n), M(N), parent(N), size(N, 1) {
        iota(all(parent), 0);
    }

    int find(int u) {
        return u == parent[u] ? u : find(parent[u]);
    }

    int unite(int u, int v) {
        u = find(u), v = find(v);

        if(u == v)
            return M;

        if(size[u] < size[v])
            swap(u, v);

        history.push(v);
        size[u] += size[v];
        parent[v] = u;
        
        return (--M);
    }

    void persist() {
        version.push(sz(history));
    }

    int rollback() {
        int target = version.top();

        while(sz(history) > target){
            int u = history.top();
            size[parent[u]] -= size[u];
            parent[u] = u;
            M++;
            history.pop();
        }

        version.pop();

        return M;
    }
};

int main() {

    FastIO();
    int n, q; cin >> n >> q;
    DSU dsu(n);

    string op;
    for(int i = 0, u, v; i < q; i++){
        cin >> op;

        if(op[0] == 'u'){
            cin >> u >> v, u--, v--;
            cout << dsu.unite(u, v) << '\n';
        } else if(op[0] == 'r')
            cout << dsu.rollback() << '\n';
        else    
            dsu.persist();
    }

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& val){cerr<<"(";prd(val.fi);cerr<<", ";prd(val.se);cerr<<")";}
template<typename T, typename... Args>void prd(const T& val, Args... args){prd(val);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
