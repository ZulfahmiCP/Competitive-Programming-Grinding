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

const int MAXN = 1e5 + 5;

vector<int> adj[MAXN];
int ord[MAXN], nex[MAXN];
char ans[MAXN];
int K = 0;

void dfs(vector<int> nodes) {
    int start = K;
    
    for(const int &u : nodes)
        for(const int &v : adj[u])
            nex[K++] = v;

    int finish = K;
    if(start == finish) return;

    sort(nex + start, nex + finish, [&](int u, int v) {
        return ord[u] < ord[v];
    });
            
    char c = 'a';
    nodes.clear();

    for(int i = start; i < finish; i++){
        nodes.pb(nex[i]);

        if((i > start && ord[nex[i - 1]] + 1 != ord[nex[i]]) || (i > start && nex[i - 1] > nex[i]))
            c++;

        ans[nex[i]] = c;

        if((i + 1 == finish || ord[nex[i]] + 1 != ord[nex[i + 1]]) || (i + 1 < finish && nex[i] > nex[i + 1])){
            dfs(nodes);
            nodes.clear();
        }
    }
}

int main() {

    FastIO();
    int n; cin >> n;

    for(int u = 1, p; u <= n; u++){
        cin >> p;
        adj[p].pb(u);
    }

    for(int o = 1; o <= n; o++){
        int u; cin >> u;
        ord[u] = o;
    }

    dfs({0});
    for(int i = 1; i <= n; i++)
        cout << ans[i];
    
    return 0;
}


