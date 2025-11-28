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
    int n,m, ans = 0; cin >> n >> m;
    vector<string> S(n);
    
    for(auto &s : S) cin >> s;

    queue<pair<int, int>> bfs;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(S[i][j] == '#')
                bfs.push({i, j});

    while(!bfs.empty()){
        int len = sz(bfs);
        vector<pair<int, int>> color;

        auto check = [&](int i, int j) -> bool {
            if(i < 0 || j < 0 || i >= n || j >= m) return 0;
            return S[i][j] == '#';
        };

        auto valid = [&](int i, int j) -> bool {
            if(i < 0 || j < 0 || i >= n || j >= m) return 0;
            if(check(i, j)) return 0;
            if(check(i - 1, j) + check(i + 1, j) + check(i, j - 1) + check(i, j + 1) == 1)
                return 1;
            return 0;
        };

        for(int k = 0; k < len; k++){
            auto [i, j] = bfs.front();
            bfs.pop();
            ans++;
            
            for(auto [di, dj] : vector<pair<int, int>>{{i - 1, j}, {i + 1, j}, {i, j - 1}, {i, j + 1}}){
                if(valid(di, dj)){
                    bfs.push({di, dj});
                    color.pb({di, dj});
                }
            }
        }

        for(auto &[i, j] : color) S[i][j] = '#';
    }

    cout << ans << endl;
    
    return 0;
}

