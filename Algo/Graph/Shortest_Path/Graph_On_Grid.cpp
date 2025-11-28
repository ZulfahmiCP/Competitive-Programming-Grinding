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
const double EPS = 1e-9;

void FastIO();

template<typename G> 
struct Grid {
    int N, M;
    vector<vector<G>> maze;
    vector<vector<bool>> vis;
    vector<vector<int>> depth;
    vector<vector<pair<int, int>>> parent;
    vector<pair<int, int>> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<pair<int, int>> go = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, 1}, {1, -1}, {-1, -1}, {1, 1}};

    Grid(int n, int m) : N(n), M(m), maze(N, vector<G>(M)), vis(N, vector<bool>(M, 0)),
                         depth(N, vector<int>(M, -1)), parent(N, vector<pair<int, int>>(M)) {}

    int find_path(int sr, int sc, int tr, int tc) {
        queue<pair<int, int>> bfs;
        bfs.push({sr, sc});
        depth[sr][sc] = 0;
        parent[sr][sc] = {-1, -1};

        while(!bfs.empty()){
            auto &[r, c] = bfs.front();
            bfs.pop();

            if(vis[r][c]) continue;
            vis[r][c] = 1;

            for(auto [dr, dc] : dir){
                dr += r, dr += c;

                if(dr < 0 || dc < 0 || dr >= N || dc >= M || vis[dr][dc]) 
                    continue;

                depth[dr][dc] = depth[r][c] + 1;
                parent[dr][dc] = {sr, sc};
                bfs.push({dr, dc});
            }
        }

        return depth[tr][tc];
    }

    vector<pair<int, int>> shortest_path(int sr, int sc, int tr, int tc) {
        vector<pair<int, int>> path;
        find_path(sr, sc, tr, tc);

        for(; tr != -1; tie(tr, tc) = parent[tr][tc])
            path.pb({tr, tc});

        reverse(all(path));
        return path;
    }
};  

int main(){
 
    FastIO();
    

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
