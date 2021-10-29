//
// Created by Christian Gould on 9/16/20.
//
#include "catch.hpp"
#include "LinkyList.h"
#include "Stringy.h"
TEST_CASE("Linked List Tests" "[LinkyList.h]") {
	SECTION("primitive type tests for minimum functionality") {
		LinkyList<int> LinkTester;
		LinkTester.push_back (5);
		REQUIRE(LinkTester.getSize () == 1);
		LinkTester.push_back (7);
		REQUIRE(LinkTester.getSize () == 2);
		REQUIRE(LinkTester[ 0 ] == 5);
		REQUIRE(LinkTester[ 1 ] == 7);
		LinkTester.push_back (10);
		REQUIRE(LinkTester.getSize () == 3);
		LinkTester.push_back (27);
		REQUIRE(LinkTester.getSize () == 4);
		LinkTester.remove (1);
		REQUIRE(LinkTester[ 1 ] == 10);
		REQUIRE(LinkTester.getSize () == 3);
		LinkTester.remove (1);
		REQUIRE(LinkTester[ 1 ] == 27);
		REQUIRE(LinkTester.getSize () == 2);
	}SECTION("complex type tests for minimum functionality") {
		LinkyList<Stringy> LinkyString;
		LinkyString.push_back (Stringy ("Hello"));
		REQUIRE(LinkyString.getSize () == 1);
		LinkyString.push_back (Stringy ("Goodbye"));
		REQUIRE(LinkyString.getSize () == 2);
		REQUIRE(LinkyString[ 0 ] == "Hello");
		REQUIRE(LinkyString[ 1 ] == "Goodbye");
		LinkyString.push_back (Stringy ("Yes"));
		REQUIRE(LinkyString.getSize () == 3);
		LinkyString.push_back ((Stringy ("No")));
		REQUIRE(LinkyString.getSize () == 4);
		LinkyString.remove (1);
		REQUIRE(LinkyString[ 1 ] == "Yes");
		REQUIRE(LinkyString.getSize () == 3);
		LinkyString.remove (1);
		REQUIRE(LinkyString[ 1 ] == "No");
		REQUIRE(LinkyString.getSize () == 2);
	}SECTION("LinkyIterator functionality") {
		LinkyList<Stringy> okie;
		okie.push_back (Stringy ("uno"));
		okie.push_back (Stringy ("dos"));
		okie.push_back (Stringy ("tres"));
		okie.push_back (Stringy ("quattro"));
		okie.push_back (Stringy ("cinco"));
// create the iterator
		auto okieiter = okie.begin ();
		CHECK(*okieiter == "uno");
		++okieiter;
		CHECK(*okieiter == "dos");
		++okieiter;
		CHECK(*okieiter == "tres");
		++okieiter;
		CHECK(*okieiter == "quattro");
		++okieiter;
		CHECK(*okieiter == "cinco");
		int counter = 0;
		okieiter = okie.begin ();
		while (*okieiter != *okie.end ()) {
			//cout << "in while, where okieier = " << *okieiter << "and end = " << *okie.end() << endl;
			counter++;
			okieiter.operator++ ();
		}
		CHECK(counter == 5);
	}SECTION ("Insertion Sort funtionality") {
		LinkyList<int> inty;
		LinkyList<Stringy> stry;
		inty.push_back (1);
		inty.push_back (10);
		inty.push_back (8);
		inty.push_back (3);
		inty.insertionSort ();
		CHECK(inty[ 0 ] == 1);
		CHECK(inty[ 1 ] == 3);
		CHECK(inty[ 2 ] == 8);
		CHECK(inty[ 3 ] == 10);
		stry.push_back (Stringy ("AAA"));
		stry.push_back (Stringy ("ZZZ"));
		stry.push_back (Stringy ("BBB"));
		stry.push_back (Stringy ("CCC"));
		stry.insertionSort ();
		CHECK(stry[ 0 ] == "AAA");
		CHECK(stry[ 1 ] == "BBB");
		CHECK(stry[ 2 ] == "CCC");
		CHECK(stry[ 3 ] == "ZZZ");
	}SECTION ("Remove duplicates function") {
		LinkyList<int> linker;
		LinkyList<Stringy> stry;
		linker.push_back (2);
		linker.push_back (2);
		linker.push_back (45);
		linker.push_back (52);
		linker.push_back (45);
		linker.push_back (52);
		linker.insertionSort ();
		linker.remDuplicates ();
		CHECK(linker.getSize () == 3);
		CHECK(linker[ 0 ] == 2);
		CHECK(linker[ 1 ] == 45);
		CHECK(linker[ 2 ] == 52);
		stry.push_back (Stringy ("AAA"));
		stry.push_back (Stringy ("ZZZ"));
		stry.push_back (Stringy ("BBB"));
		stry.push_back (Stringy ("AAA"));
		stry.push_back (Stringy ("ZZZ"));
		stry.push_back (Stringy ("CCC"));
		stry.insertionSort ();
		stry.remDuplicates ();
		CHECK(stry.getSize () == 4);
		CHECK(stry[ 0 ] == "AAA");
		CHECK(stry[ 1 ] == "BBB");
		CHECK(stry[ 2 ] == "CCC");
		CHECK(stry[ 3 ] == "ZZZ");
		// small test cases for binary search
		CHECK(stry.binarySearch ("AAA", 0, 3) == 0);
		CHECK(stry.binarySearch ("BBB", 0, 3) == 1);
		CHECK(stry.binarySearch ("CCC", 0, 3) == 2);
		CHECK(stry.binarySearch ("ZZZ", 0, 3) == 3);
		CHECK(linker.binarySearch (2, 0, linker.getSize () - 1) == 0);
		CHECK(linker.binarySearch (45, 0, linker.getSize () - 1) == 1);
		CHECK(linker.binarySearch (52, 0, linker.getSize () - 1) == 2);
	}
	SECTION("assignment operator tests"){
		LinkyList<int> ints;
		LinkyList<Stringy> strings;
		ints.push_back(1);
		ints.push_back(2);
		ints.push_back(3);
		ints.push_back(4);
		strings.push_back("one");
		strings.push_back("two");
		strings.push_back("three");
		strings.push_back("four");
		LinkyList<int> assignInt;
		assignInt = ints;
		LinkyList<Stringy> assignStr;
		assignStr = strings;
		CHECK(assignInt[0] == 1);
		CHECK(assignInt[1] == 2);
		CHECK(assignInt[2] == 3);
		CHECK(assignInt[3] == 4);
		CHECK(assignStr[0] == "one");
		CHECK(assignStr[1] == "two");
		CHECK(assignStr[2] == "three");
		CHECK(assignStr[3] == "four");
		// check that the two LinkedLists are the same
		CHECK(assignStr == strings);
		CHECK(assignInt == ints);
	}

}