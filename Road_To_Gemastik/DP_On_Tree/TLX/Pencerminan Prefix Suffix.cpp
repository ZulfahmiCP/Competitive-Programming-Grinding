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

const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

template<const int &M> struct mint {
    int v;

    mint(ll x = 0) {if(x < 0) x = x % M + M; if(x >= M) x %= M; v = x;}
    friend mint power(mint a, ll b) {mint c(1); for(; b > 0; a *= a, b >>= 1) if(b & 1) c *= a; return c;}
    friend mint inverse(const mint &a) {return power(a, M - 2);}

    mint& operator+=(const mint &b) {v += b.v; if(v >= M) v -= M; return *this;}
    mint& operator-=(const mint &b) {v -= b.v; if(v < 0) v += M; return *this;}
    mint& operator*=(const mint &b) {v = (ll)v * b.v % M; return *this;}
    mint& operator/=(const mint &b) {return (*this) *= inverse(b); }

    friend mint operator+(const mint &a, const mint &b) {return mint(a) += b;}
    friend mint operator-(const mint &a, const mint &b) {return mint(a) -= b;}
    friend mint operator*(const mint &a, const mint &b) {return mint(a) *= b;}
    friend mint operator/(const mint &a, const mint &b) {return mint(a) /= b;}
};

template<const int &MOD> struct Fenwick {
    int N, K;
    string S;
    vector<mint<MOD>> bit;
    vector<mint<MOD>> pow_hash, inv_hash;

    Fenwick(int n, string &s) : N(n), K(2377), S(s), bit(N + 1), pow_hash(N), inv_hash(N) {
        pow_hash[0] = 1;
        for(int i = 0; i < N; i++){
            if(i) pow_hash[i] = pow_hash[i - 1] * K;
            add(i, s[i]);
        }

        inv_hash[N - 1] = inverse(pow_hash[N - 1]);
        for(int i = N - 2; i >= 0; i--)
            inv_hash[i] = inv_hash[i + 1] * K;
    }  

    void update(int i, char c){
        remove(i, S[i]);
        S[i] = c;
        add(i, S[i]);
    }

    void add(int i, char c) {
        mint<MOD> v = pow_hash[i] * (c - 'a' + 1);
        for(i++; i <= N; i += i & -i)
            bit[i] += v;
    }

    void remove(int i, char c) {
        mint<MOD> v = pow_hash[i] * (c - 'a' + 1);
        for(i++; i <= N; i += i & -i)
            bit[i] -= v;
    }
    
    mint<MOD> calc(int i) {
        mint<MOD> s = 0;
        for(i++; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }

    int calc(int l, int r) {
        return ((calc(r) - calc(l - 1)) * inv_hash[l]).v;
    }
};

int main() {

    FastIO();
    string s; cin >> s;
    int n = sz(s);

    Fenwick<MOD1> fen1(n, s);
    Fenwick<MOD2> fen2(n, s);

    reverse(all(s));

    Fenwick<MOD1> fenrev1(n, s);
    Fenwick<MOD2> fenrev2(n, s);

    int q; cin >> q;

    for(int i = 0, t; i < q; i++){
        cin >> t;

        if(t){
            int j; cin >> j;
            char c; cin >> c;
            fen1.update(j, c);
            fen2.update(j, c);
            fenrev1.update(n - j - 1, c);
            fenrev2.update(n - j - 1, c);
        } else {
            int p,q; cin >> p >> q;
            
            auto good = [&](int j) -> bool {
                bool g1 = (fen1.calc(p, p + j - 1) == fenrev1.calc(n - q - 1, n - q - 1 + j - 1));
                bool g2 = (fen2.calc(p, p + j - 1) == fenrev2.calc(n - q - 1, n - q - 1 + j - 1));
                return g1 && g2;
            };

            if(!good(1)){
                cout << "0\n";
                continue;
            } 

            if(good(q - p + 1)){
                cout << q - p + 1 << endl;
                continue;
            }

            int l = 1, r = q - p + 1, m;
            while(r - l > 1){
                m = (l + r) >> 1;
                good(m) ? l = m : r = m;
            }

            cout << l << endl;
        }
    }
    
    return 0;
}

