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

struct BST {
	struct node {
		int val;
		node *left, *right;

		node() : left(NULL), right(NULL) {}
		node(int v) : val(v), left(NULL), right(NULL) {}
		node(int v, node *left, node *right) : val(v), left(left), right(right) {}
	};

	node *root;

	BST() : root(NULL) {}
	BST(const vector<int> &arr) {
		for(const int &a : arr)
			insert(a);
	}

	void insert(int v) {
		insert(v, root);
	}

	node* insert(int v, node *cur) {
		if(!cur) return cur = new node(v);
		if(cur->val < v) cur->left = insert(v, cur->left);
		else cur->right = insert(v, cur->right);
		return cur;
	}

	void erase(int v) {
		erase(v, root);
	}

	node *erase(int v, node *cur) {
		if(!cur) return cur;

		if(cur->val == v){
			node* temp;
			if(!cur->left){
				temp = cur->right;
				delete cur;
				return temp;
			} 
			
			if(!cur->right) {
				temp = cur->left;
				delete cur;
				return temp;
			}

			temp = min_val(cur->right);
			cur->val = temp->val;
			cur->right = erase(temp->val, cur->right);
		}

		if(cur->val < v) cur->left = erase(v, cur->left);
		if(cur->val > v) cur->right = erase(v, cur->right);

		return cur;
	}

	bool search(int v) {
		return search(v, root);
	}

	bool search(int v, node *cur) {
		if(!cur) return 0;
		if(cur->val == v) return 1;
		return cur->val < v ? search(v, cur->left) : search(v, cur->right);
	}

	int min_val() {return min_val(root)->val;}
	node* min_val(node *cur) {
		return !cur->left ? cur : min_val(cur->left);
	}

	int max_val() {return max_val(root)->val;}
	node* max_val(node *cur) {
		return !cur->right ? cur : max_val(cur->right);
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
