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
#ifndef ONLINE_JUDGE
// Di lokal, kita definisikan semua fungsi implementasi
ttm<ttp T> void _prd(T x){cerr<<x;}
ttm<ttp T, ttp U>void _prd(pair<T, U> x){cerr<<"(";_prd(x.fi);cerr<<", ";_prd(x.se);cerr<<")";}
ttm<ttp T, ttp... A>void _prd(T x, A... a){_prd(x);cerr<<", ";_prd(a...);}

ttm<ttp... A> void _debug(A... a){cerr << "["; _prd(a...);cerr<<"]\n";}
ttm<ttp T> void _debug(vector<T> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";_prd(v);cm=1;}cerr<<"]\n";}
ttm<ttp T> void _debug(vector<vector<T>> c){for(auto v: c)_debug(v);cerr<<'\n';}
ttm<ttp K, ttp V> void _debug(map<K, V> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";cerr<<'[';_prd(v.fi);cerr <<", ";_prd(v.se);cerr<<']';cm = 1;}cerr<<"]\n";}

// Kita buat macro untuk memanggil fungsi-fungsi di atas
#define debug(...) _debug(__VA_ARGS__)
#define newl cerr << '\n'

#else 
// Di ONLINE_JUDGE, kita buat semua macro ini menjadi KOSONG
#define debug(...)
#define newl

#endif

int M, phi;

int totient(int n) {
    ll ans = n;
    for(int i = 2; i * i <= n; i++){
        if(n % i) continue;
        ans /= i, ans *= (i - 1);
        while(!(n % i)) n /= i;
    }

    if(n > 1) ans /= n, ans *= (n - 1);
    return ans;
}

struct mint {   
    int v;

    mint(ll x = 0) {if(x < 0) x = x % M + M; if(x >= M) x %= M; v = x;}

    friend mint power(mint a, ll b) {mint c(1); for(; b > 0; a *= a, b >>= 1) if(b & 1) c *= a; return c;}
    friend mint inverse(const mint &a) {return power(a, phi);}

    mint& operator+=(const mint &b) {v += b.v; if(v >= M) v -= M; return *this;}
    mint& operator-=(const mint &b) {v -= b.v; if(v < 0) v += M; return *this;}
    mint& operator*=(const mint &b) {v = (ll)v * b.v % M; return *this;}
    mint& operator/=(const mint &b) {return *this *= inverse(b);}

    friend mint operator+(const mint &a, const mint &b) {return mint(a) += b;}
    friend mint operator-(const mint &a, const mint &b) {return mint(a) -= b;}
    friend mint operator*(const mint &a, const mint &b) {return mint(a) *= b;}
    friend mint operator/(const mint &a, const mint &b) {return mint(a) /= b;}
};

struct Tree {
    int N;
    vector<vector<pair<int, int>>> adj;
    vector<int> sub, vis, val;
    vector<mint> pow10, pow10_inv;
    ll ans = 0;

    Tree(int n) : N(n), adj(N), sub(N), vis(N, 0), val(N, 0), pow10(N + 1), pow10_inv(N + 1) {
        pow10[0] = 1;
        for(int i = 1; i <= N; i++)     
            pow10[i] = pow10[i - 1] * 10;
        
        pow10_inv[N] = inverse(pow10[N]);
        for(int i = N - 1; i >= 0; i--)
            pow10_inv[i] = pow10_inv[i + 1] * 10;
    }

    void add_edge(int u, int v, int w) {
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    int dfs_sub(int u, int p) {
        sub[u] = 1;
        for(auto &[v, w] : adj[u]){
            if(v != p && !vis[v]){
                sub[u] += dfs_sub(v, u);
                val[v] = w;
            }
        }
        return sub[u];
    }

    int cen(int u, int p, int n) {
        for(auto &[v, w] : adj[u])
            if(v != p && !vis[v] && sub[v] > n / 2)
                return cen(v, u, n);
        return u;
    }

    map<int, int> cnt;

    void dfs_cen(int u) {
        int c = cen(u, -1, dfs_sub(u, -1));
        dfs_sub(c, -1);
        vis[c] = 1;


        for(int i = 0; i < 2; i++){
            cnt.clear();

            for(auto &[v, w] : adj[c]){
                if(vis[v]) continue;
                dfs(v, c, 1, 0, 0, i);
                dfs(v, c, 1, 0, 1, i);
            }

            reverse(all(adj[c]));
        }
        debug(c, ans);

        for(auto &[v, w] : adj[c]) if(!vis[v]) dfs_cen(v);
    }

    void dfs(int u, int p, int k, mint x, bool t, bool rev) {
        if(!t){
            x = 10 * x + val[u];

            int f = ((0 - x) * pow10_inv[k]).v;
            if(cnt.find(f) != cnt.end())
                ans += cnt[f];

            if(!f && !rev) ans++;
        } else {
            x += val[u] * pow10[k - 1];
            int f = x.v;
            if(!f && !rev) ans++;
            cnt[f]++;
        }

        for(auto &[v, w] : adj[u])
            if(v != p && !vis[v])
                dfs(v, u, k + 1, x, t, rev);
    }
};

int main() {

    FastIO();
    int n; cin >> n >> M;
    phi = totient(M) - 1;
    Tree tree(n);

    for(int i = 1, u,v,w; i < n; i++){
        cin >> u >> v >> w;
        tree.add_edge(u, v, w);
    }

    tree.dfs_cen(0);
    cout << tree.ans << endl;
    
    return 0;
}

