#include <bits/stdc++.h>
#define ll long long
#define fi first  
#define se second 
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()

using namespace std;
void FastIO() {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

struct Trie {
    static const int K = 26;
    struct Node {
        int next[26], pref_cnt = 0;
        bool is_word = false;

        Node(){fill(next, next + K, -1);}

        bool empty() {
            for(int i = 0; i < K; i++)
                if(next[i]) return 0;
            return 1;
        }

        int &operator[](int i){assert(0 <= i && i < K); return next[i];}
        int &operator[](char c){assert('a' <= c && c <= 'z'); return next[c - 'a'];}
    };

    int N;
    vector<Node> trie;

    Trie() : trie(1), N(0) {}

    void insert(const string &s) {
        int x = 0;

        for(char c : s){
            if(trie[x][c] == -1){
                trie[x][c] = sz(trie);
                trie.pb(Node());
            }
            x = trie[x][c];
            trie[x].pref_cnt++;
        }

        trie[x].is_word = true;
    }

    int cnt(string s) {
        reverse(all(s));
        int x = 0, ans = 0;

        for(char c : s){
            if(trie[x][c] == -1)
                return ans;
            x = trie[x][c];
            ans += trie[x].pref_cnt;
        }

        return ans;
    }
};

int main() {

    FastIO();
    int n; cin >> n;
    vector<string> S(n);
    Trie trie;

    for(auto &s : S) cin >> s;

    for(auto &s : S) trie.insert(s);

    ll ans = 0;

    for(auto &s : S){
        ans += 1LL * sz(s) * (2 * n);
        ans -= 2 * trie.cnt(s);
        // cout << s << ' ' << trie.cnt(s) << '\n';
    }

    cout << ans << '\n';
    
    return 0;
}