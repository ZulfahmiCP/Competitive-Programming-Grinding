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
    int T,n,k; cin >> T;

    for(int tc = 1; tc <= T; tc++){
        cin >> n >> k;

        vector<int> A(n);

        for(auto &a : A) cin >> a;

        map<int, int> mp;

        mp[0] = -1;

        int l = 0, r = 0, ans = -1;

        for(int i = 0; i < n; i++){
            if(i) A[i] += A[i - 1];
            A[i] %= k;
            
            auto j = mp.begin();
            if(j->fi <= A[i]){
                if(A[i] - j->fi > ans){
                    ans = A[i] - j->fi;
                    l = j->se;
                    r = i;
                } else if(A[i] - j->fi == ans && i - j->se > r - l) {
                    l = j->se;
                    r = i;
                }
            }

            j = mp.upper_bound(A[i]);
            if(j != mp.end()){
                if(A[i] - j->fi + k > ans){
                    ans = A[i] - j->fi + k;
                    l = j->se;
                    r = i;
                } else if(A[i] - j->fi + k == ans && i - j->se > r - l) {
                    l = j->se;
                    r = i;
                }
            }

            if(mp.find(A[i]) == mp.end())
                mp[A[i]] = i;
            // debug(ans, A[i]);
        }

        cout << "Case #" << tc << ": " << ans << ' ' << r-l << endl;
    }
    
    return 0;
}

