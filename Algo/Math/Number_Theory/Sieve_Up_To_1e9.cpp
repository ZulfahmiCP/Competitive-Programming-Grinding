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

// takes 0.5s for n = 1e9
vector<int> sieve(const int N, const int Q = 17, const int L = 1 << 15) {
    const int rs[] = {1, 7, 11, 13, 17, 19, 23, 29};
    struct P { 
        int p, pos[8];
        P(int p) : p(p) {}
    };
    auto approx_prime_count = [] (const int N) -> int {
      return N > 60184 ? N / (log(N) - 1.1) : max(1., N / (log(N) - 1.11)) + 1;
    };

    const int v = sqrt(N), vv = sqrt(v);
    vector<bool> isp(v + 1, true);

    for(int i = 2; i <= vv; i++) if(isp[i])
      for(int j = i * i; j <= v; j += i)
          isp[j] = false;

    int psize = 3;
    vector<int> primes = {2, 3, 5}; 
    const int rsize = approx_prime_count(N + 30);
    primes.resize(rsize);

    vector<P> sprimes; 
    int pbeg = 0, prod = 1; 

    for(int p = 7; p <= v; p++){
        if(!isp[p]) continue;

        if(p <= Q) prod *= p, ++pbeg, primes[psize++] = p;

        auto pp = P(p); 

        for(int t = 0; t < 8; t++){
            int j = (p <= Q) ? p : p * p;
            while (j % 30 != rs[t]) 
                j += p << 1;
            pp.pos[t] = j / 30;
        }
        
        sprimes.pb(pp);
    }

    vector<unsigned char> pre(prod, 0xFF);
    for(int pi = 0; pi < pbeg; pi++) {
        auto pp = sprimes[pi]; 
        const int p = pp.p;

        for(int t = 0; t < 8; ++t){
            const unsigned char m = ~(1 << t);
            for(int i = pp.pos[t]; i < prod; i += p) 
                pre[i] &= m;
        }
    }

    const int block_size = (L + prod - 1) / prod * prod;
    vector<unsigned char> block(block_size); 
    unsigned char* pblock = block.data();
    const int M = (N + 29) / 30;

    for(int beg = 0; beg < M; beg += block_size, pblock -= block_size){
        int end = min(M, beg + block_size);

        for(int i = beg; i < end; i += prod) 
            copy(pre.begin(), pre.end(), pblock + i);

        if(!beg) 
            pblock[0] &= 0xFE;

        for(int pi = pbeg; pi < sz(sprimes); pi++){
            auto& pp = sprimes[pi];
            const int p = pp.p;

            for(int t = 0; t < 8; ++t){
                int i = pp.pos[t]; 
                const unsigned char m = ~(1 << t);
                for(; i < end; i += p) 
                    pblock[i] &= m;
                pp.pos[t] = i;
            }
        }

        for(int i = beg; i < end; i++)
            for(int m = pblock[i]; m > 0; m &= m - 1) 
                primes[psize++] = i * 30 + rs[__builtin_ctz(m)];
    }

    assert(psize <= rsize);
    while(psize > 0 && primes[psize - 1] > N) 
        --psize;
    primes.resize(psize);
    return primes;
}

int main() {
  
    FastIO();
    int N = 1e9 + 3;
    auto primes = sieve(N);
    
    for(int i = 0; i < sz(primes); i += 500)
        cout << primes[i] << '\n';
    
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
