#include "../ring/ring.hpp"
#include <iostream>
#include <cassert>
#include <algorithm>

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

template<typename T> int testIterator(const T& ring) {
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

void testMoveCtor() {
	np::ring<int, 5> fiveRing;
	fillRing(fiveRing, 5);
	int countIterations = testIterator(std::move(fiveRing));
	assert(countIterations == 5);
}

void testCopyCtor() {
	np::ring<int,5> fiveRing;
	fillRing(fiveRing, 5);
	np::ring<int,5> otherFiveRing = fiveRing;
	assert(otherFiveRing.at(0) == 0);
	assert(otherFiveRing.at(1) == 1);
	assert(otherFiveRing.at(2) == 2);
	assert(otherFiveRing.at(3) == 3);
	assert(otherFiveRing.at(4) == 4);
}

void testAssignment() {
	np::ring<int,5> fiveRing;
	fillRing(fiveRing, 5);
	np::ring<int,5> otherFiveRing;
	otherFiveRing = fiveRing;
	assert(otherFiveRing.at(0) == 0);
	assert(otherFiveRing.at(1) == 1);
	assert(otherFiveRing.at(2) == 2);
	assert(otherFiveRing.at(3) == 3);
	assert(otherFiveRing.at(4) == 4);
}

void testSorting() {
	np::ring<int,5> fiveRing;
	fiveRing.push(5);
	fiveRing.push(1);
	fiveRing.push(3);
	fiveRing.push(2);
	fiveRing.push(4);
	std::sort(fiveRing.begin(), fiveRing.end());
	assert(fiveRing.at(0) == 1);
	assert(fiveRing.at(1) == 2);
	assert(fiveRing.at(2) == 3);
	assert(fiveRing.at(3) == 4);
	assert(fiveRing.at(4) == 5);
}

int main() {
	testBadParameters();
	testConstructEmpty();
	std::cout << "Empty ring OK." << std::endl;
	testPartiallyFilled();
	std::cout << "Partially-filled ring OK." << std::endl;
	testFullyFilled();
	std::cout << "Fully-filled ring OK." << std::endl;
	testOverFilled();
	std::cout << "Over-filled ring OK." << std::endl;
	testCopyCtor();
	std::cout << "Copy Ctor OK." << std::endl;
	testMoveCtor();
	std::cout << "Move Ctor OK." << std::endl;
	testAssignment();
	std::cout << "Assignment OK." << std::endl;
	testSorting();
	std::cout << "Sorting OK." << std::endl;
	std::cout << std::endl << "------ALL Tests run succesfully :) :) :)------" << std::endl;
	return 0;
}