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
    int N, cur = 1;
    const int LOG = 31;
    vector<array<int, 2>> trie;
    vector<int> cnt;
    set<ll> st;

    Trie(int n) : N(n), trie(LOG * N, {0, 0}), cnt(LOG * N, 0) {}

    void insert(ll x) {
        if(st.find(x) != st.end()) return;

        for(int i = LOG, k = 1, b; i >= 0; i--){
            b = (x >> i) & 1;
            if(!trie[k][b])
                trie[k][b] = ++cur;
            k = trie[k][b];
            cnt[k]++;
        }

        st.insert(x);
    }

    void remove(ll x) {
        if(st.find(x) == st.end()) return;

        for(int i = LOG, k = 1, b; i >= 0; i--){
            b = (x >> i) & 1;
            k = trie[k][b];
            cnt[k]--;
        }

        st.erase(x);
    }

    ll min_xor(ll x) {
        ll ans = 0;

        for(int i = LOG, k = 1, b; i >= 0; i--){
            b = (x >> i) & 1;
            ans <<= 1;
            
            if(cnt[trie[k][b]] > 0 && trie[k][b]) 
                k = trie[k][b];
            else 
                ans++, k = trie[k][b ^ 1];
        }

        return ans;
    }
};

int main(){
 
    FastIO();
    int q; cin >> q;
    Trie trie(q);

    for(ll i = 0, t,x; i < q; i++){
        cin >> t >> x;

        if(t == 0)
            trie.insert(x);
        else if(t == 1)
            trie.remove(x);
        else 
            cout << trie.min_xor(x) << endl;
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

/*
6
0 6
0 7
2 5
1 7
1 10
2 7

6 = 110
7 = 111
5 = 101
*/