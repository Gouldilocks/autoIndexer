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
#ifndef INC_20F_AUTO_IDX_VECTYITER_H
#define INC_20F_AUTO_IDX_VECTYITER_H
using namespace std;
template <class t>
class vectyIter{
private:
	t* payload;
public:
	vectyIter(t* newLoad){
		this-> payload = newLoad;
	}
	vectyIter& operator++(){
	++payload;
	}
	vectyIter& operator--(){
	--payload;
	}
	vectyIter& operator=(const vectyIter& rhs){
		this-> payload = rhs.payload;
	}
	t operator->(){
		return *payload;
	}
	t operator*(){
		return *payload;
	}
	bool operator ==(const vectyIter<t> rhs){
		return payload == rhs.payload;
	}
	bool operator !=(const vectyIter<t> rhs){
		return payload != rhs.payload;
	}
};
#endif //INC_20F_AUTO_IDX_VECTYITER_H
