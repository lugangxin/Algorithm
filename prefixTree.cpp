#include<iostream>
using namespace std;
#include<vector>
class Trie1 {
public:
	bool isWord;
	vector<Trie1*> children;
	Trie1() :isWord(false),children(26,NULL){}
	void insert(string word) {
		Trie1* node = this;
		for (char ch:word) {
			if (node->children[ch-'a']==NULL) {
				node->children[ch - 'a'] = new Trie1();
			}
			node=node->children[ch - 'a'];
		}
		node->isWord = true;
	}
};
class TrieNode {
public:
	int pass;
	int end;
	TrieNode* nexts[26];
	TrieNode() {
		pass = 0;
		end = 0;
	}
};
class Trie {
private:
	TrieNode* root;
public:
	Trie() {
		root = new TrieNode();
	}
	void insert(string word) {
		if (word == "") return;
		TrieNode* node = root;
		node->pass++;
		int index = 0;
		for (char ch:word) {
			index = ch - 'a';
			if (node->nexts[index] == NULL) {
				node->nexts[index] = new TrieNode();
			}
			node = node->nexts[index];
			node->pass++;
		}
		node->end++;
	}
	//查单词出现过几次
	int search(string word) {
		if (word == "") return 0;
		TrieNode* node = root;
		int index = 0;
		for (char ch : word) {
			index = ch - 'a';
			if (node->nexts[index] == NULL) {
				return 0;
			}
			node = node->nexts[index];
		}
		return node->end;
	}
	//有多少以这个为前缀
	int prefixNum(string pre) {
		if (pre == "") return 0;
		TrieNode* node = root;
		int index = 0;
		for (char ch : pre) {
			index = ch - 'a';
			if (node->nexts[index] == NULL) {
				return 0;
			}
			node = node->nexts[index];
		}
		return node->pass;
	}
	void deleteWord(string word) {
		if (search(word)!=0) {
			TrieNode* node = root;
			node->pass--;
			int index = 0;
			for (char ch:word) {
				index = ch - 'a';
				if (--node->nexts[index]->pass==0) {
					node->nexts[index] = NULL;//c++应该遍历到底去析构
					return;
				}
				node = node->nexts[index];
			}
			node->end--;
		}
	}
};