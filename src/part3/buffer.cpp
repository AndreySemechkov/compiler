/*
 * buffer functions for code generation
 *
 *
 */

#include "buffer.h"

Buffer::Buffer(){	
}

Buffer::~Buffer(){
}

//Adds another line of code to the buffer
void Buffer::emit(const string& command){
    bufferLines.push_back(command);
}
// Performs the backpatching action from the lines numbers counted from zero
// input: topatch_list vector of line numbers that need patching
void Buffer::backpatch(set<int> lineNums , int address){
	string addressString = to_string(address);
	for (auto num : lineNums) {
        bufferLines[num] += addressString;
	}
}

// return: buffer size
int Buffer::nextQuad(){
	return bufferLines.size();
}

//prints all buffer lines
void Buffer::print(){
	for (auto line : bufferLines) {
	       cout << line << endl;
	}
}




