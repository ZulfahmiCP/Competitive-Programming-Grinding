

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
template<class T> using min_heap = prior_queue<T, vector<T>, greater<T>>;  
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
	int val, size; 
	double prior;
	Node *parent; 
	Node *left;
	Node *right;

	Node() : val(0), prior(-INF), parent(nullptr), left(nullptr), right(nullptr) {}
	Node(int v, double pr) : val(v), prior(pr), parent(nullptr), left(nullptr), right(nullptr) {}
	Node(int v, double pr, Node *p, Node *l, Node *r) : val(v), prior(pr), parent(p), left(l), right(r) {}
};

typedef Node *vertex;

struct Treap {
	vertex root;

	Treap() : root(nullptr) {}

	int get_size(vertex node) {return (node ? node->size : 0);}
	void update_size(vertex node) {
		if(node) node->size = 1 + get_size(node->left) + get_size(node->right);
	}
	
	vertex search(int x) {return search(root, x);}
	vertex search(vertex node, int x) {
		if(!node || x == node->val) return node;
		return x < node->val ? search(node->left, x) : search(node->right, x);
	}

	void left_rotate(vertex x) {
		vertex y = x->right;
		x->right = y->left;

		if(!y->left) y->left->parent = x;
		y->parent = x->parent;

		if(!x->parent) root = y;
		else if (x == x->parent->left) x->parent->left = y;
		else x->parent->right = y;

		y->left = x;
		x->parent = y;

		update_size(x);
	}

	void right_rotate(vertex x) {
		vertex y = x->left;
		x->left = y->right;

		if(!y->right) y->right->parent = x;
		y->parent = x->parent;

		if(!x->parent) root = y;
		else if (x == x->parent->right) x->parent->right = y;
		else x->parent->left = y;

		y->right = x;
		x->parent = y;

		update_size(x);
	}

	void move_up(vertex x) {
		if(!x->parent || x->parent && x->prior >= x->parent->prior) return;
		x == x->parent->left ? right_rotate(x->parent) : left_rotate(x->parent);
		move_up(x);
		update_size(x);
	}
	
	void move_down(vertex x) {
		if(!x->left && !x->right) return;
		if(x->left && x->right) x->left->prior < x->right->prior ? right_rotate(x) : left_rotate(x);
		else if (x->left) right_rotate(x);
		else left_rotate(x);
		move_down(x);
		update_size(x);
	}

	void erase(int v) {erase(root, v);}
	void erase(vertex node, int v) {
		vertex x = nullptr;
		for(;node; node = (node->val <= v ? node->right : node->left)){
			if(node->val == v){
				x = node;
				break;
			}
		}

		if(!x) return;
		move_down(x);

		if(x == x->parent->left) x->parent->left = nullptr;
		else x->parent->right = nullptr;

		delete x;
		x = nullptr;
		update_size(x);
	}

	vertex minimum(vertex node) {
		while(node->left) node = node->left;
		return node;
	}

	vertex maximum(vertex node) {
		while(node->right) node = node->right;
		return node;
	}

	vertex successor(vertex x) {
		if(x->right) return minimum(x->right);

		vertex y = x->parent;
		while(y && x == y->right)
			x = y, y = y->parent;
		return y;
	}

	vertex predecessor(vertex x) {
		if(x->left) return maximum(x->left);

		vertex y = x->parent;
		while(y && x == y->left) 
			x = y, y = y->parent;
		return y;
	}

	void insert(int v, double p) {
		vertex node = new Node(v, p), y = nullptr, x = root;

		while(x) y = x, x = (node->val < x->val ? x->left : x->right);
		node->parent = y;

		if(!y) root = node;
		else if (node->val < y->val) y->left = node;
		else y->right = node;

		if(node->parent) move_up(node);
		update_size(x);
	}

	void split(int x, Treap* t1, Treap* t2) {
		this->insert(x, -INFL);

		t1->root = root->left;
		t2->root = root->right;

		root->left = nullptr;
		root->right = nullptr;
		delete root;
		root = nullptr;
	}

	void merge(Treap t1, Treap t2) {
		vertex mx = t1.maximum(t1.root);
		vertex mn = t2.minimum(t2.root);

		// create a dummy node
		vertex new_root = new Node((mx->val + mn->val) / 2, INFL, nullptr, t1.root, t2.root);
		move_down(new_root);

		vertex cur = new_root;
		while(cur->parent) 
			cur = cur->parent;
		root = cur;

		if(new_root == new_root->parent->left) 
			new_root->parent->left = nullptr;
		else 
			new_root->parent->right = nullptr;

		delete(new_root);
		new_root = nullptr;
	}

	int kth(int k) {return kth(root, k);}
	int kth(vertex node, int k) {
		if(!node) return -1;
		int left_size = get_size(node->left);
		if(k == left_size) return node->val;
		if(k < left_size) return kth(node->left, k);
		return kth(node->right, k - left_size - 1);
	}
};

int main() {



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
