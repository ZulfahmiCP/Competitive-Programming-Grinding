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

struct SegTree {
    struct node {
        ll sum, mx;
    };  

    int N;
    vector<int> arr;
    vector<node> tree;

    SegTree(int n) : N(n), arr(N), tree(4 * N) {}

    node pull(node a, node b) {
        return {
            a.sum + b.sum,
            max(a.mx, b.mx)
        };
    }

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = {arr[l], arr[l]};
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        tree[x] = pull(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void update(int j, int v) {
        modify(0, 0, N - 1, j, v);
    }

    void modify(int x, int l, int r, int j, int v) {
        if(l == r){
            tree[x] = {v, v};
            return;
        }

        int m = (l + r) >> 1;

        j <= m ? modify(2 * x + 1, l, m, j, v)
               : modify(2 * x + 2, m + 1, r, j, v);

        tree[x] = pull(tree[2 * x + 1], tree[2 * x + 2]);
    }

    // calculate the sum from l to r
    ll calc_sum(int l, int r) {
        return process_sum(0, 0, N - 1, l, r).sum;
    }

    node process_sum(int x, int l, int r, int ql, int qr) {
        if(qr < l || r < ql)
            return node();

        if(ql <= l && r <= qr)
            return tree[x];

        int m = (l + r) >> 1;

        return pull(process_sum(2 * x + 1, l, m, ql, qr),
                    process_sum(2 * x + 2, m + 1, r, ql, qr));
    }
    
    // find the biggest l such that A[0:l] <= v
    int calc_max(int v) {
        if(tree[0].mx < v) return -1; 
        return process_max(0, 0, N - 1, v);
    }

    int process_max(int x, int l, int r, int v) {
        if(l == r)
            return l;

        int m = (l + r) >> 1;
        
        if(tree[2 * x + 2].sum <= l)
            return process_max(2 * x + 1, l, m, v);
        return process_max(2 * x + 2, m + 1, r, v);
    }
};

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
