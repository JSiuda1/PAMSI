#include "../inc/FifoList.hh"

#include <string>

int main(){
	Queue<std::string> queue;
	
	std::string test = "Hello world!";
	queue.push(test);
	test = "Second string";
	queue.push(test);
	test = "Third string";
	queue.push(test);
	queue.print();
	
	for (int i = 0; i < 4; ++i) {
		try {
			std::cout << "Pop: " << queue.pop() << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
	
	//queue.print();

  return 0;
}