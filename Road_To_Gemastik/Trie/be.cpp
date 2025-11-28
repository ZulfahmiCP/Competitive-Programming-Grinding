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
    int N, cur = 1, LOG = 30;
    vector<array<int, 2>> trie;
    vector<int> cnt;

    Trie() {}
    Trie(int n) : N(n + 1), trie(N * LOG), cnt(N * LOG) {
        insert(0);
    }

    void insert(int v) {
        for(int i = LOG, x = 1, c; i >= 0; i--){
            c = (v >> i) & 1;
            if(!trie[x][c])
                trie[x][c] = ++cur;
            x = trie[x][c];
            cnt[x]++;
        }
    }

    int max_xor(int v) {
        int ans = 0, x = 1;

        for(int i = LOG, c; i >= 0 && x; i--){
            c = (v >> i) & 1;

            if(trie[x][c ^ 1]){
                ans |= (1 << i), x = trie[x][c ^ 1];
            } else {
                x = trie[x][c];
            }
        }

        return ans;
    }
};

int main(){
 
    FastIO();
    int n, m; cin >> n >> m;
    vector<int> A(n + 1, 0), B(m + 1, 0);

    for(int i = 1; i <= n; i++){
        cin >> A[i];
        A[i] ^= A[i - 1];
    }

    for(int i = 1; i <= m; i++){
        cin >> B[i];
        B[i] ^= B[i - 1];
    }

    array<array<Trie, 2>, 2> trie;

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            trie[i][j] = Trie(n * m);


    auto par = [](int x) {return x & 1;};

    int ans = 0;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            ans = max(ans, trie[par(i)][par(j)].max_xor(A[i] ^ B[j]));
            trie[par(i)][par(j)].insert(A[i] ^ B[j]);
        }
    }

    Trie trie2(n);
    for(int i = 1; i <= n; i++){
        ans = max(ans, trie2.max_xor(A[i]));
        trie2.insert(A[i]);
    }

    Trie trie3(m);
    for(int j = 1; j <= m; j++){
        ans = max(ans, trie3.max_xor(B[j]));
        trie3.insert(B[j]);
    }

    cout << ans << endl;

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
