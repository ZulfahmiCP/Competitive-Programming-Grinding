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

struct Trie {
    static const int K = 10;
    struct Node {
        int next[K];

        Node() {fill(next, next + K, -1);}

        int &operator[](int i) {assert(0 <= i && i < K); return next[i];}
    };
    
    vector<Node> trie;

    Trie() : trie(1) {}

    void insert(vector<int> &A) {
        int x = 0;

        for(int &a : A){
            if(trie[x][a] == -1){
                trie[x][a] = sz(trie);
                trie.pb(Node());
            }

            x = trie[x][a];
        }
    }

    int cnt(vector<int> &A) {
        int x = 0, ans = 0;

        for(int &a : A){
            if(trie[x][a] == -1) break;
            ans++;
            x = trie[x][a];
        }

        return ans;
    }

    void clear() {
        trie.clear();
        trie.pb(Node());
    }
} trie;

int main() {

    FastIO();
    int t,n,m; cin >> t;

    while(t--){
        cin >> m >> n;
        vector<vector<int>> P(m, vector<int>(n));
        vector<vector<int>> Q(m, vector<int>(n));
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                cin >> P[i][j], P[i][j]--;
                Q[i][P[i][j]] = j;
            }

            trie.insert(Q[i]);
        }

        for(int i = 0; i < m; i++)
            cout << trie.cnt(P[i]) << " \n"[i == m - 1];
        
        trie.clear();
    }
    
    return 0;
}
