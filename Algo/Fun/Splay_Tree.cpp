// Splay tree implementation in C++
// Author: Algorithm Tutor
// Tutorial URL: http://algorithmtutor.com/Val-Structures/Tree/Splay-Trees/

#include <bits/stdc++.h>
using namespace std;

struct SplayTree {
	struct node {
		int val;
		node *parent, *left, *right; 

		node() : parent(NULL), left(NULL), right(NULL) {}
		node(int v) : val(v), parent(NULL), left(NULL), right(NULL) {} 
	};

	node* root;
	
	SplayTree() : root(NULL) {}
	SplayTree(const vector<int> &arr) {
		for(const int &a : arr)
			insert(a);
	}

	node* search(int v) {
		node* cur = search(root, v);
		if(cur) splay(cur);
		return cur;
	}
	
	node* search(node* cur, int v) {
		if(!cur || v == cur->val) return cur;
		return v < cur->val ? search(cur->left, v) : search(cur->right, v);
	}

	node* min(node* cur) {
		return !cur->left ? cur : min(cur->left);
	}

	node* max(node* cur) {
		return !cur->right ? cur : max(cur->right);
	}

	node* successor(node* x) {
		if(x->right) return min(x->right);

		node* y = x->parent;
		while(y && x == y->right) 
			x = y, y = y->parent;
		return y;
	}

	node* predecessor(node* x) {
		if(x->left) return max(x->left);

		node* y = x->parent;
		while(y && x == y->left) 
			x = y, y = y->parent;
		return y;
	}

	void insert(int v) {
		node* cur = new node(v);
		node *y, *x = root;

		while(x) y = x, x = cur->val < x->val ? x->left : x->right;
		cur->parent = y;

		if(!y) root = cur;
		else if (cur->val < y->val) y->left = cur;
		else y->right = cur;

		splay(cur);
	}

	void erase(int v) {
		erase(root, v);
	}

	void erase(node* cur, int v) {
		node *x, *t, *s;
		while(cur){
			if(cur->val == v) x = cur;
			cur = cur->val <= v ? cur->right : cur->left;
		}

		if(!x) return;

		split(x, s, t); 
		if(s->left) s->left->parent = NULL;
		root = join(s->left, t);
		delete s;
		s = NULL;
	}

	void left_rotate(node* x) {
		node* y = x->right;
		x->right = y->left;

		if(y->left) y->left->parent = x;
		y->parent = x->parent;

		if(x->parent) root = y;
		else if(x == x->parent->left) x->parent->left = y;
		else x->parent->right = y;

		y->left = x;
		x->parent = y;
	}

	void right_rotate(node* x) {
		node* y = x->left;
		x->left = y->right;
		
		if(y->right) y->right->parent = x;
		y->parent = x->parent;

		if(!x->parent) root = y;
		else if (x == x->parent->right) x->parent->right = y;
		else x->parent->left = y;

		y->right = x;
		x->parent = y;
	}

	void splay(node* x) {
		while (x->parent) {
			if (!x->parent->parent) {
				x == x->parent->left ? right_rotate(x->parent) : left_rotate(x->parent);
			} else if (x == x->parent->left && x->parent == x->parent->parent->left) {
				right_rotate(x->parent->parent);
				right_rotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->right) {
				left_rotate(x->parent->parent);
				left_rotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->left) {
				left_rotate(x->parent);
				right_rotate(x->parent);
			} else {
				right_rotate(x->parent);
				left_rotate(x->parent);
			}
		}
	}

	node* join(node* s, node* t){
		if(!s) return t;
		if(!t) return s;

		node* x = max(s);
		splay(x);
		x->right = t;
		t->parent = x;
		return x;
	}

	void split(node* &x, node* &s, node* &t) {
		splay(x);

		if(x->right){
			t = x->right;
			t->parent = NULL;
		} else {
			t = NULL;
		}

		s = x;
		s->right = NULL;
		x = NULL;
	} 
};

int main() {

	SplayTree tree;
	tree.insert(33);
	tree.insert(44);
	tree.insert(67);
	tree.insert(5);
	tree.insert(89);
	tree.insert(41);
	tree.insert(98);
	tree.insert(1);
	tree.search(33);
	tree.search(44);
	tree.erase(89);
	tree.erase(67);
	tree.erase(41);
	tree.erase(5);
	tree.erase(98);
	tree.erase(1);
	tree.erase(44);
	tree.erase(33);
	
	return 0;
}