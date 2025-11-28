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

// dp[i][j] = min(dp[i - 1][k] + C[k][j]) : k < j
// min[i][j] <= min[i][j + 1]
// min[i][j] is the smallest k that gives the optimal answer
// Reduce from O(KN^2) to O(KNlogN)

struct DNC_DP {
    int N, K;
    vector<ll> A, pref, dp, new_dp;

    DNC_DP(int n, int k) : N(n), K(k), A(N), pref(N + 1), 
                           dp(N + 1, INFL), new_dp(N + 1) {}

    ll cost(int i, int j) {
        ll sum = pref[j] - pref[i - 1];
        return sum * sum;
    }

    void dnc(int l, int r, int bestl, int bestr) {
        if(l > r) return;

        int m = (l + r) >> 1;

        pair<ll, int> best = {INFL, 1};

        for(int j = bestl; j <= min(m, bestr); j++)
            best = min(best, {dp[j - 1] + cost(j, m), j});

        new_dp[m] = best.fi;

        dnc(l, m - 1, bestl, best.se);
        dnc(m + 1, r, best.se, bestr);
    }

    ll solve() {
        pref[0] = dp[0] = 0;

        for(int i = 0; i < N; i++)
            pref[i + 1] = pref[i] + A[i];

        for(int k = 1; k <= K; k++){
            fill(all(new_dp), INFL);
            dnc(1, N, 1, N);
            dp = new_dp;
        }

        return dp[N];
    }
};

int main(){
 
    FastIO();
    int n,k; cin >> n >> k;
    DNC_DP dp(n, k);

    for(auto &a : dp.A)
        cin >> a;

    cout << dp.solve() << '\n';

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
