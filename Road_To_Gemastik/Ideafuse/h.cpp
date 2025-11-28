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

struct BinTree {
    int H;
    vector<int> pwt;

    BinTree(int h) : H(h), pwt(H+1) {
        pwt[0] = 1;
        for(int i = 1; i <= H; i++)
            pwt[i] = pwt[i - 1] << 1;
    }

    int query(int u) {   
        vector<int> path;

        for(;u > 1; u >>= 1)
            path.pb(u & 1);

        reverse(all(path));
        // debug(path);

        int v = 0;

        for(int d = 0; d < sz(path); d++){
            if(!(v & 1)){ // kanan
                if(path[d]) 
                    v += pwt[H - d - 1];
                else 
                    v++;
            } else { // kiri
                if(!path[d]) 
                    v += pwt[H - d - 1];
                else 
                    v++;
            }
        }

        return v + 1;
    }
};  

int main() {

    FastIO();
    int T,h,q; cin >> T;

    for(int tc = 1; tc <= T; tc++){
        cin >> h >> q;
        BinTree tree(h);

        cout << "Case #" << tc << ": ";

        for(int i = 0, u; i < q; i++){
            cin >> u;
            cout << tree.query(u) << ' ';
        } 

        cout << endl;
    }
    
    return 0;
}

/*
2
4 3
6 4 15
11 4
1024 2045 1234 2047

1
4 3
6 4 15
*/