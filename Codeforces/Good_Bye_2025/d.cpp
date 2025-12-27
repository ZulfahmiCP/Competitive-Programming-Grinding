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
    int t,n,m; cin >> t;

    while(t--){
        cin >> n >> m;
        vector<pair<ll, ll>> A(n);

        for(int i = 0; i < n; i++){
            cin >> A[i].fi;
            A[i].se = i + 1;
        }

        sort(all(A));

        vector<pair<int, int>> ans;

        if(m == 0){
            ll sum = 0;

            for(int i = 0; i < n - 1; i++) 
                sum += A[i].fi;

            if(sum < A[n - 1].fi){
                cout << "-1\n";
                continue;
            }
            
            ll cur = A[n - 1].fi;
            int j = 0;
            
            while(j < n - 2){
                if(cur - A[j].fi <= 0) break;
                ans.pb({A[j].se, A[n - 1].se});
                cur -= A[j].fi;
                j++;
            }
            
            if(j < n - 2){
                for(int i = j; i < n - 3; i++)
                    ans.pb({A[i].se, A[i+1].se});
                ans.pb({A[n - 3].se, A[n - 2].se});
            }
            
            ans.pb({A[n - 1].se, A[n - 2].se});
        } else if(m == 1) {
            if(n > 1){
                for(int i = 0; i < n - 2; i++)
                    ans.pb({A[i].se, A[i + 1].se});
                ans.pb({A[n - 1].se, A[n - 2].se});
            }
        } else {
            if(n < 2 * m){
                cout << "-1\n";
                continue;
            }

            int x = n - 2 * m, y = n - m;
            
            if(x > 0){
                for(int i = 0; i < x - 1; i++)
                    ans.pb({A[i].se, A[i + 1].se});
                ans.pb({A[x - 1].se, A[x].se});
            }
            
            for(int i = 0; i < m; i++)
                ans.pb({A[y + i].se, A[x + i].se});
        }

        cout << sz(ans) << endl;

        for(auto &[a, b] : ans) cout << a << ' ' << b << endl;
    }
    
    return 0;
}
