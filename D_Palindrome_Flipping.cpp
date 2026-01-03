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

void flip(string &s, int i, int j) {
    for(int k = i; k <= j; k++){
        if(s[k] == '0') s[k] = '1';
        else s[k] = '0';
    }
}

vector<pair<int, int>> trans(string s) {
    int n = sz(s);
    vector<pair<int, int>> ops;

    for(int i = 0; i < n; i++){
        if(s[i] == '0') continue;

        int j = i + 1;

        while(j < n && s[j] == '0')
            j++;

        if(j == n){
            if(i >= 2){
                ops.pb({i - 2, i - 1});
                flip(s, i - 2, i - 1);
                ops.pb({i - 2, i});
                flip(s, i - 2, i);
            } else {
                ops.pb({i + 1, i + 2});
                flip(s, i + 1, i + 2);
                ops.pb({i, i + 2});
                flip(s, i, i + 2);
            }

            break;
        }

        ops.pb({i, j});
        flip(s, i, j);

        if(i + 1 < j - 1){
            ops.pb({i + 1, j - 1});
            flip(s, i + 1, j - 1);
        }
    }

    assert(s == string(n, '0'));

    return ops;
}

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tc,n; cin >> tc;
    string s,t;

    while(tc--){
        cin >> n >> s >> t;

        auto ans_s = trans(s);
        auto ans_t = trans(t);

        // deb(ans_s);deb(ans_t);newl;

        reverse(all(ans_t));

        int k = sz(ans_s) + sz(ans_t);
        assert(k <= 2 * n);

        cout << k << endl;
        for(auto &[l, r] : ans_s) cout << l+1 << ' ' << r+1 << endl;
        for(auto &[l, r] : ans_t) cout << l+1 << ' ' << r+1 << endl;
    }
    
    return 0;
}
