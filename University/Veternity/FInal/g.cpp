#include <bits/stdc++.h>
#define ll long long 
using namespace std;

const int INF = 1e9 + 7;

struct Trie {
    int N, cur = 1, LOG = 30;
    vector<array<int, 2>> trie;
    vector<int> mx;

    Trie(int n) : N(n + 1), trie(LOG * N), mx(LOG * N, 0) {
        insert(0, 0);
    } 

    void insert(int v, int j) {
        for(int i = LOG, x = 1, c; i >= 0; i--){
            c = (v >> i) & 1;
            if(!trie[x][c])
                trie[x][c] = ++cur;
            x = trie[x][c];
            mx[x] = max(mx[x], j);
        }
    }

    int count(int v, int u) {
        int ans = 0, x = 1;

        for(int i = LOG; i >= 0 && x; i--){
            int cv = (v >> i) & 1;
            int cu = (u >> i) & 1;

            if(!cu){
                if(trie[x][cv ^ 1])
                    ans = max(ans, mx[x]);
                x = trie[x][cv];
            } else 
                x = trie[x][cv ^ 1];
        }

        return ans;
    }
};

int main() {

    int n,m; cin >> n >> m;
    vector<int> A(n);
    Trie trie(n);

    for(int &a : A) cin >> a;
    for(int i = 1; i < n; i++)
        A[i] ^= A[i - 1];

    int ans = INF;

    for(int i = 0; i < n; i++){
        int j = trie.count(A[i], m - 1);
        
        cout << i+1 << ' ' << j << endl;
        if(j) ans = min(ans, i - j + 1);

        trie.insert(A[i], i + 1);
    }

    cout << ans << endl;

    return 0;
}
