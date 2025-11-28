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

struct Node {
    int key, height, size;
    Node *left, *right;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1), size(1) {}
};

typedef Node *vertex;

struct AVL {
    vertex root;

    AVL() : root(nullptr) {}

    int height(vertex node) {return node ? node->height : 0;}
    int size(vertex node) {return node ? node->size : 0;}
    int get_balance(vertex node) {return node ? height(node->left) - height(node->right) : 0;}

    vertex rightRotate(vertex y) {
        vertex x = y->left, T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        y->size = size(y->left) + size(y->right) + 1;
        x->size = size(x->left) + size(x->right) + 1;

        return x;
    }

    vertex left_rotate(vertex x) {
        vertex y = x->right;
        vertex T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        x->size = size(x->left) + size(x->right) + 1;
        y->size = size(y->left) + size(y->right) + 1;

        return y;
    }

    void insert(int key) {root = insert(root, key);}
    vertex insert(vertex node, int key) {
        if(!node) return new Node(key);

        if(key == node->key) return node;
        if(key < node->key) node->left = insert(node->left, key);
        else  node->right = insert(node->right, key);

        node->height = 1 + max(height(node->left), height(node->right));
        node->size = 1 + size(node->left) + size(node->right);

        int balance = get_balance(node);

        if(balance > 1 && key < node->left->key)
            return rightRotate(node);

        if(balance < -1 && key > node->right->key)
            return left_rotate(node);

        if(balance > 1 && key > node->left->key) {
            node->left = left_rotate(node->left);
            return rightRotate(node);
        }

        if(balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return left_rotate(node);
        }

        return node;
    }

    vertex min_value(vertex node) {
        vertex cur = node;
        while(cur->left)
            cur = cur->left;
        return cur;
    }

    vertex max_value(vertex node) {
        vertex cur = node;
        while(cur->right)
            cur = cur->right;
        return cur;
    }

    void remove(int key) {root = remove(root, key);}
    vertex remove(vertex root, int key) {
        if(!root) return root;

        if(key < root->key)
            root->left = remove(root->left, key);
        else if (key > root->key)
            root->right = remove(root->right, key);
        else {
            if(!root->left || !root->right){
                vertex cur = root->left ? root->left : root->right;
                if(!cur) cur = root, root = nullptr;
                else *root = *cur;
                delete cur;
            } else {
                vertex cur = min_value(root->right);
                root->key = cur->key;
                root->right = remove(root->right, cur->key);
            }
        }

        if(!root) return root;

        root->height = 1 + max(height(root->left), height(root->right));
        root->size = 1 + size(root->left) + size(root->right);

        int balance = get_balance(root);

        if(balance > 1 && get_balance(root->left) >= 0)
            return rightRotate(root);

        if(balance > 1 && get_balance(root->left) < 0){
            root->left = left_rotate(root->left);
            return rightRotate(root);
        }

        if(balance < -1 && get_balance(root->right) <= 0)
            return left_rotate(root);

        if(balance < -1 && get_balance(root->right) > 0){
            root->right = rightRotate(root->right);
            return left_rotate(root);
        }

        return root;
    }

    int kth(int k) {return kth(root, k);}
    int kth(vertex root, int k) {
        if (!root) return -1;
        int left_size = size(root->left);
        if(left_size == k - 1) return root->key;
        if(left_size > k - 1) return kth(root->left, k);
        return kth(root->right, k - left_size - 1);
    }

};

int main() {

    FastIO();
    int n; cin >> n;
    vector<int> A(n);
    AVL tree;

    for(int &a : A){
        cin >> a;
        tree.insert(a);
    }

    sort(all(A)); 
    for(int i = 0; i < n; i++)
        assert(A[i] == tree.kth(i + 1));

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
