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
    // 16
    // x 2 4 x 6 8 x 10 12 x 14 16 
    // x 2 4 x 6 8 x 10 12 x 14 16 x 3 9 x 15 
    // 1 2 4 5 6 8 7 10 12 11 14 16 13 3 9 15

    int t,n; cin >> t;

    while(t--){
        cin >> n;
        vector<int> A(n, 0), done(n+1, 0);

        int j = 2;

        for(int i = 1; i < n && j <= n; i += 3){
            if(i + 2 > n) break;
            
            if(!(j % 2) && j+2 <= n){
                A[i] = j;
                A[i+1] = j+2;
                done[j] = done[j+2] = 1;

                j += 4;

                if(j > n || j + 2 > n) j = 3;
            } else if(!(j % 3) && j+6 <= n) {
                A[i] = j;
                A[i+1] = j+6;
                done[j] = done[j+6] = 1;

                j += 12;

                if(j > n) break;
            } else {
                break;
            }
        }

        j = 1;

        for(int &a : A){
            if(a == 0){
                a = j;
                done[a] = 1;
                while(j <= n && done[j]) j++;
            }

            cout << a << ' ';
        }

        cout << endl;
    }
    
    return 0;
}
