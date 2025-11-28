#include <bits/stdc++.h>

#define fi first 
#define se second 
#define ll long long 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define uniq(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'
#define endl '\n'
#define ttm template
#define ttp typename

using namespace std;
ttm<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
ttm<ttp T> void prd(T x){cerr<<x;}
ttm<ttp T, ttp U>void prd(pair<T, U> x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
ttm<ttp T, ttp... A>void prd(T x, A... a){prd(x);cerr<<", ";prd(a...);}

ttm<ttp... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
ttm<ttp T> void debug(vector<vector<T>> c){for(auto v: c)debug(v);cerr<<'\n';}
ttm<ttp K, ttp V> void debug(map<K, V> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";cerr<<'[';prd(v.fi);cerr <<", ";prd(v.se);cerr<<']';cm = 1;}cerr<<"]\n";}

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

template<typename T> struct RMQ {
    int N, LOG;
    vector<vector<T>> tab;
    vector<T> arr, logs;

    RMQ(int n = 0) : N(n), LOG(log2(N) + 1), tab(N, vector<T>(LOG)), logs(N + 1, 0), arr(N) {}
    
    void build() {
        for(int i = 2; i <= N; i++)
            logs[i] = 1 + logs[i >> 1];

        for(int i = 0; i < N; i++)
            tab[i][0] = arr[i];

        for(int j = 1; j < LOG; j++)
            for(int i = 0; i + (1 << j) <= N; i++)
                tab[i][j] = best(tab[i][j - 1], tab[i + (1 << (j - 1))][j - 1]);
    }

    T best(T &a, T &b) {
        return max(a, b);
    }

    T calc(int l, int r){
        int k = logs[r - l + 1];
        return best(tab[l][k], tab[r - (1 << k) + 1][k]);
    }
};

int main() {

    FastIO();
    int n; cin >> n;
    vector<int> A(n), dp(n, 0);

    for(int &a : A) cin >> a;
    
    vector<int> L(n), R(n);
    RMQ<int> rmq(n);

    rmq.arr = A;
    rmq.build();

    for(int i = 0; i < n; i++){
        L[i] = i;
        if(!i || A[i - 1] >= A[i]) continue;

        int l1 = 0, r1 = i - 1, m;
        while(r1 - l1 > 1){
            m = (l1 + r1) >> 1;
            rmq.calc(m, i - 1) < A[i] ? r1 = m : l1 = m;
        }

        if(rmq.calc(l1, i - 1) < A[i])
            r1 = l1;

        int l2 = r1, r2 = i - 1;
        while(r2 - l2 > 1){
            m = (l2 + r2) >> 1;
            rmq.calc(m, i - 1) == rmq.calc(r1, i - 1) ? l2 = m : r2 = m;
        }

        if(rmq.calc(r2, i - 1) == rmq.calc(r1, i - 1))
            l2 = r2;

        L[i] = l2;
    }

    for(int i = n - 1; i >= 0; i--){
        R[i] = i;
        if(i == n - 1 || A[i + 1] >= A[i]) continue;

        int l1 = i + 1, r1 = n - 1, m;
        while(r1 - l1 > 1){
            m = (l1 + r1) >> 1;
            rmq.calc(i + 1, m) < A[i] ? l1 = m : r1 = m;
        }

        if(rmq.calc(i + 1, r1) < A[i])
            l1 = r1;

        int l2 = i + 1, r2 = l1;
        while(r2 - l2 > 1){
            m = (l2 + r2) >> 1;
            rmq.calc(i + 1, m) == rmq.calc(i + 1, l1) ? r2 = m : l2 = m;
        }

        if(rmq.calc(i + 1, l2) == rmq.calc(i + 1, l1))
            r2 = l2;
            
        R[i] = r2;
    }

    function<int(int)> solve = [&](int i) -> int {
        if(dp[i]) return dp[i];

        dp[i] = 1;

        if(L[i] != i) dp[i] = max(dp[i], solve(L[i]) + 1);
        if(R[i] != i) dp[i] = max(dp[i], solve(R[i]) + 1);

        return dp[i];
    };

    int ans = 0;

    for(int i = 0; i < n; i++)
        ans = max(ans, solve(i));

    cout << ans << endl;
    
    return 0;
}
