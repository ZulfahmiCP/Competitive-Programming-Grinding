#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <climits>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <string>
#include <bitset>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <deque>
#include <set>
#include <map>

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

struct MillerRabin {
    ll N, K;
    vector<int> primes, mind;

    MillerRabin(ll n) : N(n), K(cbrt(N) + 5), primes(K, 0), mind(K, 0) {
        int cnt = 0;
        for(int i = 2; i < K; i++){
            if(!mind[i]) primes[cnt++] = mind[i] = i;
            for(int j = 0, k; (k = i * primes[j]) < K; j++){
                mind[k] = primes[j];
                if(mind[i] == mind[k]) break;
            }
        }
    }

    // Determine if n is prime or not in O(it * (log (n)) ^ 3)
    // where it = number of rounds performed (but faster in practice)
    bool is_prime(ll n) {
        if(n <= 2 || !(n & 1)) return (n == 2);
        if(n < K) return mind[n] == n;

        ll c, d, s(0), r(n - 1);

        for(; !(r & 1); r >>= 1, s++){}

        for(int i = 0; primes[i] < n && primes[i] < 32; i++){
            c = pow_mod(primes[i], r, n);
            for(int j = 0; j < s; j++){
                d = mul_mod(c, c, n);
                if(d == 1 && c != 1 && c != n - 1) 
                    return false;
                c = d;
            }

            if(c != 1) 
                return false;
        }

        return true;
    }

    ll mul_mod(ll x, ll y, ll m) {
        return __int128(x) * y % m;
    }

    ll pow_mod(ll x, ll n, ll m) {
        ll res = 1 % m;
        for(; n; n >>= 1){
            if(n & 1) res = mul_mod(res, x, m);
            x = mul_mod(x, x, m);
        }
        return res;
    }
} millerrabin(1e18);

int main(){
 
    FastIO();
    ll t,n; cin >> t;
    while(t--){
        cin >> n;
        cout << (millerrabin.is_prime(n) ? "Yes" : "No") << '\n';
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
