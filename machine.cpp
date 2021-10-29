//
// Created by loggityloglog on 9/15/20.
//
#include "machine.h"
#include <iostream>
using namespace std;
machine :: machine(){
words_To_pageNums = map<Stringy,LinkyList<int>>();
groupNames_To_Words = map<Stringy,set<Stringy>>();
}
void machine::jumpStart (ifstream& input, ofstream& output) {
this->pull_And_Sort (input);
//this->deBug();
this->output_File (output);
}

machine& machine:: operator= (const machine &rhs) {
this->words_To_pageNums = rhs.words_To_pageNums;
this->groupNames_To_Words = rhs.groupNames_To_Words;
return *this;
}

void machine::pull_And_Sort (ifstream& input_File) {
char getNumber[1000];
char buffer[1000];
Stringy pgNum;
int loopnum = 0;
// gets a line of the page number
	cout << "begin sorting" << endl;
while(!input_File.eof()) {
	loopnum++;
	// check if the next line is a page number
	if(input_File.peek() == '<') {
		input_File.getline (getNumber, 999);
		//cout << "getnumber char array: " << getNumber << endl;
		pgNum = Stringy (getNumber).get_Pg_Nmbr ();
		if(pgNum == "-1") break;
	}
	// gets a line of words
	input_File.getline (buffer, 999);
	// instantiate a stringy and clean it up a bit
	Stringy lineOfWords (buffer);
	lineOfWords.toUpper ();
	// get a vector of pairs of a word and its group
	Vecty<pair<Stringy, Stringy *>> pairMe = lineOfWords.check_For_Goups ();
	int vectSize = pairMe.getSize();
	// for each of the words which were acquired
	for(int i = 0; i < vectSize; i++){
		// remove the unnecessary punctuation from the words
		pairMe[i].first.remPunct();
		// if the word has a grouping
	if (pairMe[i].second != nullptr) {
		//cout << "pairMe[" << i << "].second before punct: " << *pairMe[i].second << endl;
		(pairMe)[i].second->remPunct();
		//cout << "pairMe[" << i << "].second after punct: " << *pairMe[i].second << endl;
		// put the key groupName with value page number
		groupNames_To_Words[*(pairMe[i].second)].insert(pairMe[i].first);
		//cout << "Adding " << pgNum << " to groupnames" << endl;
		// put the key wordName with the value page number
		words_To_pageNums[ pairMe[i].first ].push_back(pgNum.toInt ());
	}
		// if the word does not have a grouping
	else {
		// put the key wordName with the value page number
		words_To_pageNums[ pairMe[i].first ].push_back(pgNum.toInt());
	}
}
	}
cout << "end sorting" << endl;
// after all information has been processed
}

void machine::output_File (ofstream &output_File) {
	cout << "begin output_File" << endl;
	auto group = groupNames_To_Words.begin();
	map<Stringy,LinkyList<int>> :: iterator word = words_To_pageNums.begin();
	int wordsPrinted = 0;
	int toPrint = groupNames_To_Words.size() + words_To_pageNums.size();;
	char printLetter = 48;
	bool newLetter = true;
	bool wordEnd = false;
	bool groupEnd = false;
	while(wordsPrinted < toPrint) {
		if(word == words_To_pageNums.end()) wordEnd = true;
		if (group == groupNames_To_Words.end()) groupEnd = true;
		// if the letter to print it equal to the first letter in a word or group
		if (checkLettering(word,printLetter, wordEnd)|| checkLettering(group,printLetter, groupEnd)){
			//cout << "checklettering is true for letter: " << (char)printLetter << endl;
			// if group is earlier than word
			if ((groupLessThanWord(group,groupEnd,word,wordEnd) == 10) && newLetter){
				//cout << "group first is: " << group->first << endl;
				output_File << "[" << (char)printLetter << endl;
				newLetter = false;
			// if word is earlier than group
		} else if((groupLessThanWord(group,groupEnd,word,wordEnd)== 20) && newLetter){
				//cout << "word first is: " << word->first << endl;
				output_File << "[" << (char)printLetter << "]" << endl;
				newLetter = false;
			}
		} else {
			// increase printLetter within printable bounds
			if (printLetter == 57) {printLetter = 65;}
			else {printLetter++;}
			newLetter = true;
			continue;
		}
		// if word is at end
		if (wordEnd) {
			//cout <<"end word" << endl;
			output_Group (group, output_File);
			++wordsPrinted;
			group++;
			continue;
		} else if (groupEnd) {
			//cout << "end group" << endl;
			output_Word (word, output_File);
			++wordsPrinted;
			word++;
			continue;
		} else {
				if (group->first < word->first) {
					output_Group (group, output_File);
					wordsPrinted++;
					group++;
					continue;
				}
			if (word->first < group->first) {
				output_Word (word, output_File);
				wordsPrinted++;
				word++;
				continue;
			}
			if(word->first == group->first){
				output_Group (group, output_File);
				wordsPrinted++;
				group++;
				output_Word (word, output_File);
				wordsPrinted++;
				word++;
			}
		}
	}
	cout << "end output_File" << endl;
}
int machine:: output_Word(map<Stringy,LinkyList<int>>:: iterator& it, ofstream& out, bool subCategory, int numChars){
	if(it == this->words_To_pageNums.end())return 0;
	int charsInLine = numChars;
	it->second.insertionSort();
	it->second.remDuplicates ();
	if(subCategory) out << "  ";
	charsInLine +=2;
	// if the name does not sent it past 50
	if((charsInLine + it->first.charLength() + 2) <= 50) {
		out << it->first << ": ";
		// add to chars in line
		charsInLine += it->first.charLength ();
		charsInLine += 2;
	// if the name does send it past 50
	} else {
		out << endl << "    ";
		charsInLine = 4;
		out << it->first << ": ";
		charsInLine +=2;
		charsInLine += it->first.charLength();
	}
		auto iter = it->second.begin();
	if ((charsInLine + (Stringy(*iter)).charLength()) <= 50 ) {
		out << *iter;
		charsInLine += (Stringy(*iter)).charLength();
	} else {
		out << endl << "    ";
		charsInLine = 4;
		out << *iter;
		charsInLine += (Stringy(*iter).charLength());
	}
	++iter;
	for(auto i = iter; i != it->second.end(); ++i){
		if ((charsInLine + (Stringy (*i).length()-1 + 2)) > 50) {
			out << endl << "    ";
			charsInLine = 4;
			out << *i;
			charsInLine += (Stringy(*i).length()-1);
		} else {
			out << ", " << *i;
			charsInLine += (Stringy (*i)).length () - 1;
			charsInLine += 2;
		}
	}
	out << endl;
	return charsInLine;
}
bool machine :: checkLettering(map<Stringy, set<Stringy>> ::iterator it, char toFind, bool ended){
if (!ended){
	return it->first.at(0) == toFind;
} else return false;
}
bool machine :: checkLettering(map<Stringy,LinkyList<int>> ::iterator it, char toFind, bool ended){
	if (!ended){
		return it->first.at(0) == toFind;
	} else return false;
}
int machine:: groupLessThanWord (map<Stringy,set<Stringy>> ::iterator group, bool grpEnd, map<Stringy,LinkyList<int>> ::iterator word, bool wrdEnd){
	if(wrdEnd){
		if(grpEnd){
			return 0;
		} else
			return 10;
	}
	else if (grpEnd){
			return 20;
	}
	else {
		return (group->first <= word->first)? 10 : 20;
	}
}


void machine::output_Group (map<Stringy, set<Stringy>>::iterator& it, ofstream &out) {
	// print out the pagenumbers for the group
	//int chars = output_Word (it,out);
	int charsInLine = 0;
	if(it == this->groupNames_To_Words.end())return;
	// prints the group
	out << it->first << ": ";
	charsInLine += 2;
	charsInLine += it->first.length()-1;
	// prints all the numbers.
	Vecty<int> groupNums;
	for(auto ity = groupNames_To_Words[it->first].begin(); ity != groupNames_To_Words[it->first].end(); ity++) {
		for (auto ityy = words_To_pageNums[ *ity ].begin (); ityy != words_To_pageNums[ *ity ].end (); ++ityy) {
			groupNums.push_back (*ityy);
		}
	}
		groupNums.insertionSort();
		groupNums.remDuplicates();
	if((charsInLine + 2 + Stringy(groupNums[0]).length() - 1) <= 50) {
		out << groupNums[0];
		charsInLine += Stringy(groupNums[0]).length() - 1;
	} else {
		out << endl << "    ";
		out << groupNums[0];
		charsInLine = 4;
		charsInLine += Stringy(groupNums[0]).length() - 1;
	}
		for(int i = 1; i < groupNums.getSize (); i++){
			if((charsInLine + 2 + Stringy(groupNums[i]).length() - 1) <= 50) {
				out << ", " << groupNums[i];
				charsInLine += 2;
				charsInLine += Stringy(groupNums[i]).length() - 1;
			} else {
				out << endl << "    ";
				out << groupNums[i];
				charsInLine = 4;
				charsInLine += Stringy(groupNums[i]).length() - 1;
			}
		}

	out << endl;
	// print out the subwords that are in the group
/*------------------------------------------------------*/
	// iterator to beginning of set of subwords
	// iterate through the elements in the set of words

	for(auto i = groupNames_To_Words[it->first].begin(); i != groupNames_To_Words[it->first].end(); i++){
		// print out each of the elements using output word
		auto parameterInput = words_To_pageNums.find(*i);
		output_Word(parameterInput,out, true);
	}
}

void machine::deBug () {
	cout << "GroupNames to Words" << endl;
	cout << "-------------------" << endl;
for(auto it = this->groupNames_To_Words.begin(); it != groupNames_To_Words.end(); it++){
	cout << endl;
	cout << "Groupname: ";
	cout << it->first << endl;
	cout << "Words inside" << endl;
	cout << "~~~~~~~~~~~~" << endl;
	for(auto i = it->second.begin(); i != it->second.end(); i++){
		cout << *i << endl;
	}
}
	cout << "Words to pageNums" << endl;
	cout << "-------------------" << endl;
	for(auto it = this->words_To_pageNums.begin(); it != words_To_pageNums.end(); it++){
		cout << endl;
		cout << "Word: ";
		cout << it->first << endl;
		cout << "pageNums inside" << endl;
		cout << "~~~~~~~~~~~~" << endl;
		for(auto i = it->second.begin(); i != it->second.end(); i.operator++ ()){
			cout << *i << endl;
		}
	}
}
