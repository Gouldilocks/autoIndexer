//
// Created by Christian Gould on 9/24/20.
//
/* references
 * https://stackoverflow.com/questions/21569483/c-overloading-dereference-operators
 * used to find out how to change dereference operators
 *
 * https://users.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html
 * used to find how to make a basic iterator class
 * */
#ifndef INC_20F_AUTO_IDX_LINKYLISTITER_H
#define INC_20F_AUTO_IDX_LINKYLISTITER_H
using namespace std;
#include "Nody.h"
template <class t>
class LinkyIter{
private:
	Nody<t>* payload;
public:
	LinkyIter(Nody<t>* newLoad){
		this-> payload = newLoad;
	}

	LinkyIter& operator++(){
		payload = payload->getNext();
	}
	LinkyIter& operator--(){
		payload = payload->getPrev();
	}
	LinkyIter& operator=(const LinkyIter& rhs){
		this-> payload = rhs.payload;
	}
	t operator->(){
		return payload->getPayload();
	}
	t operator*(){
		// if the node is end() payload will be nullptr
		if (this-> payload == nullptr) return t();
		// otherwise return the payload
		return payload->getPayload();
	}
	bool operator ==(const LinkyIter<t> rhs){
		return payload == rhs.payload;
	}
	bool operator !=(const LinkyIter<t> rhs){
		return payload != rhs.payload;
	}
};
#endif //INC_20F_AUTO_IDX_LINKYLISTITER_H
