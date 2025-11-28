#include <bits/stdc++.h>
using namespace std;

struct TNode {
    TNode* ch[26];
    bool end;
    TNode() { 
        memset(ch, 0, sizeof(ch)); 
        end = false; 
    }
};

struct SNode {
    TNode* trie;
    SNode* l, *r;
    SNode() { 
        trie = new TNode(); 
        l = r = nullptr; 
    }
    SNode(SNode* prev) {
        trie = new TNode();
        if (prev) {
            memcpy(trie->ch, prev->trie->ch, sizeof(prev->trie->ch));
            trie->end = prev->trie->end;
        }
        l = r = nullptr;
    }
};

class PST {
private:
    vector<SNode*> roots;
    int n;
    
    void ins(TNode* node, const string& s, int idx) {
        if (idx == s.size()) {
            node->end = true;
            return;
        }
        int c = s[idx] - 'a';
        if (!node->ch[c]) node->ch[c] = new TNode();
        ins(node->ch[c], s, idx + 1);
    }
    
    TNode* copy(TNode* node) {
        if (!node) return nullptr;
        TNode* nn = new TNode();
        memcpy(nn->ch, node->ch, sizeof(node->ch));
        nn->end = node->end;
        return nn;
    }
    
    void merge(TNode* dest, TNode* src) {
        if (!src) return;
        dest->end |= src->end;
        for (int i = 0; i < 26; i++) {
            if (src->ch[i]) {
                if (!dest->ch[i]) dest->ch[i] = new TNode();
                merge(dest->ch[i], src->ch[i]);
            }
        }
    }
    
    SNode* upd(SNode* node, int tl, int tr, int pos, const string& s) {
        SNode* nn = new SNode();
        if (tl == tr) {
            ins(nn->trie, s, 0);
            return nn;
        }
        
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            nn->l = upd(node ? node->l : nullptr, tl, tm, pos, s);
            nn->r = node ? node->r : nullptr;
        } else {
            nn->l = node ? node->l : nullptr;
            nn->r = upd(node ? node->r : nullptr, tm + 1, tr, pos, s);
        }
        
        if (nn->l && nn->l->trie) merge(nn->trie, nn->l->trie);
        if (nn->r && nn->r->trie) merge(nn->trie, nn->r->trie);
        
        return nn;
    }
    
    bool qry2(TNode* node, const string& s, int idx) {
        if (!node) return false;
        if (node->end && idx <= s.size()) return true;
        if (idx == s.size()) return false;
        
        int c = s[idx] - 'a';
        return qry2(node->ch[c], s, idx + 1);
    }
    
    bool qry3(TNode* node, const string& s, int idx) {
        if (!node) return false;
        if (idx == s.size()) return node->end || hasAny(node);
        
        int c = s[idx] - 'a';
        return qry3(node->ch[c], s, idx + 1);
    }
    
    bool hasAny(TNode* node) {
        if (!node) return false;
        if (node->end) return true;
        for (int i = 0; i < 26; i++) {
            if (hasAny(node->ch[i])) return true;
        }
        return false;
    }
    
    TNode* qRange(SNode* node, int tl, int tr, int l, int r) {
        if (!node || l > tr || r < tl) return nullptr;
        if (l <= tl && tr <= r) return node->trie;
        
        int tm = (tl + tr) / 2;
        TNode* lt = qRange(node->l, tl, tm, l, r);
        TNode* rt = qRange(node->r, tm + 1, tr, l, r);
        
        if (!lt) return rt;
        if (!rt) return lt;
        
        TNode* res = new TNode();
        merge(res, lt);
        merge(res, rt);
        return res;
    }
    
public:
    PST(int sz) : n(sz) {
        roots.push_back(nullptr);
    }
    
    void upd(int pos, const string& s) {
        SNode* nr = upd(roots.back(), 0, n - 1, pos, s);
        roots.push_back(nr);
    }
    
    bool vpfx(int l, int r, const string& s) {
        TNode* trie = qRange(roots.back(), 0, n - 1, l, r);
        return qry2(trie, s, 0);
    }
    
    bool spfx(int l, int r, const string& s) {
        TNode* trie = qRange(roots.back(), 0, n - 1, l, r);
        return qry3(trie, s, 0);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    PST pst(n);
    
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        pst.upd(i, s);
    }
    
    int q;
    cin >> q;
    
    while (q--) {
        int t;
        cin >> t;
        
        if (t == 1) {
            int i;
            string s;
            cin >> i >> s;
            pst.upd(i - 1, s);
        } else {
            int l, r;
            string s;
            cin >> l >> r >> s;
            l--; r--;
            
            if (t == 2) {
                cout << (pst.vpfx(l, r, s) ? "Y" : "N") << "\n";
            } else {
                cout << (pst.spfx(l, r, s) ? "Y" : "N") << "\n";
            }
        }
    }
    
    return 0;
}