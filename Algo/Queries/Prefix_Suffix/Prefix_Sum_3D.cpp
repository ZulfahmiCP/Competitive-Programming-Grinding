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

struct PrefSum {
    int N, M, P;
    vector<vector<vector<ll>>> sum;

    PrefSum(const vector<vector<vector<int>>> &A) : N(sz(A)), M(sz(A[0])), P(sz(A[0][0])), sum(N + 1, vector<vector<ll>>(M + 1, vector<ll>(P + 1, 0))) {
        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= M; j++)
                for(int k = 1; k <= P; k++)
                    sum[i][j][k] = A[i - 1][j - 1][k - 1]
                                   + sum[i - 1][j][k] + sum[i][j - 1][k] + sum[i][j][k - 1]
                                   - sum[i - 1][j - 1][k] - sum[i - 1][j][k - 1] - sum[i][j - 1][k - 1]
                                   + sum[i - 1][j - 1][k - 1];
    }

    ll operator()(int x1, int y1, int z1, int x2, int y2, int z2) {
        return sum[x2][y2][z2]
               - sum[x1 - 1][y2][z2]  -  sum[x2][y1 - 1][z2]  -  sum[x2][y2][z1 - 1]
               + sum[x1 - 1][y1 - 1][z2] + sum[x1 - 1][y2][z1 - 1] + sum[x2][y1 - 1][z1 - 1]
               - sum[x1 - 1][y1 - 1][z1 - 1];
    }
};

int main(){
 
    FastIO();
    int n; cin >> n;
    vector A(n, vector<vector<int>>(n, vector<int>(n)));

    for(auto &a : A) for(auto &b : a) for(auto &c : b) cin >> c;

    PrefSum pref(A);
    int q; cin >> q;
    
    for(int i = 0, x1, y1, z1, x2, y2, z2; i < q; i++){
        cin >> x1 >> x2 >> y1 >> y2 >> z1 >> z2;
        cout << pref(x1, y1, z1, x2, y2, z2) << '\n';
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
