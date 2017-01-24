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
        bufferLines[num-1] += addressString;
	}
}

// return: buffer size
int Buffer::nextQuad(){
	return bufferLines.size() + 1 ;
}

//prints all buffer lines
void Buffer::print(){
	for (auto line : bufferLines) {
	       //cout << line << endl;
	}
}

// print out the buffer into a .riksi file
	void Buffer::printRiski(string filename)
	{
      string filenameOut = filename.substr(0,filename.length()-4) + ".rsk";
	  //cout << filenameOut << endl;
      ofstream myfile;
      myfile.open(filenameOut.c_str());
      for (auto line : this->bufferLines) {
    	  myfile << line << endl;
	   }
      myfile.close();
	}

	void Buffer::insertHeader(string line){
        vector<string>::iterator it = this->bufferLines.begin();
		this->bufferLines.insert(it,line);
	}






