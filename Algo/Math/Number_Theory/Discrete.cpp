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

struct Discrete {
    // return minimum x such that a^x === b (mod m)
    int discrete_log(int a, int b, int m) {
        a %= m, b %= m;

        int k = 1, add = 0, g;
        while((g = gcd(a, m)) > 1) {
            if(b == k) return add;
            if(b % g) return -1;
            b /= g, m /= g, add++;
            k = (1LL * k * a / g) % m;
        }

        int n = sqrt(m) + 1, an = 1;
        for(int i = 0; i < n; i++)
            an = (1LL * an * a) % m;

        Map<int, int> vals;
        for(int q = 0, cur = b; q <= n; q++){
            vals[cur] = q;
            cur = (1LL * cur * a) % m;
        }

        for(int p = 1, cur = 1; p <= n; p++){
            cur = (1LL * cur * an) % m;
            if(vals.count(cur))
                return n * p - vals[cur];
        }

        return -1;
    }

    // Finding the primitive root modulo p.
    // Exist if for any a where gcd(a, n) == 1
    // there exist any integer k such that
    // g^k === a (mod p)
    int primitive_root(int p) {
        int phi = p - 1, n = phi;
        vector<int> fact;

        for(int i = 2; i * i <= n; i++){
            if(n % i) continue;
            fact.pb(i);
            while(!(n % i))
                n /= i;
        }

        if(n > 1) fact.pb(n);

        for(int res = 2; res <= p; res++){
            bool good = 1;
            for(int i = 0; i < sz(fact) && good; i++)
                good &= power(res, phi / fact[i], p) != 1;
            if(good) return res;
        }
       
        return -1;
    }

    // Finds all numbers x such that x^k === a (mod n)
    vector<int> discrete_root(int n, int k, int a) {
        if(!a) return {0};

        int g = primitive_root(n), m = sqrt(n) + 1;

        vector<pair<int, int>> dec(m);
        for(int i = 1; i <= m; i++)
            dec[i - 1] = {power(g, i * m * k % (n - 1), n), i};
        sort(all(dec));
        
        int any_ans = -1;
        for (int i = 0, y; i < m; ++i) {
            y = power(g, i * k % (n - 1), n) * a % n;
            auto it = lower_bound(all(dec), make_pair(y, 0));
            if(it != dec.end() && it->first == y){
                any_ans = it->second * m - i;
                break;
            }
        }
        
        if(any_ans == -1) return {};

        int val = (n - 1) / gcd(k, n - 1);
        vector<int> ans;

        for(int cur = any_ans % val; cur < n - 1; cur += val)
            ans.pb(power(g, cur, n));
        
        sort(all(ans));
        return ans;
    }

    int power(int a, int b, int m) {
        int c = 1;
        for(; b > 0; a = (1LL * a * a) % m, b >>= 1)
            if(b & 1) c = (1LL * c * a) % m;
        return c;
    }
} discrete;

int main(){
 
    FastIO();
    

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
