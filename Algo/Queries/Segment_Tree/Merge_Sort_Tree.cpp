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

struct MergeSortTree {
    int N;
    vector<pair<int, int>> arr;
    vector<vector<int>> tree;
    vector<int> value;

    MergeSortTree(int n) : N(n), value(N), arr(N), tree(4 * N) {}

    void pull(int x) {
        tree[x].clear();
        merge(all(tree[2 * x + 1]), all(tree[2 * x + 2]), back_inserter(tree[x]));
    } 

    void build() {
        for(int i = 0; i < N; i++)
            arr[i] = {value[i], i};
        sort(all(arr));
        build(0, 0, N - 1);
    }

    void build(int x, int l, int r) {
        if (l == r) {
            tree[x] = {arr[l].se};
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);
        pull(x);
    }

    void update(int j, int v) {
        modify(0, 0, N - 1, j, v);
    }

    void modify(int x, int l, int r, int j, int v) {
        if(l == r){
            tree[x] = {v};
            return;
        }

        int m = (l + r) >> 1;

        j <= m ? modify(2 * x + 1, l, m, j, v)
               : modify(2 * x + 2, m + 1, r, j, v);
        pull(x);
    }

    int calc(int l, int r, int k) {
        return value[process(0, 0, N - 1, l, r, k)];
    }

    int process(int x, int l, int r, int ql, int qr, int k) {
        if(l == r)
            return tree[x][0];

        int p = upper_bound(all(tree[2 * x + 1]), qr) -
                lower_bound(all(tree[2 * x + 1]), ql);
                
        int m = (l + r) >> 1;

        return (p >= k ? process(2 * x + 1, l, m, ql, qr, k) :
                         process(2 * x + 2, m + 1, r, ql, qr, k - p));
    }
};

int main(){
 
    FastIO();
    int t,n,q; cin >> t;
    for(int T = 1; T <= t; T++){
        cin >> n >> q;
        MergeSortTree seg(n);

        for(int &a : seg.value)
            cin >> a;

        seg.build();

        cout << "Case #" << T << ":\n";
        for(int i = 0, l, r, k; i < q; i++){
            cin >> l >> r >> k, l--, r--;
            cout << seg.calc(l, r, k) << '\n';
        }
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
