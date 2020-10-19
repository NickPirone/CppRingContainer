#ifndef RING_H
#define RING_H

#include <memory>
#include <iostream>

namespace np {

template<class T, size_t S, class Allocator = std::allocator<T> > class ring {
public:
	
//member types:
	using value_type = T;
	using allocator_type = Allocator;
	using pointer = typename std::allocator_traits<Allocator>::pointer;
	using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
	using reference = value_type&;
	using const_reference = const value_type&;
	using size_type = size_t;
	using difference_type = std::ptrdiff_t;

	//ring::iterator class:
	class iterator {
	public:
		iterator(ring& data, size_type index) : mData(data), mIndex(index) {}
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;
		
		iterator& operator++() {
			mIndex++;
			return *this;
		}
		iterator& operator++(int val) {
			mIndex++;
			return *this;
		}
		iterator& operator--() {
			mIndex--;
			return *this;
		}
		iterator& operator+=(size_type val) {
			mIndex += val;
			return *this;
		}
		iterator& operator-=(size_type val) {
			mIndex -= val;
			return *this;
		}
		iterator operator+(size_type val) const {
			return iterator(mData, mIndex + val);
		}
		iterator operator-(size_type val) const {
			return iterator(mData, mIndex - val);
		}
		reference operator*() {
			return mData.at(mIndex);
		}
		reference operator->() {
			return mData.at(mIndex);
		}
		bool operator==(const iterator& rhs) const {
			return &(mData) == &(rhs.mData) && mIndex == rhs.mIndex;
		}
		bool operator!=(const iterator& rhs) const {
			return !operator==(rhs);
		}
		
	private:
		ring& mData;
		size_type mIndex = 0;
	};

	using const_iterator = const iterator;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
	using ALLOCATOR_TRAITS = std::allocator_traits<Allocator>;
	static constexpr size_t MEMORY_SIZE = sizeof(T) * S;
public:

//constructors:
	ring(const allocator_type& allocator = allocator_type()) : mAllocator(allocator) {
		mElements = ALLOCATOR_TRAITS::allocate(mAllocator, MEMORY_SIZE);
	}
	
//destructor:
	~ring() {
		ALLOCATOR_TRAITS::deallocate(mAllocator, mElements, MEMORY_SIZE);
	}
	
//iterators

	iterator begin() {
		return iterator(*this, 0);
	}
	const_iterator begin() const {
		return const_iterator(*this, 0);
	}
	iterator end() {
		return iterator(*this, mConstructedSize);
	}
	const_iterator end() const {
		return const_iterator(*this, mConstructedSize);
	}
	/*
	reverse_iterator rbegin() {
	}
	const_reverse_iterator rbegin() const {
	}
	reverse_iterator rend() {
	}
	const_reverse_iterator rend() const {
	}
	*/
	
//operators:
	ring& operator=(const ring& other) = default;
	ring& operator=(ring&& other) = default;
	
//element access:
	reference at(size_type index) {
		return mElements[getRelativeIndexFromClientIndex(index)];
	}
	const_reference at(size_type index) const {
		return mElements[getRelativeIndexFromClientIndex(index)];
	}
	
//capacity:
	size_type size() const {
		return mConstructedSize;
	}	
	bool empty() const {
		return mConstructedSize == 0;
	}

//modifiers:
	void push(const T& value) {
		if (full()) {
			ALLOCATOR_TRAITS::destroy(mAllocator, getPointerToElementAtMemoryIndex(mFirstElementIndex));
		} else {
			mConstructedSize++;
		}
		ALLOCATOR_TRAITS::construct(mAllocator, getPointerToElementAtMemoryIndex(mFirstElementIndex), value);
		incrementIndex();
	}
	void push(T&& value) {
		if (full()) {
			ALLOCATOR_TRAITS::destroy(mAllocator, getPointerToElementAtMemoryIndex(mFirstElementIndex));
		} else {
			mConstructedSize++;
		}
		ALLOCATOR_TRAITS::construct(mAllocator, getPointerToElementAtMemoryIndex(mFirstElementIndex), value);
		incrementIndex();
	}
	void clear() {
		for (size_type i; i < mConstructedSize; i++) {
			ALLOCATOR_TRAITS::destroy(mAllocator, getPointerToElementAtMemoryIndex(i));
		}
		mConstructedSize = 0;
		mFirstElementIndex = 0;
	}
	
private:
	allocator_type mAllocator;
	size_type mFirstElementIndex = 0;
	size_type mConstructedSize = 0;
	T* mElements;
	
	constexpr T* getPointerToElementAtMemoryIndex(size_type memoryIndex) {
		return mElements + memoryIndex;
	}
	constexpr bool full() const {
		return mConstructedSize == S;
	}
	void incrementIndex() {
		mFirstElementIndex++;
		if (mFirstElementIndex == S) {
			mFirstElementIndex = 0;
		}
	}
	size_type getRelativeIndexFromClientIndex(size_type clientIndex) const {
		if (clientIndex >= mConstructedSize) {
			return 0;
		}
/*								[0][1][2][3][4]
*                                      *        -last element index;         //if index = 4, we want [2]
*                                         *     -first element inex;         //if index = 1, we want [4]
*/
		size_type relativeIndex = getFirstElementIndex() + clientIndex; // 7 or 4.
		if (relativeIndex >= S) relativeIndex -= S; //2 or 4.  good.
		//std::cout << "client Index = " << clientIndex << ", relativeIndex= " << relativeIndex << std::endl;
		return relativeIndex;
	}

	size_type getFirstElementIndex() const {
		if (mConstructedSize == S) {
			return (mFirstElementIndex == S - 1) ? 0 : mFirstElementIndex;
		} else {
			return 0;
		}
	}
	
};//template class ring
	
//partial specialization for S == 0:  do not allow to compile:
template<class T, class Allocator> class ring<T, 0, Allocator> {
	ring() = delete;
};

}//namespace np
	
#endif