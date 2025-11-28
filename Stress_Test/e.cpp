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

int main() {

    FastIO();
    int tc,n,m; cin >> tc;

    while(tc--){
        cin >> n >> m;
        vector<string> S(n);
        map<string, array<int, 3>> pos;

        for(int i = 0; i < n; i++){
            cin >> S[i];
            for(int j = 0; j < m; j++){
                if(j + 1 < m)
                    pos[S[i].substr(j, 2)] = {j+1, j+2, i+1};
                if(j + 2 < m) 
                    pos[S[i].substr(j, 3)] = {j+1, j+3, i+1};
            }
        }

        string t; cin >> t;
        t = '$' + t;

        vector<bool> dp(m + 1, 0);

        dp[0] = 1;

        for(int i = 2; i <= m; i++){
            if(pos.find(t.substr(i - 1, 2)) != pos.end() && dp[i - 2])
                dp[i] = 1;
            if(pos.find(t.substr(i - 2, 3)) != pos.end() && dp[i - 3])
                dp[i] = 1;
        }

        if(!dp[m]){
            cout << "-1\n";
            continue;
        }

        vector<array<int, 3>> ans;

        for(int i = m; i > 0;){
            if(dp[i - 2]){
                ans.pb(pos[t.substr(i - 1, 2)]);
                i -= 2;
            } else if(dp[i - 3]) {
                ans.pb(pos[t.substr(i - 2, 3)]);
                i -= 3;
            } else {
                assert(false);
            }
        }

        reverse(all(ans));

        cout << sz(ans) << endl;

        for(auto &[l, r, i] : ans) cout << l << ' ' << r << ' ' << i << endl;
    }
    
    return 0;
}

