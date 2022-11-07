#ifndef HUFFMAN_H_
#define HUFFMAN_H_
/**
* Project Huffman Coding Algorithm Implementation using Priority Queue
* Testing
* Huffman.h
* Copyright (c) 2022, Myo Aung.
*/
#include <iostream>
#include <queue>
#include <iterator>
#include <map>
#include <vector>
#define MAX_TREE_HT 256
using namespace std;
map<char, int> freqPair;
map<char, string> codes;

struct MinHeapNode {
	char data;												// One of the input characters
	int freq;												// Frequency of the character
	MinHeapNode* left, * right;								// Left and right child
	MinHeapNode(char data, int freq) {
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

bool freq_cmp(const pair<char, int>& x, const pair<char, int>& y) {
	return (x.second > y.second);
}

void getSortedMap(map<char, int>& M) {
	vector<pair<char, int>> vec;
	for (auto& it : M) {
		vec.push_back(it);
	}
	sort(vec.begin(), vec.end(), freq_cmp);
	for (const auto& entry : vec) {
		std::cout << "{" << entry.first << ", " << entry.second << "}" <<
			std::endl;
	}
}

void printCodes(struct MinHeapNode* root, string str) {
	if (!root)
		return;
	if (root->data != '$') {
		cout << root->data << ": " << str << "\n";
	}
	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

struct compare {
	bool operator()(MinHeapNode* l, MinHeapNode* r) {                       // For comparison of two heap nodes(needed in min heap)
		return (l->freq > r->freq);
	}
};

void storeCodes(struct MinHeapNode* root, string str) {
	if (root == NULL)
		return;
	if (root->data != '$')
		codes[root->data] = str;
	storeCodes(root->left, str + "0");
	storeCodes(root->right, str + "1");
}

priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;        // Create a min heap& inserts all characters of data[]

void HuffmanCodes(int size) {
	struct MinHeapNode* left, * right, * top;
	for (map<char, int>::iterator itr = freqPair.begin(); itr != freqPair.end();
		itr++) {
		minHeap.push(new MinHeapNode(itr->first, itr->second));
	}
	while (minHeap.size() != 1) {                                          // Iterate while size of heap doesn't become 1

		left = minHeap.top();											   // Extract the two minimum freq items from min heap
		minHeap.pop();
		right = minHeap.top();
		minHeap.pop();
		top = new MinHeapNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		minHeap.push(top);
	}
	storeCodes(minHeap.top(), "");
	freqPair.clear();
}

void calcFreq(string str, int n) {
	for (int i = 0; i < str.size(); i++) {
		freqPair[str[i]]++;
	}
}

string decode_file(struct MinHeapNode* root, string s) {
	string ans = "";
	struct MinHeapNode* curr = root;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '0')

			curr = curr->left;
		else
			curr = curr->right;
		// reached leaf node
		if (curr->left == NULL && curr->right == NULL) {
			ans += curr->data;
			curr = root;
		}
	}
	// cout<<ans<<endl;
	return ans + '\0';
}

void emptyPQ() {
	while (!minHeap.empty()) {
		minHeap.pop();
	}
}
#endif // !HUFFMAN_H_