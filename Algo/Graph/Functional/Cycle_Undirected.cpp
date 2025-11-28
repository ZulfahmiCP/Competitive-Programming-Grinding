
#include <iostream>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <numeric>
#include <vector>
#include <string>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <deque>
#include <set>
#include <map>
#define X first 
#define Y second 
#define Int int64_t
#define pb push_back
#define pf push_front
#define ld long double
#define ll long long int
#define ull unsigned long long int
#define min_heap priority_queue<int, vector<int>, greater<int>>
#define all(x) x.begin(), x.end()
#define All(x) x.rbegin(), x.rend()
#define Map unordered_map
#define Set unordered_set
using namespace std;
 
template <typename T>
    void printDebug(const T& x);
template <typename T, typename U>
    void printDebug(const pair<T, U>& value);
template <typename T, typename... Args>
    void printDebug(const T& value, Args... args);
template <typename... Args>
    void Debug(Args... args);
template <typename K, typename V>
    void Debug(const map<K, V>& container);
template <typename T>
    void Debug(const set<T>& container);
template <typename T>
    void Debug(const vector<T>& container);
 
void FastIO();
void FreeOpen();
void UsacoOpen();

struct UndirectedGraph {
    int n; 
    vector<vector<int>> adj;
    vector<bool> visited;
    set<int> in_current_path;
    vector<vector<int>> allCycles;

    UndirectedGraph(int v) : n(v) {
        adj.resize(v);
        visited.resize(v, 0);
    }

    void addGraph(const vector<vector<int>>& adjacencyList) {
        adj = adjacencyList;
        n = adjacencyList.size();
    }

    void findAllCycles() {
        for (int i = 0; i < n; ++i) if (!visited[i]) {
            vector<int> current_path;
            dfs(i, -1, current_path);
        }
    }

    void dfs(int node, int parent, vector<int>& current_path) {
        visited[node] = 1;
        current_path.push_back(node);
        in_current_path.insert(node);

        for(int adjNode : adj[node]){
            if (adjNode == parent) 
                continue; 

            if (in_current_path.find(adjNode) != in_current_path.end()) {
                vector<int> cycle;
                for (int i = current_path.size() - 1, cur_node; i >= 0; --i) {
                    cur_node = current_path[i];
                    cycle.push_back(cur_node);
                    if(node == adjNode) 
                        break;
                }

                allCycles.push_back(cycle);
            } else if(!visited[adjNode]) 
                dfs(adjNode, node, current_path);
        }

        current_path.pop_back();
        in_current_path.erase(node);
    }

    void printAllCycles() {
        for (const vector<int>& cycle : allCycles){
            for (int node : cycle) 
                cout << node << ' ';
            cout << cycle.front() << endl;
        }
    }
};

int main(){
 
    FastIO();
    

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void printDebug(const T& x){ cout << x; }
template <typename T, typename U>void printDebug(const pair<T, U>& value){ cout << "("; printDebug(value.first); cout << ", "; printDebug(value.second); cout << ")"; }
template <typename T, typename... Args>void printDebug(const T& value, Args... args){printDebug(value); cout << ", "; printDebug(args...); }
template <typename... Args> void Debug(Args... args){ cout << "[";  printDebug(args...); cout << "]\n"; }
template <typename K, typename V> void Debug(const map<K, V>& container){ cout << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cout << ", "; cout << '['; printDebug(k); cout << ", "; printDebug(v); cout << ']'; comma = 1; } cout << "]\n"; }
template <typename T> void Debug(const set<T>& container) { cout << '['; bool comma = 0; for (const auto& st : container) { if (comma) cout << ", "; printDebug(st); comma = 1; } cout << "]\n";}
template <typename T> void Debug(const vector<T>& container) { cout << '['; bool comma = 0; for (const auto& v : container){ if(comma) cout << ", "; printDebug(v); comma = 1; } cout << "]\n"; }
