// Created by Christian Gould on Sep 16, 2020
#define CATCH_CONFIG_RUNNER
#include <iostream>
#include <vector>
#include "machine.h"
#include "catch.hpp"
#include <map>
using namespace std;
// function which returns the index of the given stringy where the beginning of the sentiment starts.
int main (int argc, char **argv) {

	// if the args are not there, run catch.
	if (argc == 1) {
		Catch::Session ().run ();
		return 0;
		// run sentiment analyser.
	} else {
		cout << "Opening: " << argv[ 1 ] << endl;
		cout << "Putting output in: " << argv[ 2 ] << endl;
		ifstream training_Data;
		training_Data.open (argv[ 1 ]);
		ofstream outPut;
		outPut.open (argv[ 2 ]);
		auto *newMachine = new machine ();
		newMachine->jumpStart (training_Data, outPut);
		training_Data.close ();
		outPut.close ();
		cout << "Done" << endl;
	}
	return 0;
}
