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
 
#ifndef ONLINE_JUDGE
ttm<ttp T> void prd(T x){cerr<<x;}
ttm<ttp T, ttp U>void prd(pair<T, U> x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
ttm<ttp T, ttp... A>void prd(T x, A... a){prd(x);cerr<<", ";prd(a...);}
ttm<ttp... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr<<"[ ";for(auto v:c){prd(v);cerr<<' ';}cerr<<"]\n";}
ttm<ttp T> void debug(vector<vector<T>> c){for(auto v: c)debug(v);cerr<<'\n';}
ttm<ttp K, ttp V> void debug(map<K, V> c){cerr<<"[ ";for(auto v:c){cerr<<'[';prd(v.fi);cerr <<", ";prd(v.se);cerr<<']';cerr<<' ';}cerr<<"]\n";}
#define deb(...) debug(__VA_ARGS__)
#define newl cerr << '\n'
#else 
#define deb(...)
#define newl
#endif

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n; cin >> n;
    vector<string> S(n);

    for(auto &s : S) cin >> s;

    // dp[i][k] = minimum cost such that the height of the stairs at column i is k.

    // dp[i][k] = cost(i, k) + min(dp[i-1][l]), l <= k

    vector<vector<int>> pref_w(n, vector<int>(n, 0));
    vector<vector<int>> pref_b(n, vector<int>(n, 0));

    for(int j = 0; j < n; j++){
        pref_w[0][j] = S[0][j] == '.';
        pref_b[0][j] = S[0][j] == '#';

        for(int i = 1; i < n; i++){
            pref_w[i][j] = pref_w[i-1][j] + (S[i][j] == '.');
            pref_b[i][j] = pref_b[i-1][j] + (S[i][j] == '#');
        }
    }
    
    auto cost = [&](int i, int k) {
        if(k == 0) return pref_b[n-1][i];
        if(k == n) return pref_w[n-1][i];
        k = n-k;
        return (pref_w[n-1][i] - pref_w[k-1][i]) + pref_b[k-1][i];
    };

    vector<int> dp(n+1, INF);

    for(int k = 0; k <= n; k++)
        dp[k] = cost(0, k);
    // deb(dp);

    for(int i = 1; i < n; i++){
        vector<int> new_dp(n+1, INF);
        
        for(int k = 0; k <= n; k++){
            if(k > 0)
                dp[k] = min(dp[k], dp[k-1]);
            new_dp[k] = dp[k] + cost(i, k);
        }

        dp = new_dp;
        // deb(new_dp);
    }

    cout << *min_element(all(dp)) << endl;
    
    return 0;
}
