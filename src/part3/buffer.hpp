#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <vector>

extern Buffer buffer;

using namespace std;

class Buffer{

	vector<string> quadList;
public:

	Buffer();
	~Buffer();

	void emit(const string& command);
	int nextQuad();

	void print();
	void backpatch(vector<int>& backpatch_list , int lineNum);
};


#endif
