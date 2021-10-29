//
// Created by loggityloglog on 9/15/20.
//

#ifndef INC_20F_AUTO_IDX_MACHINE_H
#define INC_20F_AUTO_IDX_MACHINE_H

#include "Stringy.h"
#include "Vecty.h"
#include "LinkyList.h"
#include <map>
#include <set>

class machine {
public:
	/* constructors */
	machine();
	machine(const machine& mach) = default;
	/* destructors */
	// nothing to delete
	~machine() = default;
	/* functions */
	// will call all necessary functions to start the program
	void jumpStart(ifstream& in, ofstream& out);
	// this function will pull the data and sort it into the maps appropriately
	void pull_And_Sort(ifstream& input_File);
	// this function will take the information from the maps and output it to the file
	void output_File(ofstream& output_File);
	/* put this function into jumpstart in order to help debug code
	* outputs all of the words and all of the sorted elements in the program.
	*/
	void deBug();
	// prints out the group of numbers from the given iterator
	int output_Word(map<Stringy,LinkyList<int>>:: iterator& it, ofstream& out, bool subCat = false, int numChars = 0);
	// prints out the group of numbers from the given iterator
	void output_Group(map<Stringy,set<Stringy>>:: iterator& it, ofstream& out);
	// is a failsafe to check if the first letter equals the letter given. Checks for nullptr in group
	bool checkLettering(map<Stringy,set<Stringy>>:: iterator it, char toFind, bool ended);
	// overloaded to take a map of linkylist
	bool checkLettering(map<Stringy,LinkyList<int>>:: iterator it, char toFind, bool ended);
	// compares group and word safely
	int groupLessThanWord (map<Stringy, set<Stringy>> ::iterator group, bool grpEnd, map<Stringy,LinkyList<int>> ::iterator word, bool wrdEnd);
	/* operators */
	machine& operator=(const machine& rhs);
private:
	// map relating the word to a list of page numbers
	map<Stringy,LinkyList<int>> words_To_pageNums;
	// map relating the group name to a list of subcategories.
	map<Stringy,set<Stringy>> groupNames_To_Words;
};
#endif //INC_20F_AUTO_IDX_MACHINE_H
