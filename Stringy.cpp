//
// Created by Christian Gould on 8/31/20.
//
# include "Stringy.h"
# include <iostream>
# include <cstring>
# include <sstream>
//# define debugg

using namespace std;
//Destructor
Stringy::~Stringy () {
	delete[] ystring;
}
Stringy::Stringy () {
	//initialize the string at 1 character, being the null-terminator.
	ylength = 1;
	ystring = new char[ylength];
	ystring[ ylength - 1 ] = '\0';
}

Stringy::Stringy (const char *input) // constructor, given a c-string.
{
	// A new copy of a C-string contains exactly the same number of characters in
	// the C-string plus a terminating zero.
	this->ylength = strlen (input) + 1;
	this->ystring = new char[this->ylength];
	// adds each of the elements in input including the null terminating zero.
	for (int i = 0; i < this->ylength; i++) {
		this->ystring[ i ] = input[ i ];
	}
	this->ystring[ylength-1] = '\0';
}


Stringy::Stringy (const Stringy *S) {
	this->ylength = S->length ();
	this->ystring = new char[ylength];
	//make all the values in S part of this string
	for (int i = 0; i < this->ylength; i++) {
		this->ystring[ i ] = S->getString ()[ i ];
	}
}
Stringy::Stringy (const Stringy &s) {
	this->ylength = s.ylength;
	this->ystring = new char[ylength];
	strcpy (this->ystring, s.ystring);
}
Stringy::Stringy (const char *input, int size) {
	this->ylength = size + 1;
	char *temp = new char[ylength];
	// loops only size times.
	for (int i = 0; i < size; i++) {
		temp[ i ] = input[ i ];
	}
	temp[ ylength - 1 ] = '\0';
	this->ystring = temp;
}
bool Stringy::firstThree (Stringy same) {
	return this->ystring[ 0 ] == same.ystring[ 0 ] &&
		   this->ystring[ 1 ] == same.ystring[ 1 ] &&
		   this->ystring[ 2 ] == same.ystring[ 2 ];
}

bool Stringy::wordInsideIt (const Stringy &word) {
	return strstr (this->ystring, word.ystring) != nullptr;
}

/* Referenced Stack overflow for this function:
 * https://stackoverflow.com/questions/5457608/how-to-remove-the-character-at-a-given-index-from-a-string-in-c
 * */
/* Wanted to take a substring out of a larger string
 * and found this article. Ended up not using it in the program. */
void Stringy::findAndDelete (char *toFind) {
	// strstr returns null if needle is not found in haystack. i.e. if toFind is not found in this-> ystring.
	while (strstr (this->ystring, toFind) != nullptr) {
		char *begOfWord = strstr (this->ystring, toFind);
		if (begOfWord == nullptr) return;
		int toFindLen = strlen (toFind);
		int bytesToMove = strlen (begOfWord) - toFindLen;
		memmove (begOfWord, begOfWord + toFindLen,
				 bytesToMove);
		subStrObj (0, this->length () - toFindLen-1);
		this->ylength = strlen (ystring) + 1;
	}
}
char & Stringy::at (int loc) const {
	// this is the location without subracting 1, because of the null terminator.
	if (loc < ylength) {
		return ystring[ loc ];
	} else {
		cout << "location out of bounds in Stringy (at) function" << endl;
		return ystring[ 1 ];
	}
}
bool Stringy::empty () {
	//check to see if the first element is null, and if the length of the cstring is only one.
	return strlen (ystring) < 1;
}

int Stringy::length () const {
	// returns the length with the null terminator
	return (this->ylength);
}

int Stringy::charLength () const {
	// returns the length without the null terminator
	return strlen (this->ystring);
}

Vecty<Stringy *> *Stringy::tokenizeStringy (char delim, const Stringy &stopWords) {
	Vecty<Stringy*> *returnMe = new Vecty<Stringy *> ();
	char temp[10000];
	Stringy *tempStringy;
	stringstream ss (this->getString ());
	while (ss.getline (temp, 9999, delim)) {
		// avoid spaces being put into the word vector.
		if (temp[ 0 ] != ' ') {
			if (strstr (stopWords.ystring, temp)) continue;
			tempStringy = new Stringy (temp);
			returnMe->push_back (tempStringy);
		} else {continue;}
	}
	return returnMe;
}

Vecty<Stringy *> *Stringy::tokenizeStringy (char delim, const Stringy &stopWords, int size) {
	auto *returnMe = new Vecty<Stringy *> ();
	char temp[10000];
	Stringy *tempStringy;
	stringstream ss (this->getString ());
	while (ss.getline (temp, 9999, delim)) {
		// avoid spaces being put into the word vector.
		if (temp[ 0 ] != ' ') {
			if (strstr (stopWords.ystring, temp)) continue;
			tempStringy = new Stringy (temp, size);
			returnMe->push_back (tempStringy);
		} else {continue;}
	}
	return returnMe;
}

void Stringy::subStrObj (int index, int length) {

	int size = length + 1;
	char *temp = new char[size];
	//double for loop, in which it will end at a specified length "i" in the string,
	//and starts at zero for the new temp string.
	for (int i = index, j = 0; j < size; i++, j++) {
		temp[ j ] = ystring[ i ];
	}
	//make sure the end of the c-string is null-terminated.
	if (temp[ size - 1 ] != '\0') {temp[ size - 1 ] = '\0';}
	delete this->ystring;
	this->ystring = temp;
	this->ylength = size;
}

Stringy Stringy::substr (int index, int length) {
	int size = length + 1;
	char *temp = new char[size];
	//double for loop, in which it will end at a specified length "i" in the string,
	//and starts at zero for the new temp string.
	for (int i = index, j = 0; j < size; i++, j++) {
		temp[ j ] = ystring[ i ];
	}
	//make sure the end of the c-string is null-terminated.
	if (temp[ size - 1 ] != '\0') {temp[ size - 1 ] = '\0';}
	return Stringy (temp);
}

// Function to set the string to a new string.
void Stringy::setString (const char *input) {
	// get the new length
	this->ylength = strlen (input) + 1;
	// copy over the new data
	this->ystring = new char[ylength];
	for (int i = 0; i < ylength - 1; i++) {
		this->ystring[ i ] = input[ i ];
	}
	// add the null terminator
	this->ystring[ ylength - 1 ] = '\0';
}

char *Stringy::getString () const {
	return this->ystring;
}

int Stringy::find_Number_Inside (Stringy *toFind) {
	int returnMe = 0;
	//cout << "Stringy toFind: " << *toFind << endl;
	//cout << "char* findMe: " << toFind-> getString () << endl;
	char *findMe = toFind->getString ();
	while (strstr (this->ystring, findMe) != nullptr && (strcmp (strstr (this->ystring, findMe), " ")) != 0 &&
		   strcmp (findMe, "") != 0) {
		int toFindLen = strlen (findMe);
		int bytesToMove = strlen (strstr (this->ystring, findMe)) - toFindLen;
		returnMe++;
		/* this will find where the toFind string is inside of the ystring, then delete the word that was found
		by moving the data over the number of places that the length of toFind is. */
//		cout << "toFind: " << toFind << endl;
//		cout << "Destination: " << strstr(this->ystring,findMe) << endl;
//		cout << "Source: " << strstr(this->ystring, findMe) + strlen(findMe) << endl;
//		cout << "Number of Bytes: " << bytesToMove << endl;
//		cout << "******************" << endl;
		memmove (strstr (this->ystring, findMe), strstr (this->ystring, findMe) + strlen (findMe),
				 bytesToMove);
		subStrObj (0, this->length () - toFindLen);
		this->ylength = strlen (ystring) + 1;
	}
	return returnMe;
}

void Stringy::clean () {
	// for every character in the string
	for (int i = 0; i < ylength - 1; i++) {
		// if the character is not a letter
		if (!(((int) ystring[ i ] > 64 && (int) ystring[ i ] < 90) ||
			  ((int) ystring[ i ] > 96 && (int) ystring[ i ] < 123))) {
			// replace it with a space.
			//cout << (int) ystring[i] << " = " << ystring[i] << endl;
			//cout << ystring[i-1] << ystring[i] << ystring[i+1] << " becomes ";
			ystring[ i ] = ' ';
			//cout << ystring[i-1] << ystring[i] << ystring [i+1] << endl;
		}
	}
}
bool Stringy::findSentiment (Stringy total) {
	// whole function will not execute if Stringy is empty.
	if (total.empty ()) return false;
	bool returnMe = false;
	for (int i = 0; i < total.length (); i++) {
		if (i == total.length () - 1) {return false;}
		else {
			// will only return true if ",p or ",|| find->getString ()[i] == '\t' || find-> getString ()[i] == '|')|| find->getString ()[i] == '\t' || find-> getString ()[i] == '|')
			if (total.getString ()[ i ] == '"' &&
				(total.getString ()[ i + 1 ] == ',' || total.getString ()[ i + 1 ] == '\t' ||
				 total.getString ()[ i + 1 ] == '|') && total.getString ()[ i + 2 ] == 'p') {
				for (int x = i; x < 8; x++) {
					total.getString ()[ i ] = '\0';
				}
				return true;
			} else if (total.getString ()[ i ] == '"' &&
					   (total.getString ()[ i + 1 ] == ',' || total.getString ()[ i + 1 ] == '\t' ||
						total.getString ()[ i + 1 ] == '|') && total.getString ()[ i + 2 ] == 'n') {
				for (int x = i; x < 8; x++) {
					total.getString ()[ i ] = '\0';
				}
				return false;
			}
		}
	}
	return returnMe;
}

ostream &operator<< (ostream &OS, const Stringy &S) {
	OS << S.ystring;
	return OS;
}
istream &operator>> (istream &IS, Stringy &S) {
	// get data into c string
	char tempArr[1000];
	IS >> tempArr;
	// initialize the length of the string
	S.ylength = strlen (tempArr) + 1;
	// copy over the data
	for (int i = 0; i < S.ylength - 1; i++) {
		S.ystring[ i ] = tempArr[ i ];
	}
	// add null terminator
	S.ystring[ S.ylength - 1 ] = '\0';
	return IS;
}
Stringy &Stringy::operator= (const Stringy &S) {
	// if it is self assignment, return this Stringy
	if (this == &S) return *this;
	//set the length the same, then delete this Stringy's string.
	this->ylength = S.ylength;
	delete[] this->ystring;
	this->ystring = new char[this->ylength];
	// copy each of the elements of S to this Stringy.
	for (int i = 0; i < (this->ylength); i++) {
		this->ystring[ i ] = S.ystring[ i ];
	}
	// return this Stringy.
	return *this;
}
bool operator== (const Stringy &S1, const Stringy &S2) {
	return strcmp (S1.getString (), S2.getString ()) == 0;

}
Stringy &operator+ (const Stringy &S1, const Stringy &S2) {
	//add the lengths minus the null terminator, then add one to rep. the new null terminator.
	int length = (S1.ylength - 1) + (S2.ylength - 1) + 1;
	// initialize the array that will be used
	char *array = new char[length];
	// add the first array to the full array, without the null terminator.
	for (int i = 0; i < S1.ylength - 1; i++) {
		array[ i ] = S1.ystring[ i ];
	}
	// add the second array to the full array, without the null terminator.
	for (int i = 0; i < S2.ylength - 1; i++) {
		array[ i + (S1.ylength - 1) ] = S2.ystring[ i ];
	}
	// add the null terminator to the end of the new array.
	array[ length - 1 ] = '\0';
	// create the new Stringy object which will store this new added c-String.
	auto *returnMe = new Stringy (array);
	// delete the temp variable
	delete[] array;
	// return the new Stringy
	return *returnMe;
}
Stringy &operator+ (const Stringy &S1, const char *addition) {
	char *newStringy = nullptr;
	int newlen = strlen (S1.getString ()) + strlen (addition) + 1;
	newStringy = new char[newlen];
	for (int i = 0; i < strlen (S1.getString ()); i++) {
		newStringy[ i ] = S1.getString ()[ i ];
	}
	for (int i = strlen (S1.getString ()), j = 0; i < newlen; i++, j++) {
		newStringy[ i ] = addition[ j ];
	}
	newStringy[ newlen ] = '\0';
	return *new Stringy (newStringy);
}
/* reference:
 * https://www.cplusplus.com/forum/beginner/50062/
 * */
Stringy &operator+ (const Stringy &S1, const int num_Toadd) {
	int counter = 0;
	int number = num_Toadd;
	// counter will be how many digits inside the number.
	while (number) {
		number = number / 10;
		counter++;
	}
	int returnLen = S1.length () + counter;
	char *putMeInStringy = new char[returnLen];
	// put the elements of S1 into the new char
	for (int i = 0; i < S1.length () - 1; i++) {
		putMeInStringy[ i ] = S1.getString ()[ i ];
	}
	char numberToAddToString[counter + 1];
	stringstream strs;
	strs << num_Toadd;
	strs.getline (numberToAddToString, counter + 1);
	for (int i = S1.length () - 1, j = 0; i < returnLen - 1; i++, j++) {
		putMeInStringy[ i ] = numberToAddToString[ j ];
	}
	putMeInStringy[ returnLen - 1 ] = '\0';
	return *new Stringy (putMeInStringy);
}
Stringy &Stringy::operator+= (const Stringy &S1) {
	// make total length equal to the original length minus null plus new stringy minus null plus new null
	int newLength = (this->ylength - 1) + (S1.ylength - 1) + 1;
	int oldlength_WO_Null = this->ylength - 1;

	// save the old string in its original form without null.
	char oldString[ylength];
	for (int i = 0; i < ylength - 1; i++) {
		oldString[ i ] = ystring[ i ];
	}

	// reset the string in this object.
	this->ylength = newLength;
	delete[] this->ystring;
	this->ystring = new char[ylength];

	// add the two strings together into a new Stringy, excluding the null terminator
	for (int i = 0; i < oldlength_WO_Null; i++) {
		this->ystring[ i ] = oldString[ i ];
	}
	// add the second string to the new string, including the null terminator
	for (int i = oldlength_WO_Null, j = 0; i < ylength; i++, j++) {
		this->ystring[ i ] = S1.ystring[ j ];
	}
	// return the Stringy.
	return *this;
}
bool operator< (const Stringy &lhs, const Stringy &rhs) {
	return strcmp (lhs.ystring, rhs.ystring) < 0;
}

void Stringy::toUpper () {
	// for each of the letters in the string
for(int i = 0; i < this-> ylength; i++){
	if ((int)ystring[i] <= 122 && (int)ystring[i] >= 97){
		ystring[i] = (int)ystring[i] - 32;
	}
}
}

Vecty<pair<Stringy, Stringy *>> Stringy::check_For_Goups () {
	Vecty<pair<Stringy,Stringy*>> returnMe;
	char spaceSeparated[80];
	Stringy word_Or_Phrase_to_Index;
	Stringy* group_Name = nullptr;
	stringstream ss(this->ystring);
	// this will get each of the pieces space-separated
	while(ss.getline(spaceSeparated, 79, ' ')){
#ifdef debugg
		cout << "Top of while loop, spaceSeparated: " << spaceSeparated << endl;
#endif
		// if the first word is a phrase
		if (spaceSeparated[0] == '[') {
			word_Or_Phrase_to_Index = this->getPhrase(ss, spaceSeparated);
			//cout << "The word or phrase this round is: " << word_Or_Phrase_to_Index << endl;
		}
		// if the first word is not a phrase
		else if (spaceSeparated[0] != '['){
			word_Or_Phrase_to_Index = this->getWord(spaceSeparated);
		}
		// check if there is a group
		if(ss.peek() == '('){
			ss.getline(spaceSeparated, 79, ' ');
		}
		char* parentheses = strstr(spaceSeparated, "(");
		// if there is a group
		if (parentheses != nullptr){
#ifdef debugg
			cout << "There is a group, parentheses: " << parentheses << "expected '(' "<< endl;
#endif
			// if the group is a phrase
			//cout << "parentheses of 1: " << parentheses[1] << endl;
			if (parentheses[1] == '['){
				parentheses = parentheses + 1;
				group_Name = new Stringy(this->getPhrase (ss,parentheses));
				ss.get();
				if(ss.peek() == ' ') ss.get();
			}
			// if the group is a word
			else {
				// start one after the parenthetical, at the word itself
				char buffer[79];
				stringstream tempStream(parentheses+1);
				tempStream.getline(buffer,78,')');
				//cout << "buffer ends up being: " << buffer << endl;
				group_Name = new Stringy(buffer);
			}
		}
		// if there is no group
		else {
			group_Name = nullptr;
		}
		// push back the pair of the word/phrase and the group name into the return variable
		returnMe.push_back (pair<Stringy, Stringy*>(word_Or_Phrase_to_Index,group_Name));
		memset(spaceSeparated, '\0', sizeof(spaceSeparated));
	} // end while getline
	return returnMe;
}

Stringy Stringy :: getPhrase(stringstream& ss, char spaceSeparated[]){
	Stringy word_Or_Phrase_to_Index = "";
	word_Or_Phrase_to_Index = word_Or_Phrase_to_Index + (spaceSeparated+1);
	word_Or_Phrase_to_Index = word_Or_Phrase_to_Index + " ";
	ss.getline(spaceSeparated, 79, ']');
#ifdef debugg
	cout << "Got: " << spaceSeparated << endl;
#endif
	word_Or_Phrase_to_Index = word_Or_Phrase_to_Index + spaceSeparated;
	memset(spaceSeparated, '\0', sizeof(spaceSeparated));
#ifdef debugg
	cout << "returning: " << word_Or_Phrase_to_Index << endl;
#endif
	if(ss.peek() == ' ')ss.get();
	return word_Or_Phrase_to_Index;
}
Stringy Stringy :: getWord(char spaceSeparated[]){
	char* foundParenthetical = strstr(spaceSeparated, "(");
	// if there is no group, just return the stringy of the given char array
	if(foundParenthetical == nullptr){
		return Stringy(spaceSeparated);
	// if there is a group, ignore the group using a stringstream
	} else {
		stringstream tempStream(spaceSeparated);
		char buffer[79];
		tempStream.getline(buffer, 78, '(');
		return Stringy(buffer);
	}
}

Stringy Stringy::get_Pg_Nmbr () {
	char returnChar[100];
	stringstream ss(this->ystring);
	// get rid of the beginning < character
	ss.get();
	// pull the number
	ss.getline(returnChar,100, '>');
	return Stringy(returnChar);
}
void Stringy::remPunct () {
int counter = this->ylength - 2;
while (counter > 0 && !isNtPunct(ystring[counter]) ){
	this->subStrObj (0,counter);
	counter--;
}
}
bool Stringy:: isNtPunct(char isIt){
	int ascii = (int) isIt;
	return ((ascii > 64 && ascii < 91) || (ascii == 40) || (ascii == 41) || (ascii == 91) || (ascii == 93));
}

bool operator<= (const Stringy &lhs, const Stringy& rhs) {
	return ((lhs < rhs) || lhs == rhs);
}

int Stringy::toInt () {
	return stoi(this->ystring);
}

bool operator!= (const Stringy &S1, const Stringy& S2) {
	return strcmp(S1.ystring, S2.ystring) != 0;
}

Stringy::Stringy (const int& input) {
	stringstream strm;
	strm << input;
	char num[50];
	strm.getline(num,49);
	ylength = strlen (num) + 1;
	this-> ystring = new char[ylength];
	for(int i = 0; i < strlen(num); i++){
		this->ystring[i] = num[i];
	}
	this-> ystring[ylength -1] = '\0';
}
