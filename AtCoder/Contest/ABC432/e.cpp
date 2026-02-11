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

struct Fenwick {
    int N;
    vector<ll> bit;

    Fenwick(int n) : N(n), bit(N + 1, 0) {}

    void update(int i, ll v) {
        for(i++; i <= N; i += i & -i) bit[i] += v;
    }

    ll calc(int i) {
        ll s = 0;
        for(i++; i > 0; i -= i & - i) s += bit[i];
        return s;
    }

    ll calc(int l, int r) {
        if(l < 0 || r < 0) return 0; 
        if(l > r) return 0;
        return calc(r) - calc(l - 1); 
    }
};

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q; cin >> n >> q;
    Fenwick sum(n + q + 1), cnt(n + q + 1);

    vector<int> A(n), B;

    for(int &a : A){
        cin >> a;
        B.pb(a);
    }

    vector<array<int, 3>> Q(q);

    for(auto &[t, x, y] : Q){
        cin >> t >> x >> y;
        if(t == 1){
            x--;
            B.pb(y);
        }
    }

    uniq(B);

    map<int, int> pos;

    for(int i = 0; i < sz(B); i++)
        pos[B[i]] = i;

    for(int &a : A){
        sum.update(pos[a], a);
        cnt.update(pos[a], 1);
    }

    // deb(B);

    for(auto &[t, x, y] : Q){
        if(t == 1){
            sum.update(pos[A[x]], -A[x]);
            cnt.update(pos[A[x]], -1);
            A[x] = y;
            sum.update(pos[A[x]], A[x]);
            cnt.update(pos[A[x]], 1);
        } else {
            // max(x, min(y, A[i]))
            int ry = upper_bound(all(B), y) - B.begin(); // A[i] > y
            int ly = ry - 1;                             // A[i] <= y
            int rx = upper_bound(all(B), x) - B.begin(); // A[i] > x
            int lx = rx - 1;                             // A[i] <= x
            ll ans = 0;
            // deb(x, y, lx, rx, ly, ry);

            // min(y, A[i]) = y

            ans += 1LL * max(x, y) * cnt.calc(ry, n + q - 1);
            // deb("min(y, A[i]) = y   ", cnt.calc(ry, n + q - 1));

            // min(y, A[i]) = A[i]

            // max(x, A[i]) = x

            ans += 1LL * x * cnt.calc(0, min(lx, ly));
            // deb("max(x, A[i]) = x   ", cnt.calc(0, min(lx, ly)));

            // max(x, A[i]) = A[i]

            ans += sum.calc(rx, ly);
            // deb("max(x, A[i]) = A[i]", sum.calc(rx, ly));

            cout << ans << endl;
        }
    }

    
    return 0;
}
