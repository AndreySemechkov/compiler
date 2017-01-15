#ifndef QUADBUFFER_HPP_
#define QUADBUFFER_HPP_

#include <vector>
#include <list>
#include <string>




class QuadBuffer {
public:
	QuadBuffer();
	~QuadBuffer();

	void printBuffer();
	void emit(const std::string& command);
	void backpatch(std::vector<int> list, int line);
	int nextQuad();
private:
	std::vector<std::string> quadList;
};

#endif /* QUADBUFFER_HPP_ */
