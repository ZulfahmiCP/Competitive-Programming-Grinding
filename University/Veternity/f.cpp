#include <bits/stdc++.h>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'
#define endl '\n'

using namespace std;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& x);
template<typename T, typename... A>void prd(const T& x, A... a);
template<typename... A>void debug(A... a);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);
template<typename K, typename V>void debug(const map<K, V>& c);
void fail() {debug("DONE"); exit(0);}

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 2e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct frac {
    ll a, b;

    frac(pair<ll, ll> p) : frac(p.fi, p.se) {}
    frac(ll x, ll y) : a(x), b(y) {
        assert(b != 0);
        if(a > 0 && b < 0) a = -a, b = -b;
        ll g = gcd(abs(a), abs(b));
        if(g) a /= g, b /= g;
    }

    frac& operator+=(const frac &y) {return *this = frac(a * y.b + y.a * b, b * y.b);}
    frac& operator-=(const frac &y) {return *this = frac(a * y.b - y.a * b, b * y.b);}
    frac& operator*=(const frac &y) {return *this = frac(a * y.a, b * y.b);}
    frac& operator/=(const frac &y) {return *this = frac(a * y.b, b * y.a);}
    frac& operator++() {a += b; return *this = frac(a, b);}
    frac& operator--() {a -= b; return *this = frac(a, b);}

    friend frac operator-(const frac &a){return frac(-a.a, a.b);}
    friend frac operator+(const frac &a, const frac &b) {return frac(a) += b;}
    friend frac operator-(const frac &a, const frac &b) {return frac(a) -= b;}
    friend frac operator*(const frac &a, const frac &b) {return frac(a) *= b;}
    friend frac operator/(const frac &a, const frac &b) {return frac(a) /= b;}

    friend bool operator==(const frac &x, const frac &y) {return x.a == y.a && x.b == y.b;}
    friend bool operator!=(const frac &x, const frac &y) {return !(x == y); }
    friend bool operator<(const frac &x, const frac &y) {return x.a * y.b < y.a * x.b; }
    friend bool operator>(const frac &x, const frac &y) {return y < x;}
    friend bool operator<=(const frac &x, const frac &y) {return !(y < x);}
    friend bool operator>=(const frac &x, const frac &y) {return !(x < y);}
};

int main() {

    FastIO();
    ll n,m,d; cin >> n >> m >> d;
    int k; cin >> k;

    vector<array<int, 3>> A(k);

    for(auto &[a, b, c] : A)
        cin >> a >> b >> c;

    for(ll v = 1;; v++){
        for (ll t = 1; t <= 4e4; t++){
            bool ok = 1;

            for(int i = 0; i < k; i++) {
                auto &[c, s, p] = A[i];
                frac x(1LL * t * v + s - 1, v);
                frac y(1LL * c * p + d, p);

                // debug(x.a, x.b);
                // debug(y.a, y.b);

                if(x < y) continue;

                frac z(2 * d, p);
                frac ans = (x - y) / z;

                if(ans.a >= 0 && ans.b == 1){
                    ok = 0;
                    break; 
                }
            }
            // newl;
            if(ok){
                cout << t << ' ' << v << '\n';
                return 0;
            }
        }
    }

    assert(false);

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
template<typename T, typename... A>void prd(const T& x, A... a){prd(x);cerr<<", ";prd(a...);}
template<typename... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
