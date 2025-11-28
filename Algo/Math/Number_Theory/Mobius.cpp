#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <climits>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <string>
#include <bitset>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <deque>
#include <set>
#include <map>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define Int unsigned int 
#define Long unsigned long long int
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& val);
template<typename T, typename... Args>void prd(const T& val, Args... args);
template<typename... Args>void debug(Args... args);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);
template<typename K, typename V>void debug(const map<K, V>& c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const int MAX = 1e6 + 5;
const double EPS = 1e-9;

void FastIO();

struct Mobius {
    int N;
    vector<int> mind, mobius, div;

    Mobius(int n) : N(n), mobius(N + 1, 0), mind(N + 1, -1), div(N + 1, 0) {
        mind[1] = 1;

        for(int i = 2; i <= N; i++) if(mind[i] == -1)
            for(int j = i; j <= N; j += i)
                if(mind[j] == -1) mind[j] = i;

        mobius[1] = 1;
        for(int i = 2; i <= N; i++)
            if(mind[i] != mind[i / mind[i]])
                mobius[i] = -1 * mobius[i / mind[i]];

        for(int i = 1; i <= N; i++)
            for(int j = i; j <= N; j += i)
                div[j] += mobius[i];
    }

    int& operator[](int i) {
        assert(0 <= i && i < N);
        return mobius[i];
    }

    ll coprime_pairs(int n) {
        ll res = 0;
        for(int d = 1; d <= N; d++)
            res += 1LL * mobius[d] * (N / d) * (N / d);
        return res / 2;
    }

    ll gcd_sum(int n) {
        ll res = 0;
        for(int d = 1; d <= N; d++)
            res += 1LL * mobius[d] * div[N / d];
        return res;
    }

    ll lcm_sum(int n) {
        ll res = 0;
        for(int d = 1; d <= N; d++)
            res += 1LL * mobius[d] * div[N / d] * (N / d);
        return res;
    }
} mobius(MAX);

int main() {

    FastIO();
    int n; cin >> n;
    vector<int> A(n);

    for(int &a : A) cin >> a;

    ll ans= 0;

    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            ans += gcd(A[i], A[j]);

    cout << ans;

    int n; cin >> n;
    vector<int> cnt(MAX, 0);

    for(int i = 0, a; i < n; i++){
        cin >> a;
        cnt[a]++;
    }

    ll ans = 0, d = 0;
    for(int i = 1; i < MAX; i++, d = 0){
        if(!mobius[i])
            continue;
        
        for(int j = i; j < MAX; j += i)
            d += cnt[j];

        ans += d * (d - 1) / 2 * mobius[i];
    }

    cout << ans << '\n';

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& val){cerr<<"(";prd(val.fi);cerr<<", ";prd(val.se);cerr<<")";}
template<typename T, typename... Args>void prd(const T& val, Args... args){prd(val);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
