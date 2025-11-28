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
template<typename K, typename V>void debug(const map<K, V>& c);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct Manacher {
    int N;
    string s;
    vector<int> p_odd, p_even;

    Manacher(const string& t) : N(sz(t)), s(t), p_odd(N, 0), p_even(N, 0) {
        for(int i = 0, l = 0, r = -1, k; i < N; i++){
            k = (i > r) ? 1 : min(p_odd[l + r - i], r - i + 1);
            while(i >= k && i + k < N && s[i - k] == s[i + k]) 
                k++;

            p_odd[i] = k--;
            if(i + k > r)
                l = i - k, r = i + k;
        }

        for(int i = 0, l = 0, r = -1, k; i < N; i++){
            k = (i > r) ? 0 : min(p_even[l + r - i + 1], r - i + 1);
            while (i >= k + 1 && i + k < N && s[i - k - 1] == s[i + k]) 
                k++;

            p_even[i] = k--;
            if(i + k > r)
                l = i - k - 1, r = i + k;
        }
    }   

    vector<string> palindrome() {
        vector<string> P;

        for(int i = 0; i < N; i++){
            if(p_odd[i] > 1)
                P.pb(s.substr(i - p_odd[i] + 1, 2 * p_odd[i] - 1));
            if(p_even[i] > 0)
                P.pb(s.substr(i - p_even[i], 2 * p_even[i]));
        }

        return P;
    }

    string longest_palindrome() {
        string best_odd, best_even;
        int best = 0;

        for(int i = 0; i < N; i++)
            if(p_odd[i] > p_odd[best])
                best = i;

        best_odd = s.substr(best - p_odd[best] + 1, 2 * p_odd[best] - 1);
        best = 0;

        for(int i = 0; i < N; i++)
            if(p_even[i] > p_even[best])
                best = i;
        
        best_even = s.substr(best - p_even[best], 2 * p_even[best]);

        return sz(best_odd) > sz(best_even) ? best_odd : best_even;
    }
};

int main() {
    
    FastIO();
    string s, ans; cin >> s;
    Manacher str(s);

    debug(str.longest_palindrome().size());

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& val){cerr<<"(";prd(val.fi);cerr<<", ";prd(val.se);cerr<<")";}
template<typename T, typename... Args>void prd(const T& val, Args... args){prd(val);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr<<"]\n";}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
