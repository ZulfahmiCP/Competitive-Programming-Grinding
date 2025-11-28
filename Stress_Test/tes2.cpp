struct Trie {
    static const int LOG = 30;
    struct Node {
        int next[2];
        int time = -1;
        int cnt = 0;

        Node() {fill(next, next + 2, 0);}

        int &operator[](int i) {assert(0 <= i && i < 2); return next[i];}
    };

    int N, last = 1;
    vector<Node> trie;
    vector<int> rt; 

    Trie(int n, int m) : N(n), trie(2), rt(m + 1) {
        rt[0] = 1;
    }

    int clone(int i) {
        int j = sz(trie);
        trie.pb(Node());
        if(i != 0) trie[j] = trie[i];
        return j;
    }

    bool go(int i, int l) {
        return (i ? trie[i].time >= l : 0);
    }

    void insert(int v, int t) {
        int x = clone(last);
        rt[t + 1] = last = x;

        for(int i = LOG; i >= 0; i--){
            int c = (v >> i) & 1;
            
            trie[x][c] = clone(trie[x][c]);

            x = trie[x][c];
            trie[x].time = t;
            trie[x].cnt++;
        }
    }
    
    int max_xor(int l, int r, int v) {
        int ans = 0, x = rt[r + 1];

        for(int i = LOG, c; i >= 0; i--){
            c = (v >> i) & 1;
            ans <<= 1;

            if(go(trie[x][c ^ 1], l)){
                ans++;
                x = trie[x][c ^ 1];
            } else {
                x = trie[x][c];
            }
        }
        return ans;
    }
};
