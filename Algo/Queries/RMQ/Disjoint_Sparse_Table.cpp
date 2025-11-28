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

template<typename T>
struct DisjointSparseTable {
    int N, LOG;
    vector<vector<T>> table;
    vector<T> arr, log_table;

    DisjointSparseTable(int n) : N(n), LOG(log2(N) + 1), arr(N), table(LOG, vector<T>(N)), log_table(N + 1, 0) {}
    DisjointSparseTable(const vector<T>& A) : DisjointSparseTable<T>(sz(A)) {
        arr = A;
        build();
    }

    void build() {
        for(int i = 2; i <= N; i++)
            log_table[i] = 1 + log_table[i >> 1];

        for(int i = 0; i < N; i++) 
            table[0][i] = arr[i];

        for(int i = 1, k; (1 << i) <= N; i++){
            k = 1 << i;
            for (int l = 0, r, m; l < n; l += k) {
                m = l + (k >> 1), r = min(l + k, n);

                table[i][m - 1] = arr[m - 1];
                for(int j = m - 2; j >= l; j--) 
                    table[i][j] = best(arr[i], table[i][j + 1]);
                
                table[i][m] = arr[m];
                for(int j = m + 1; j < r; j++) 
                    table[i][j] = best(table[i][j - 1], arr[j]);
            }
        }
    }

    T best(T &a, T &b) {
        return min(a, b);
    }

    T query(int l, int r) const {
        if (l == r) return table[0][l];
        int k = log_table(l ^ r);
        return std::min(table[k][l], table[k][r]);
    }
};

int main() {

    FastIO();
    vector<int> arr = {1, 3, 2, 7, 9, 11, 3, 5, 6};
    DisjointSparseTable<int> dst(arr);

    int l = 2, r = 5;
    cout << "Range Minimum from " << l << " to " << r << " is " << dst.query(l, r) << "\n";

    l = 4, r = 8;
    cout << "Range Minimum from " << l << " to " << r << " is " << dst.query(l, r) << "\n";

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
