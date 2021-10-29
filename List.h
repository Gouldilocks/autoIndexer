//
// Created by Christian Gould on 9/15/20.
//

#ifndef INC_20F_AUTO_IDX_LIST_H
#define INC_20F_AUTO_IDX_LIST_H
#define debug false
#include <iostream>
using namespace std;
template <class t>
class List {
public:
	/* destructor */
	~List() = default;

	/* constructors */
	List(){
		this-> sorted = false;
	}
	List(const List& l){
		this-> sorted = l.sorted;
	}

	/* functions */
	virtual void push_back(const t&) = 0;
	virtual void remove(int rem) = 0;
	virtual int getSize() const = 0;
	virtual void insertionSort() = 0;
	// removes duplicates from a sorted List
	void remDuplicates(){
		if (this->getSize() == 0 || this->getSize () == 1) return;
		for(int i = 1; i < this->getSize (); i++){
			if(this->operator[] (i) == this->operator[] (i-1)){
				this->remove (i);
				i--;
			}
		}
		sorted = true;
	}
	// returns the index of the searched for term. Works unsorted
	// returns -1 if not found
	int search(const t& findMe){
		for(int i = 0; i < this->getSize(); i++){
			if (findMe == this->operator[] (i)) return i;
		}
		return -1;
	}
	// searches through a sorted array, returning the index of found element
	// returns -1 if not found, or array not sorted
	// i represents the beginning of the search, j the end.
	int binarySearch(const t& findMe, int i = 0, int j = 1) {
		// make the last element in the array
		if (debug)cout << "object is: " << findMe << endl;
		int begin = i;
		if (debug)cout << "begin is: " << i << endl;
		if (debug)cout << "end is: " << j << endl;
		if (sorted) {
			// switch the number of elements in the array
				switch (j - i + 1) {
					// if the size is 0 i.e. element not found
					case 0: {
						if (debug) cout << "no elements in List when j: " << j << " i: " << i << endl;
					return -1;
					};
						// if the size is 1
					case 1: {
						if (debug) cout << "one element in List when j: " << j << " i: " << i << endl;
						return i;
					};
						// if the size is 2
					case 2: {
						if (debug)cout << "two elements in List when j: " << j << " i: " << i << endl;
						if (debug)cout << "returns" << (this->operator[](0) == findMe) << endl;
						return (this->operator[] (i) == findMe) ? i : j;
					};
						// if the size is >2
					default: {
						int middle = i + ((j-i) / 2);
						if (debug)cout << "middle is: " << middle << " when j: " << j << " i: " << i << endl;
						// while we have not found the element
							// if find me is the same as the middle
							if (findMe == this->operator[] (middle)) {
								if (debug)cout << "middle is equal when j: " << j << " i: " << i << endl;
								return middle;
							}
								// if find me is less than the middle
							else if (findMe < this->operator[] (middle)) {
								if (debug)cout << "recursion" << endl;
								return binarySearch (findMe, i, middle-1);
							}
								// if find me is greater than the middle
							else {
								if (debug)cout << "recursion" << endl;
								return binarySearch (findMe, middle+1, j);
							}
					};
				}
		}
		else return -1;
	}

	/* operators */
	List& operator= (const List& rhs) = default;
	virtual t operator[] (int ret)const  = 0;
private:
	bool sorted;
};
#endif //INC_20F_AUTO_IDX_LIST_H
