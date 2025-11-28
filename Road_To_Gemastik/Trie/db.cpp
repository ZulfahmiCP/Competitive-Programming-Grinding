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
ttm<ttp T> void debug(set<T> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
ttm<ttp T> void debug(vector<vector<T>> c){for(auto v: c)debug(v);cerr<<'\n';}
ttm<ttp K, ttp V> void debug(map<K, V> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";cerr<<'[';prd(v.fi);cerr <<", ";prd(v.se);cerr<<']';cm = 1;}cerr<<"]\n";}

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

struct Trie {
    int N, cur = 1, LOG;
    vector<array<int, 2>> trie;
    vector<vector<int>> id;
    vector<int> cnt;

    Trie(int n, int k) : N(n), LOG(k - 1), trie(31 * N), cnt(31 * N), id(31 * N) {}

    void insert(int v, int j) { 
        int x = 1;

        for(int i = LOG, c; i >= 0; i--){
            c = (v >> i) & 1;
            if(!trie[x][c])
                trie[x][c] = ++cur;
            
            x = trie[x][c];
            cnt[x]++;
        }

        id[x].pb(j);
    }

    pair<int, int> max_val(int v) {
        int x = 1, ans = 0, y = 0;

        for(int i = LOG, c; i >= 0 && x; i--){
            c = (v >> i) & 1;
            // debug('y', y);

            if(cnt[trie[x][c]]){
                x = trie[x][c];
                if(!c) y |= (1 << i);
            } else {
                x = trie[x][c ^ 1];
            }
        }

        int i = id[x].empty() ? -1 : (id[x][0]);
        return {i, y};
    }
};

int main() {

    FastIO();
    int t,n,k; cin >> t;

    while(t--){
        cin >> n >> k;
        vector<int> A(n);
        Trie trie(n, k);

        for(int &a : A) cin >> a;

        int ians = 0, jans = 1, xans = 0;

        for(int j = 0; j < n; j++){
            auto [i, x] = trie.max_val(A[j]);
            trie.insert(A[j], j);

            x &= ((1 << k) - 1);

            ll cur = (A[i] ^ x) & (A[j] ^ x);
            ll ans = (A[ians] ^ xans) & (A[jans] ^ xans);

            if(i != -1 && cur >= ans)
                ians = i, jans = j, xans = x;
        }

        cout << ians + 1 << ' ' << jans + 1 << ' ' << xans << endl;
    }
    
    return 0;
}
