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
template<typename K, typename V>void debug(const map<K, V>& c);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

vector<bool> prime;
void gen_prime(int n) {
    prime.assign(n + 1, 1);
    prime[0] = prime[1] = 0; 
    for(int i = 2; i * i <= n; i++) if(prime[i]) 
        for(int j = i * i; j <= n; j += i)
            prime[j] = 0;
}

vector<int> primes;
void gen_primes(int n) {
    gen_prime(n);
    for(int i = 2; i <= n; i++)
        if(prime[i]) primes.pb(i);
}

vector<vector<int>> divisors;
void gen_div(int n) {
    divisors.resize(n + 1);
    for(int i = 1; i <= n; i++)
        for(int j = i; j <= n; j += i)
            divisors[j].pb(i);
}

vector<int> mind;
void gen_mind(int n) {
    mind.assign(n + 1, 1);
    for(int i = 2; i <= n; i++) if(mind[i] == 1)
        for(int j = i; j <= n; j += i)
            if(mind[j] == -1) mind[j] = i;
}

vector<int> div_sum;
void gen_div_sum(int n) {
    div_sum.assign(n + 1, 0);
    for(int i = 1; i <= n; i++)
        for(int j = i; j <= n; j += i)
            div_sum[j] += 1;
}

vector<int> totient;
void gen_totient(int n) {
    totient.resize(n + 1);
    iota(all(totient), 0);
    for(int i = 2; i <= n; i++) if(totient[i] == i) 
        for(int j = i; j <= n; j += i)
            totient[j] -= totient[j] / i;
}

vector<int> pdc;
vector<int> gen_pdc(int n) {
    gen_mind(n);
    pdc.resize(n + 1);
    for(int i = 2, j; i <= n; i++){
        j = i / mind[i];
        pdc[i] = pdc[j] + (mind[i] != mind[j]);
    }
}

vector<ll> fact;
void gen_fact(int n) {
    fact.resize(n + 1, 1);
    for(int i = 2; i <= n; i++)
        fact[i] = fact[i - 1] * i;
}

vector<ll> inv;
void gen_inv(int n) {
    inv.assign(n + 1, 1);
    for(int i = 2; i <= n; i++)
        inv[i] = 1LL * (MOD - MOD / i) * inv[MOD % i] % MOD;
}

vector<vector<bool>> coprime;
void gen_coprime(int n, int m) {
    coprime.assign(n + 1, vector<bool>(m + 1, true));
    for(int k = 2; k <= min(n, m); k++)
        for(int i = k; i <= n; i += k)
            for(int j = k; j <= m; j += k)
                coprime[i][j] = false;
}

template<typename T>
bool perfect_square(T &n) {
    T s = sqrt(n);
    return s * s == n;
}

ll div_cnt(ll n) {
    if(n == 1) return 1;
    int ans = 1, cnt;
    gen_primes(n);
    gen_prime(n);

    for(int &p : primes){
        if(1LL * p * p * p > n) break;
        cnt = 1;
        while(!(n % p)) n /= p, cnt++;
        ans *= cnt;
    }

    if(prime[n]) ans *= 2;
    else if(perfect_square(n)) ans *= 3;
    else if(n != 1) ans *= 4;

    return ans;
}

int main(){
 
    FastIO();
    cout << gcd(272, 545);

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& val){cerr<<"(";prd(val.fi);cerr<<", ";prd(val.se);cerr<<")";}
template<typename T, typename... Args>void prd(const T& val, Args... args){prd(val);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr<<"]\n";}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
