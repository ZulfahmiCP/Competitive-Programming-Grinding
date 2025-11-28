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

#include <bits/stdc++.h>

#define pb push_back
#define sz(x) (int)x.size()
#define all(x) (x).begin(), (x).end()

using namespace std;

struct Trie {
    static const int K = 26;
    struct Node {
        int next[K];
        int word_cnt;
        int pref_cnt;

        Node() {
            fill(next, next + K, 0); // 0 adalah indeks null/kosong
            word_cnt = 0;
            pref_cnt = 0;
        }
        
        // Operator untuk akses anak berdasarkan karakter
        int& operator[](char c) { 
            return next[c - 'a']; 
        }
    };

    int cur;
    vector<Node> trie;
    vector<int> roots; // Menyimpan root dari setiap versi

    Trie(int max_total_chars) {
        // Alokasi memori yang aman
        trie.resize(max_total_chars + 2); 
        cur = 1;       // Node 0 adalah null, root dimulai dari indeks 1
        roots.pb(1);   // Versi 0 (awal) adalah root 1 (Trie kosong)
    }
    
private:
    // Fungsi insert privat yang mengembalikan root baru
    int _insert(int old_root, const string& s) {
        int new_root = ++cur;
        trie[new_root] = trie[old_root]; // Salin root lama
        trie[new_root].pref_cnt++;

        int v_old = old_root;
        int v_new = new_root;

        for (char ch : s) {
            int old_child = trie[v_old][ch];
            int new_child = ++cur;
            trie[new_child] = trie[old_child]; // Salin node anak
            
            trie[v_new][ch] = new_child; // Arahkan ke anak yang baru
            trie[v_new].pref_cnt++;
            
            v_new = new_child;
            v_old = old_child;
        }
        trie[v_new].word_cnt++;
        return new_root;
    }

public:
    // Fungsi publik untuk membuat versi baru dengan menambahkan string
    void create_new_version_with(const string& s) {
        roots.pb(_insert(roots.back(), s));
    }

    // Fungsi search pada versi tertentu
    bool search(int version, const string &s) {
        if (version < 0 || version >= sz(roots)) return false;
        int v = roots[version];
        for (char ch : s) {
            if (trie[v][ch] == 0) return false;
            v = trie[v][ch];
        }
        return trie[v].word_cnt > 0;
    }

    // Fungsi hitung prefix pada versi tertentu
    int count_prefix(int version, const string& s) {
        if (version < 0 || version >= sz(roots)) return 0;
        int v = roots[version];
        for (char ch : s) {
            if (trie[v][ch] == 0) return 0;
            v = trie[v][ch];
        }
        return trie[v].pref_cnt;
    }
};

// --- Contoh Penggunaan ---
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    Trie pt(1000); // Alokasi untuk maks 1000 node baru

    // Versi 0: Kosong
    cout << "Versi 0 - Cek 'hello': " << pt.search(0, "hello") << endl;

    // Buat Versi 1 dengan menambahkan "hello"
    pt.create_new_version_with("hello");
    cout << "Versi 1 - Cek 'hello': " << pt.search(1, "hello") << endl;
    cout << "Versi 1 - Cek 'hell': " << (pt.count_prefix(1, "hell") > 0) << endl;
    
    // Buat Versi 2 dengan menambahkan "world" ke versi terbaru (versi 1)
    pt.create_new_version_with("world");
    cout << "Versi 2 - Cek 'world': " << pt.search(2, "world") << endl;
    // 'hello' masih ada karena versi 1 tidak diubah
    cout << "Versi 2 - Cek 'hello': " << pt.search(2, "hello") << endl;

    // Cek kembali versi 1, ia tetap tidak berubah
    cout << "Versi 1 (setelah update lain) - Cek 'world': " << pt.search(1, "world") << endl;

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
