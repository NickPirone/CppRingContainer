#include "../ring/ring.hpp"
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

template<typename T> void fillRing(T& ring, int count) {
	for (int i = 0; i < count; i++) {
		ring.push(i);
	}
}

template<typename T> int testIterator(T& ring) {
	int successes = 0;
	for (auto iter = ring.begin(); iter != ring.end(); iter++) {
		auto val = *iter;
		
		successes++;
		const int MAX_LOOPS = 100;
		if (successes > MAX_LOOPS) assert(false); // throw error.
	}
	return successes;
}

void testPartiallyFilled() {
	np::ring<int,5> fiveRing;
	fillRing(fiveRing, 3);
	assert(fiveRing.at(0) == 0);
	assert(fiveRing.at(1) == 1);
	assert(fiveRing.at(2) == 2);
	int iterLoops = testIterator(fiveRing);
	assert(iterLoops == 3);
}

void testFullyFilled() {
	np::ring<int,5> fiveRing;
	fillRing(fiveRing, 5);
	assert(fiveRing.at(0) == 0);
	assert(fiveRing.at(1) == 1);
	assert(fiveRing.at(2) == 2);
	assert(fiveRing.at(3) == 3);
	assert(fiveRing.at(4) == 4);
	int iterLoops = testIterator(fiveRing);
	assert(iterLoops == 5);
}

void testOverFilled() {
	np::ring<int,5> fiveRing;
	fillRing(fiveRing, 6);
	assert(fiveRing.at(0) == 1);
	assert(fiveRing.at(1) == 2);
	assert(fiveRing.at(2) == 3);
	assert(fiveRing.at(3) == 4);
	assert(fiveRing.at(4) == 5);
	int iterLoops = testIterator(fiveRing);
	assert(iterLoops == 5);
}

int main() {
	testConstructEmpty();
	testBadParameters();
	testPartiallyFilled();
	testFullyFilled();
	testOverFilled();
	std::cout << "Tests run succesfully." << std::endl;
	return 0;
}