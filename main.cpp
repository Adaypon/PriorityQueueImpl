#include <iostream>
#include <vector>
#include "priority_queue.hpp"

int main() {
	priority_queue<int, std::vector<int>> q;
	q.push(45);
	q.push(11);
	q.push(12);
	q.push(7);
	q.push(100);
	
	std::cout << "Top = " << q.top() << std::endl; // == 100
	std::cout << "Popped: " << q.pop() << std::endl; // == 100
	
	std::cout << "Is queue empty? " << std::boolalpha << q.empty() << std::endl;
	
	while(!q.empty())
		std::cout << "Popped: " << q.pop() << std::endl;

	return 0;
}