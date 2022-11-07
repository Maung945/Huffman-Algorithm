#include <fstream>
#include <string>
#include "Huffman.h"
using namespace std;
/**
* Project Huffman Coding Algorithm Implementation using Priority Queue
* Testing
* HuffmanCoding.cpp
* Copyright (c) 2022, Myo Aung.
*/

void huffPrint(string str) {
	string encodedString, decodedString;
	int n = str.length();
	cout << "The legth: " << n << endl;
	calcFreq(str, str.length());
	getSortedMap(freqPair);
	cout << endl;
	cout << "Binary Format:" << endl;
	cout << "--------------";
	HuffmanCodes(n);
	cout << endl;
	for (auto v = codes.begin(); v != codes.end(); v++)
		cout << v->first << ' ' << v->second << endl;
	for (auto i : str)
		encodedString += codes[i];
	cout << "\nEncoded Huffman data:\n" << encodedString << endl;
	decodedString = decode_file(minHeap.top(), encodedString);
	cout << "\nDecoded Huffman Data:\n" << decodedString << endl;
	cout << "===================================================" << endl;
	codes.clear();
}

int main()
{
	fstream file("Huffman Test Strings.txt", ios::in);
	string str;
	if (file.is_open()) {
		while (getline(file, str)) {
			huffPrint(str);
			emptyPQ();
		}
	}
	else {
		cout << "EROOR!! FILE IS NOT FOUND!" << endl;
	}
	return 0;
}
