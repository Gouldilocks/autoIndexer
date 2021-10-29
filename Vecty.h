//
// Created by Christian Gould on 9/15/20.
//
/*
 * Insertion sort adapted from professor Gabrielson's lecture materials
 */
#ifndef INC_20F_AUTO_IDX_VECTY_H
#define INC_20F_AUTO_IDX_VECTY_H
#define debug true
#include "List.h"
#include "VectyIter.h"
#include <iostream>
using namespace std;

template <class t>
class Vecty : public List<t> {
public:
	/* iterator */
// returns the first element in the yvector
vectyIter<t> begin() {
	return vectyIter<t>(this-> yvector);
}
// returns the theoretical next element after the last
vectyIter<t> end(){
	return vectyIter<t>(this->yvector + ysize);
}

	/* constructors */
	// default constructor
	Vecty()  : List <t>(){
		ysize = 0;
		this-> yvector = nullptr;
	}
	// copy constructor
	Vecty(const Vecty& v) : List <t>(){
		this-> ysize = v.ysize;
		this-> yvector = new t[ysize];
		for(int i = 0; i < ysize; i++){
			this-> yvector[i] = v.yvector[i];
		}
	}
	// constructor given one element t
	Vecty(const t& addMe) : List <t>(){
		this-> yvector = new t[1];
		this->yvector[1] = addMe;
		this->ysize = 1;
	}
	/* destructor */
	~Vecty () {
		delete []this-> yvector;
	}
	/* functions */
	void push_back(const t& pushMe){
		// make temp variable, and copy the old elements into it
		t old[ysize];
		for(int i = 0; i < ysize; i++){
			old[i] = yvector[i];
		}
		++this-> ysize;
		delete []this-> yvector;
		this-> yvector = new t[ysize];
		// copy each of the old elements into the new resized array
		for(int i = 0; i < ysize-1; i++){
			this->yvector[i] = old[i];
		}
		// add the new element
		this->yvector[ysize-1] = pushMe;
	}
	void remove(int remMe) {
		// copy the old elements into this array
		t old[ysize];
		for(int i = 0; i < ysize; i++){
			old[i] = this-> yvector[i];
		}
		--this->ysize;
		delete []this->yvector;
		this->yvector = new t[ysize];
		// will change i, and skip the index that needs to be put in.
		// ex.) if remMe == 2, then it will skip adding yvector[i].
		for(int i = 0; i < ysize; i++){
			if(i == remMe) break;
			this-> yvector[i] = old[i];
		}
		for (int i = remMe; i < ysize; i++){
			this-> yvector[i] = old[i+1];
		}
	}
	int getSize() const{
		return this-> ysize;
	}
	// function has incorrect input handling: If findMe exceeds the array, then it will return final element
	t at(int findMe){
		if (findMe >= this-> ysize){
#ifdef DEBUG_MODE
			{cout << "exceeded bounds of vector" << endl;}
#endif
			return this-> yvector[ysize-1];
		} else {
			return this-> yvector[findMe];
		}
	}
	/* operators */
	Vecty& operator=(const Vecty& rhs){
		if(this != &rhs) {
			delete[] yvector;
			this->ysize = rhs.ysize;
			this->yvector = new t[ysize];
			for (int i = 0; i < this->ysize; i++) {
				this->yvector[ i ] = rhs.yvector[ i ];
			}
			return *this;
		}
	}
	// returns an element without data protection
	t operator[] (const int ret)const {
	return yvector[ret];
	}
	/* Operators */
	bool operator==(const Vecty<t>& rhs) const {
		// if they are the same size, execute comparison
		if(rhs.getSize() == this->getSize ()){
			// loop through all the elements
			for(int i = 0; i < getSize(); i++){
				// if the elements are not the same, return false
				if(this->operator[] (i) != rhs[i]) return false;
			}
			return true;
			// if they are not the same size, return false
		} else return false;
	}
	void insertionSort(){
		 	int thisSizey = this->getSize ();
		 	// this integer is a counter for each element in the array
			int i;
			// this integer is a counter for the index of the current element being sorted
			int j;
			// temporary variable to swap
			t temp;

			for (i = 1; i < thisSizey; ++i) {
				j = i;
				// Insert yvector[i] into sorted part
				// stopping once yvector[i] in correct position
				while (j > 0 && yvector[j] < yvector[j - 1]) {

					// switch yvector [j] and yvector[j-1]
					temp = yvector[j];
					yvector[j] = yvector[j - 1];
					yvector[j - 1] = temp;
					--j;
				}
			}
		}
private:
	int ysize;
	t* yvector;
};
#endif //INC_20F_AUTO_IDX_VECTY_H
