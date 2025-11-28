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
const ll mod = (1LL << 61) - 1;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

ll rng() {
	static mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
	return uniform_int_distribution<ll>(0, LLONG_MAX)(gen);
} 

struct Hashing {
    int N;
    vector<ll> hash;
    
    Hashing(int n) : N(n), hash(N + 1) {
        for(auto &h : hash) h = rng();
    }

    vector<ll> pref(const vector<int> &A) {
        int n = sz(A);
        vector<ll> pref_hash(n + 1);

        pref_hash[0] = 0;
        for(int i = 0; i < n; i++)
            pref_hash[i + 1] = pref_hash[i] + hash[A[i]];

        return pref_hash;
    }

    ll sub_hash(int l, int r, const vector<ll> &pref_hash) {
        return (pref_hash[r] - pref_hash[l - 1] + mod) % mod;
    }
} hasher(2e5);  

int main(){
 
    FastIO();
    int n, q; cin >> n >> q;
    vector<int> A(n), B(n);

    for(int &a : A) cin >> a;
    for(int &b : B) cin >> b;

    auto pref_A = hasher.pref(A);
    auto pref_B = hasher.pref(B);

    for(int i = 0, la, ra, lb, rb; i < q; i++){
        cin >> la >> ra >> lb >> rb;
        cout << (hasher.sub_hash(la, ra, pref_A) == hasher.sub_hash(lb, rb, pref_B) ? "Yes" : "No") << '\n';
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
