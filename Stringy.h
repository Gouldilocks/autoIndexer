//
// Created by Christian Gould on 8/31/20.
//

#ifndef S20_PA01_SENTIMENTANALYSIS_STRINGY_H
#define S20_PA01_SENTIMENTANALYSIS_STRINGY_H
#include <cstring>
#include <fstream>
#include "Vecty.h"
using namespace std;
class Stringy
{

public:
	/* ***** Destructor ***** */
	~Stringy();


	/* ***** Constructors ***** */
	//default sets string to NULL
	Stringy();
	//Takes in a string and creates an object
	Stringy(const char* input);
	// pointer constructor
	Stringy(const Stringy *S);
	// copy constructor
	Stringy(const Stringy &s);
	// smaller stringy constructor
	Stringy(const char* input, int size);
	// stringy constructor for integers
	Stringy(const int& input);


	/* ***** Functions ***** */
	// function returns a bool of whether the first 3 letters are the same or not.
	bool firstThree(Stringy same);
	// function will find if a given review total has a word inside.
	bool wordInsideIt (const Stringy& wordInside);
	// will find and remove the char* that is passed from the ystring.
	void findAndDelete(char* toFind);
	// returns a chracter at specified loc (includes 0)
	char & at(int loc) const;
	// if string is empty returns true else it returns false
	bool empty();
	//displays length of string including null
	int length() const;
	// returns the length of the string, excluding null-terminator
	int charLength() const;
	// takes the next word in the String, then returns a vector of each word according to the delimeter
	Vecty<Stringy*>* tokenizeStringy(char delim, const Stringy& stopWords);
	// overloaded tokenize, uses sized string constructor.
	Vecty<Stringy*>* tokenizeStringy(char delim, const Stringy& stopWords, int size);
	// Modifies the current object to be a substring.
	void subStrObj(int index, int length);
	// returns a substring of the object
	Stringy substr(int index, int length);
	// sets the string
	void setString (const char* input); // $$$
	// returns the char* of this-> Stringy
	char * getString () const;
	// sets the ylength of this Stringy
	int find_Number_Inside(Stringy* toFind);
	// cleans the string up according to the blacklist.
	void clean();
	// finds the sentiment and deletes it.
	bool findSentiment(Stringy total);
	/* returns a vector of pairs with this organization:
	 * first element: the word / phrase
	 * second element: the name of the group. If no group, second == nullptr
	 * */
	Vecty<pair<Stringy,Stringy*>> check_For_Goups();
	// sets the letters in the string to upper case
	void toUpper();
	// gets a phrase from the given stringstream until it finds a ]
	Stringy getPhrase (stringstream& ss, char *spaceSeparated);
	// gets a word from the given char array
	Stringy getWord (char *spaceSeparated);
	// gets the page number
	Stringy get_Pg_Nmbr();
	// removes the punctuation except for [] and ()
	void remPunct();
	// checks if the string is a letter or has [] or ()
	bool isNtPunct(char isIt);
	// changes a Stringy to an integer
	int toInt();

	/* ***** Overloaded Operators ***** */
	// outputs the ystring to the output stream.
	friend ostream& operator << (ostream & OS,const Stringy &S);
	// adds the input from IS to this Stringy
	friend istream& operator >> (istream & IS,Stringy &S);
	// assigns ystring and ylength from given Stringy.
	Stringy& operator = (const Stringy& S);
	// compares the ystrings, and NOT ylength.
	friend  bool operator ==(const Stringy& S1, const Stringy & S2);
	// adds two Stringys together and returns result. Does not modify parameters.
	friend Stringy & operator + (const Stringy& S1, const Stringy & S2);
	// adds Stringy to a char. Does not modify parameters.
	friend Stringy & operator + (const Stringy& S1,const char* addition);
	// adds an integer to a Stringy. Does not modify parameters.
	friend Stringy & operator + (const Stringy& S1, const int num_Toadd);
	// adds a Stringy to this Stringy. Modifies left hand side of operator. Does not modify right side.
	Stringy & operator += (const Stringy& S1);
	// less than operator
	friend bool operator< (const Stringy& rhs, const Stringy& lhs);
	// less than or equal to operator
	friend bool operator <= (const Stringy& rhs, const Stringy& lhs);
	// not equal operator
	friend bool operator !=(const Stringy& S1, const Stringy& S2);
private:
	int ylength;
	char* ystring;

};
#endif //S20_PA01_SENTIMENTANALYSIS_STRINGY_H
