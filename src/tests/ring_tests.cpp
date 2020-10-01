#include "ring.hpp"
#include <iostream>
#include <cassert>

void testConstructEmpty() {
	np::ring<int,5 > fiveRing;
	assert(fiveRing.empty());
	assert(fiveRing.size() == 0);
}

void testBadParameters() {
#ifdef COMPILE_TIME_TESTS
	np::ring<int, 0> zeroRing;
#endif
}

int main() {
	testConstructEmpty();
	testBadParameters();

/*
	np::ring<int, 5> myFiveRing;
	myFiveRing.push(1);
	myFiveRing.push(2);
	myFiveRing.push(3);
	std::cout << "-----" << std::endl;	
	for (int i = 0; i < 3; i++) {
		std::cout << "i= " << i << ", value= " << myFiveRing.at(i) << std::endl;
	}
	std::cout << "-----" << std::endl;
	myFiveRing.push(4);
	myFiveRing.push(5);pir0wn4ge
	std::cout << "-----" << std::endl;
	for (int i = 0; i < 5; i++) {
		std::cout << "i= " << i << ", value= " << myFiveRing.at(i) << std::endl;
	}
	std::cout << "-----" << std::endl;
	myFiveRing.push(6);
	std::cout << "-----" << std::endl;
	for (int i = 0; i < 5; i++) {
		std::cout << "i= " << i << ", value= " << myFiveRing.at(i) << std::endl;
	}
	std::cout << "-----" << std::endl;
*/
	std::cout << "Tests run succesfully." << std::endl;
	return 0;
}