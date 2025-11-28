#include <bits/stdc++.h>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'
#define endl '\n'

using namespace std;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& x);
template<typename T, typename... A>void prd(const T& x, A... a);
template<typename... A>void debug(A... a);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);
template<typename K, typename V>void debug(const map<K, V>& c);
void fail() {debug("DONE"); exit(0);}

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 2e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct Trie {
    int N, cur = 1, lz = 0;
    const int LOG = 20;
    vector<array<int, 2>> trie;
    vector<int> sub;

    Trie(int n) : N(n + 1), trie(LOG * N), sub(LOG * N) {}

    void insert(int x) {
        int k = 1;
        sub[k]++;

        for(int i = LOG, b; i >= 0; i--){
            b = (x >> i) & 1;
            if(!trie[k][b])
                trie[k][b] = ++cur;
            
            k = trie[k][b];
            sub[k]++;
        }
    }

    void update(int x) {
        lz ^= x;
    }

    int mex() {
        int ans = 0, k = 1;

        for(int i = LOG, b; i >= 0 && k; i--){
            b = (lz >> i) & 1;

            if(trie[k][b] && sub[trie[k][b]] == (1 << i)){
                ans |= (1 << i);
                k = trie[k][b ^ 1];
            } else {
                k = trie[k][b];
            }
        }

        return ans;
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    Trie trie(n);
    set<int> s;

    for(int i = 0, x; i < n; i++){
        cin >> x;
        if(s.find(x) != s.end()) continue;
        trie.insert(x);
        s.insert(x);
    }

    for(int i = 0, x; i < q; i++){
        cin >> x;
        trie.update(x);
        cout << trie.mex() << endl;
    }

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
template<typename T, typename... A>void prd(const T& x, A... a){prd(x);cerr<<", ";prd(a...);}
template<typename... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
