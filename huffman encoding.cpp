#include <bits/stdc++.h>
#define sz(x) (int)x.size()
#define entrada freopen("input.txt", "r", stdin);
#define saida freopen("output.txt", "w", stdout);

using namespace std;

struct node { // node com frequencia e letra
	node* left;
	node* right;
	int freq;
	char letra;
	node() { left = right = NULL; freq = 0, letra = '$'; }
	node(int f, char l) { left = right = NULL; freq = f, letra = l; }
};
struct cmp { // so pra ordenar a priority_queue
	bool operator()(node* a, node* b) { return a->freq > b->freq; }
};
struct huffman {
	priority_queue<node*, vector<node*>, cmp> q;
	map<char, int> mp; map<char, string> code; 
	
	node* merge(node* a, node* b) { // unir 2 nodes
		node* c = new node; c->freq = a->freq + b->freq; c->letra = '$';
		return c;
	}
	
	huffman() {
		string str, word;
		while(cin >> word) {
			str += word + " ";
		}
		
		for(auto &i : str) { // mapear as letras e ocorrencias
			if(i != ' ') mp[i]++;
		}
		for(auto const &[a, b] : mp) {
			q.push(new node(b, a));
		}
		if(sz(q) == 1) { 
			auto t = new node; t->left = q.top(), t->right = NULL; q.pop();
			q.push(t);
		}
		while(sz(q) > 1) {// build da huffman tree
			auto r = q.top(); q.pop();
			auto l = q.top(); q.pop();

			auto t = merge(l, r); t->left = l, t->right = r;
			q.push(t);
		}
		if(sz(q) > 0) { dfs(q.top(), ""); q.pop(); } // dfs pra encontrar os caminhos ate as folhas
		
		for(auto const &[a, b] : code) { // codigo de cada letra
			cout << a << ' ' << b << endl;
		}
		cout << endl;
		
		for(auto i : str) { // palavra codificada
			cout << (i == ' ' ? " " : code[i]);
		}
		cout << endl;
	}
	
	void dfs(node* root, string str) {
		if(root->left == NULL && root->right == NULL) {
			code[root->letra] = str;
			return;
		}
		
		if(root->left) {
			dfs(root->left, str + "0");
		}
		if(root->right) {
			dfs(root->right, str + "1");
		}
	}
};
signed main() {
	entrada saida // input e output com freopen
	huffman h;
}
