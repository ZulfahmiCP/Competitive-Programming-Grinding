#include <bits/stdc++.h>
using namespace std;

#define fi first 
#define se second
#define ll long long
#define pb push_back
#define ppb pop_back 
#define pf push_front
#define ppf pop_front
#define all_range(x) (x).begin(), (x).begin()
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define sz(x) (int)x.size()
#define endl '\n'
#define ttm  template
#define ttp typename

#ifndef ONLINE_JUDGE 
ttm<ttp T> void prd(T x) {cerr << x;}
ttm<ttp T, ttp U> void prd(pair<T, U> x) {cerr << "("; prd(x.fi); cerr<<", "; prd(x.se); cerr<<")";}
ttm<ttp T, ttp ... A> void prd(T x, A... a) {prd(x); cerr << ", "; prd(a...); }
ttm<ttp... A> void debug(A... a) {cerr << "["; prd(a...); cerr <<"]\n";}
ttm<ttp T> void debug(vector<T> c) {cerr <<"["; for(auto v : c) debug(v); cerr << '\n';} 
ttm<ttp T> void debug(vector<vector<T>> c) {cerr <<"["; for(auto v : c) debug(v); cerr << '\n';} 
#define deb(...) debug(__VA_ARGS__)
#define newl cerr << '\n'
#else 
#define deb(...)
#define newl
#endif

struct car {
    ll i, p, fuel, time;
};

bool operator<(const car &a, const car &b) {
    return a.time < b.time;
}

int main() {

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n,m,F,C,sc,tc; cin >> n >> m >> F >> C >> sc >> tc;

    vector<vector<array<int, 3>>> adj(n);
    vector<ll> T(n), R(n);

    vector<map<ll, ll>> dist(n);
    priority_queue<car> pq;

    sc--, tc--;

    for(int i = 0, u,v,fuel,time; i < m; i++){
        cin >> u >> v, u--, v--;
        cin >> fuel >> time;
        adj[u].pb({v, fuel, time});
        adj[v].pb({u, fuel, time});
    }

    for(int i = 0; i < n; i++){
        cin >> R[i] >> T[i];
    }
    pq.push({sc, -1, F, 0});
    dist[sc][F] = 0;
    
    while(!pq.empty()){
        auto [u, par, fuel, time] = pq.top();
        deb(u+1, par, fuel, time);
        pq.pop();

        if(dist[u][fuel] < time) continue;

        for(auto &[v, f, t] : adj[u]){
            if(v == par) continue;

            ll fuel_x = fuel, time_x = time;

            if(f > fuel_x){
                ll k = ceil((f - fuel_x) / (double)R[v]);
                fuel_x += k * R[v];
                time_x += k * T[v];
                if(fuel_x > C) continue;
            }

            fuel_x -= f;
            time_x += t;

            deb('A', f, t, fuel_x, time_x);

            if(dist[v].find(fuel_x) == dist[v].end()){
                dist[v][fuel_x] = time_x;
                pq.push({v, u, fuel_x, time_x});
            } else if(time_x < dist[v][fuel_x]) {
                dist[v][fuel_x] = time_x;
                pq.push({v, u, fuel_x, time_x});
            }
        }
    }

    ll ans = 9e18;
    for(auto a : dist[tc]){
        ans = min(ans, a.se);
    }
    cout << (ans == 9e18 ? -1 : ans) << endl;
    
    return 0;
}