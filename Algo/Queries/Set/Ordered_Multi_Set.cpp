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

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
 
template<typename T>
using ordmulset = tree<T, null_type, less_equal<T>, rb_tree_tag,
tree_order_statistics_node_update>;

template<typename T>
struct multi_set {
    ordmulset<T> S;

    multi_set() {}
    multi_set(const ordmulset<T> &s) : S(s) {}
    bool exist(T v) {return (S.upper_bound(v) == S.end() ? 0 : *S.upper_bound(v) == v);}
    bool empty() {return S.empty();}
    void insert(T v) {S.insert(v);}
    void erase(T v) {if(exist(v)) S.erase(S.upper_bound(v));}
    void clear() {S.clear();}
    int val(int i) {return *S.find_by_order(i);}
    int first_idx(T v) {return (exist(v) ? S.order_of_key(v) : -1);}
    int last_idx(T v) {
        if(!exist(v)) return -1;
        if(val(size() - 1) == v) return size() - 1;
        return first_idx(*S.lower_bound(v)) - 1;
    }
    int count(T v) {return exist(v) ? last_idx(v) - first_idx(v) + 1 : 0;}
    int find_by_order(int i) {return *S.find_by_order(i);}
    int order_of_key(T v) {return S.order_of_key(v);}
    int size() {return sz(S);}
};

int main(){
 
    FastIO();
    int n; cin >> n;
    vector<int> A(n);
    multi_set<int> S;

    for(int &a : A){
        cin >> a;
        S.insert(a);
    }

    // order_of_key(k) return number of element < k;
    for(int i = 0; i < n; i++)
        debug(S.find_by_order(i));

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
