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

// Point Update and Range Query
template <typename T> struct Fenwick {
    int N;
    vector<T> bit;
    vector<int> arr;
 
    Fenwick(int n) : N(n), arr(N), bit(N + 1, 0) {}
    Fenwick(const vector<int> &A) : N(A.size()), arr(A), bit(N + 1, 0) {
        build();
    }

    void build() {
        for(int i = 0; i < N; i++)
            update(i, arr[i]);
    }
 
    void update(int i, T v) {
        for(i++; i <= N; i += i & -i) 
            bit[i] += v;
    }
 
    T calc(int i) {
        T sum = 0;
        for(i++; i > 0; i -= i & -i)
            sum += bit[i];
        return sum;
    }
 
    T calc(int l, int r) {
        return calc(r) - calc(l - 1);
    }
};

// Range Update and Point Query 
template <typename T> struct Fenwick {
    int N;
    vector<T> bit;
    vector<int> arr;
 
    Fenwick(int n) : N(n), arr(N), bit(N + 1, 0) {}
    Fenwick(const vector<int> &A) : N(A.size()), arr(A), bit(N + 1, 0) {
        build();
    }

    void build() {
        for(int i = 0; i < N; i++)
            update(i, arr[i]);
    }
 
    void update(int i, T v) {
        for(i++; i <= N; i += i & -i) 
            bit[i] += v;
    }

    void update(int l, int r, T v) {
        update(l, v);
        update(r + 1, -v);
    }
 
    T calc(int i) {
        T sum = 0;
        for(i++; i > 0; i -= i & -i)
            sum += bit[i];
        return sum;
    }
};

// Range Update and Range Query
template <typename T> struct Fenwick {
    int N;
    vector<int> arr;
    vector<T> bit1, bit2;

    Fenwick(int n) : N(n), arr(N), bit1(N + 1, 0), bit2(N + 1, 0) {}
    Fenwick(const vector<int>& A) : N(A.size()), arr(A),
                                    bit1(N + 1, 0), bit2(N + 1, 0) {
        build();
    }

    void build() {
        for(int i = 0; i < N; i++)
            update(i, i, arr[i]);
    }

    void update(vector<ll>& bit, int i, T v) {
        for(i++; i <= N; i += i & -i) 
            bit[i] += v;
    }

    void update(int l, int r, T v) {
        update(bit1, l, v);
        update(bit1, r + 1, -v);
        update(bit2, l, v * (l - 1));
        update(bit2, r + 1, -v * r);
    }

    T sum(const vector<ll>& bit, int i) {
        T total = 0;
        for(i++; i > 0; i -= i & -i)
            total += bit[i];
        return total;
    }

    T prefix_sum(int i) {
        return sum(bit1, i) * i - sum(bit2, i);
    }

    T calc(int l, int r) {
        return prefix_sum(r) - prefix_sum(l - 1);
    }

    T calc(int i) {
        return calc(i, i);
    }
};

int main() {

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
