#include "QuadBuffer.hpp"
#include "Common.hpp"
#include <iostream>

using namespace std;

QuadBuffer::QuadBuffer() {
}

QuadBuffer::~QuadBuffer() {
}

void QuadBuffer::emit(const string& command) {
	quadList.push_back(command);
}

/////////////////////////////////////////////////////////////////////////
// returns the next free line number in the QuadBuffer
/////////////////////////////////////////////////////////////////////////
int QuadBuffer::nextQuad() {
	return quadList.size() + 1;
}

/////////////////////////////////////////////////////////////////////////
// backpatch the given list
// parameters:
// - a list containing quad lines which has an unfinished goto (UJUMP)
//	 command.
// - the destination address (line) to append to each of those quads
/////////////////////////////////////////////////////////////////////////
void QuadBuffer::backpatch(std::vector<int> list, int line) {
	for (unsigned int i = 0; i < list.size(); i++) {
		quadList[list[i]-1] += to_string(line);
		// -1 is because nextQuad does not return current ~
	}
}
void QuadBuffer::printBuffer() {
	for (unsigned int i = 0; i < quadList.size(); i++) {
		cout << quadList[i] << endl;
	}
}
