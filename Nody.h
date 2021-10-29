//
// Created by Christian Gould on 9/15/20.
//

#ifndef INC_20F_AUTO_IDX_NODY_H
#define INC_20F_AUTO_IDX_NODY_H
using namespace std;

#include <iostream>

template<class t>
class Nody {
private:
	t *payload;
	Nody *next;
	Nody *prev;
public:
	// default constructor sets elemts to nullptr
	Nody () {
		this->payload = nullptr;
		this->next = nullptr;
		this->prev = nullptr;
	}

	// full constructor sets the payload and next pointer
	Nody (t payload, Nody next, Nody* prev) {
		this->payload = new t (payload);
		this->next = new Nody (next);
		this->prev = prev;
	}

	// copy constructor given reference
	Nody (const Nody &newGuy) {
		this->payload = newGuy.payload;
		this->next = newGuy.next;
		this->prev = newGuy.prev;
	}

	// copy constructor given pointer
	Nody (Nody *newGuy) {
		this->payload = new t(newGuy->payload);
		this->next = newGuy->next;
		this->prev = newGuy->prev;
	}

	// copy assignment operator
	Nody &operator= (const Nody &newGuy) {
		if (*this == newGuy) {return *this;}
		else {
			this->payload = new t (*newGuy.getPayload ());
			this->next = newGuy.next;
			this-> prev = newGuy.prev;
			return *this;
		}
	}

	// constructor given only payload. Sets next to null
	Nody (t payload) {
		t *newPayload = new t (payload);
		this->payload = newPayload;
		this->next = nullptr;
		this->prev = nullptr;
	}

	// destructor
	~Nody () {
		if(this->payload != nullptr) delete this->payload;
		if(this->next != nullptr) delete this->next;
	}

	// returns a pointer to the payload
	t getPayload () {
		return *this->payload;
	}

	t* getPayloadptr(){
		return this->payload;
	}
	// sets the payload of this
	void setPayload (t newPayload) {
		this->payload = new t (newPayload);
	}

	// returns a pointer to next list element
	Nody *getNext () {
		return this->next;
	}

	// sets the next in the list
	void setNext (Nody *nextOne) {
		this->next = nextOne;
	}

	// returns a pointer to the previous element
	Nody* getPrev() {
		return this->prev;
	}

	void setPrev (Nody* prevOne){
		this-> prev = prevOne;
	}

};
#endif //INC_20F_AUTO_IDX_NODY_H
