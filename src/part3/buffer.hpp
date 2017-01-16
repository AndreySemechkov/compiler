#ifndef BUFFER_H
#define BUFFER_H

#include "common.hpp"
#include <vector>

extern Buffer buffer;

using namespace std;

class Buffer{

private:
	vector<string> bufferLines;

public:

	Buffer();
	~Buffer();

	//Adds another line of code to the buffer
	void emit(const string& command);

	// Performs the backpathing action from the lines numbers counted from zero
	// input: topatch_list vector of line numbers that need patching
	//        address data to attach
	void Buffer::backpatch(vector<int> lineNums , int address){}

	//prints all buffer lines
	void print();
	// return: buffer size
	unsigned int getSize();
};


#endif
