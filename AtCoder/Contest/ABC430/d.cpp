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

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T> using ordmulset = tree<T, null_type, 
    less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    ordmulset<pair<int, int>> ms;

    int n; cin >> n;
    vector<int> A(n+1, INF);

    ms.insert({0, 0});
    ll ans = 0;

    for(int j = 1; j <= n; j++){
        int x, v; cin >> x;
        ms.insert({x, j});
        
        int b = ms.order_of_key({x, j});

        if(b > 0){
            auto left = ms.find_by_order(b-1);
            v = x - left->fi;
            A[j] = min(A[j], v);
            if(v < A[left->se]){
                if(A[left->se] == INF) 
                    A[left->se] = 0;
                ans += v - A[left->se];
                A[left->se] = v;
            }
        }

        if(b < sz(ms)-1){
            auto right = ms.find_by_order(b+1);
            v = right->fi - x;
            A[j] = min(A[j], v);
            if(v < A[right->se]){
                if(A[right->se] == INF) 
                    A[right->se] = 0;
                ans += v - A[right->se];
                A[right->se] = v;
            }
        }

        ans += A[j];
        cout << ans << endl;
    }
    
    return 0;
}
