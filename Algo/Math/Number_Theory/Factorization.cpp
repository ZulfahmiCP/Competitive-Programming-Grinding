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
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct Factor {
    int N;
    vector<int> mind;

    Factor(int n) : N(n) {
        mind.resize(N + 1, -1);

        mind[1] = 1;

        for(int i = 2; i <= N; i++) if(mind[i] == -1)
            for(int j = i; j <= N; j += i)
                if(mind[j] == -1)
                    mind[j] = i;
    }

    vector<pair<int, int>> operator[](int n) {
        vector<pair<int, int>> div;

        while(n > 1){
            if(div.empty() || div.back().fi != mind[n])
                div.pb({mind[n], max_pow(n, mind[n])});
            n /= mind[n];
        }

        return div;
    }

    vector<int> operator()(int n) {
        vector<int> div;

        while(n > 1){
            if(div.empty() || div.back() != mind[n])
                div.pb(mind[n]);
            n /= mind[n];
        }

        return div;
    }

    int max_pow(int n, int p){
        if(n % p) return 0;
        return 1 + max_pow(n / p, p);
    }
} factor(1e6);

struct Factorization {
    int N, M;
    vector<int> primes;

    Factorization(int n) : N(n), M(sqrt(N) + 1) {
        vector<bool> prime(M + 1, 1);
        
        for(int i = 2; i * i <= M; i++) if(prime[i])
            for(int j = i * i; j <= M; j += i)
                prime[j] = 0;
        
        for(int i = 2; i <= M; i++)
            if(prime[i]) primes.pb(i);
    }

    vector<pair<int, int>> operator[](int n) {
        vector<pair<int, int>> div;

        for(int &p : primes){
            if(n < p) break;
            if(n % p) continue;

            int a = 0;
            while(!(n % p))
                n /= p, a++;
            div.pb({p, a});

        }

        if(n > 1)
            div.pb({n, 1});
    
        return div;
    }

    vector<int> operator()(int n) {
        vector<int> div;

        for(int &p : primes){
            if(n < p) break;
            if(n % p) continue;
            
            int a = 0;
            while(!(n % p))
                n /= p, a++;
            div.pb(p);
        }

        if(n > 1)
            div.pb(n);

        return div;
    }
} factorize(1e9);

int factor_count(int n) {
    int x = 1;
    for(auto &[a, p] : factor[n])
        x *= (p + 1);
    return x;
}

int main(){
 
    FastIO();
    debug(factor(174));

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
