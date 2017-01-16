/*
 * buffer functions for code generation
 *
 *
 */

#include "buffer.hpp"

Buffer::Buffer(){
	bufferLines = new vector<string>;
}

Buffer::~Buffer(){
	delete bufferLines;
}

//Adds another line of code to the buffer
void Buffer::emit(const string& command){
    bufferLines.push_back(command);
}
// Performs the backpatching action from the lines numbers counted from zero
// input: topatch_list vector of line numbers that need patching
void Buffer::backpatch(vector<int> lineNums , int address){
	string addressString = to_string(address);
	for (auto num : lineNums) {
        bufferLines[num] += addressString;
	}
}

// return: buffer size
unsigned int Buffer::getSize(){
	return bufferLines.size();
}

//prints all buffer lines
void Buffer::print(){
	for (auto line : bufferLines) {
	       cout << line << endl;
	}
}




