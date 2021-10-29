//
// Created by Christian Gould on 9/16/20.
//
#include "catch.hpp"
#include "Vecty.h"
#include "Stringy.h"
TEST_CASE("Vector Tests" "[Vecty.h]"){
SECTION("primitive type tests for minimum functionality") {
Vecty<int> vectTester;
vectTester.push_back (5);
REQUIRE(vectTester.getSize () == 1);
vectTester.push_back (7);
REQUIRE(vectTester.getSize () == 2);
REQUIRE(vectTester[ 0 ] == 5);
REQUIRE(vectTester[ 1 ] == 7);
vectTester.push_back (10);
REQUIRE(vectTester.getSize () == 3);
vectTester.push_back (27);
REQUIRE(vectTester.getSize () == 4);
vectTester.remove (1);
REQUIRE(vectTester[ 1 ] == 10);
REQUIRE(vectTester.getSize () == 3);
vectTester.remove (1);
REQUIRE(vectTester[ 1 ] == 27);
REQUIRE(vectTester.getSize () == 2);
}
SECTION("complex type tests for minimum functionality"){
Vecty<Stringy> VectyString;
VectyString.push_back(Stringy("Hello"));
REQUIRE(VectyString.getSize() == 1);
VectyString.push_back(Stringy("Goodbye"));
REQUIRE(VectyString.getSize() == 2);
REQUIRE(VectyString[0] == "Hello");
REQUIRE(VectyString[1] == "Goodbye");
VectyString.push_back(Stringy("Yes"));
REQUIRE(VectyString.getSize() == 3);
VectyString.push_back((Stringy("No")));
REQUIRE(VectyString.getSize() == 4);
VectyString.remove(1);
REQUIRE(VectyString[1] == "Yes");
REQUIRE(VectyString.getSize() == 3);
VectyString.remove(1);
REQUIRE(VectyString[1] == "No");
REQUIRE(VectyString.getSize() == 2);
}
SECTION("Iterator functionality"){
Vecty<Stringy> okie;
okie.push_back(Stringy("uno"));
okie.push_back(Stringy("dos"));
okie.push_back(Stringy("tres"));
okie.push_back(Stringy("quattro"));
okie.push_back(Stringy("cinco"));
// create the iterator
auto okieiter = okie.begin();
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
okieiter = okie.begin();
while(*okieiter != *okie.end()){
	counter++;
	++okieiter;
}
CHECK(counter == 5);
}
SECTION("insertion sort tests"){
		Vecty<int> inty;
		Vecty<Stringy> stry;
		inty.push_back(1);
		inty.push_back(10);
		inty.push_back(8);
		inty.push_back(3);
		inty.insertionSort();
		CHECK(inty[0] == 1);
		CHECK(inty[1] == 3);
		CHECK(inty[2] == 8);
		CHECK(inty[3] == 10);
		stry.push_back(Stringy("AAA"));
		stry.push_back(Stringy("ZZZ"));
		stry.push_back(Stringy("BBB"));
		stry.push_back(Stringy("CCC"));
		stry.insertionSort();
		CHECK(stry[0] == "AAA");
		CHECK(stry[1] == "BBB");
		CHECK(stry[2] == "CCC");
		CHECK(stry[3] == "ZZZ");
	}
	SECTION("remove duplicates function"){
		Vecty<int> vector;
		Vecty<Stringy> stry;
		vector.push_back(2);
		vector.push_back(2);
		vector.push_back(45);
		vector.push_back(52);
		vector.push_back(45);
		vector.push_back(52);
		vector.insertionSort();
		vector.remDuplicates();
		CHECK(vector.getSize() == 3);
		CHECK(vector[0] == 2);
		CHECK(vector[1] == 45);
		CHECK(vector[2] == 52);
		stry.push_back(Stringy("AAA"));
		stry.push_back(Stringy("ZZZ"));
		stry.push_back(Stringy("BBB"));
		stry.push_back(Stringy("AAA"));
		stry.push_back(Stringy("ZZZ"));
		stry.push_back(Stringy("CCC"));
		stry.insertionSort();
		stry.remDuplicates();
		CHECK(stry.getSize() == 4);
		CHECK(stry[0] == "AAA");
		CHECK(stry[1] == "BBB");
		CHECK(stry[2] == "CCC");
		CHECK(stry[3] == "ZZZ");
		CHECK(stry.binarySearch("AAA", 0, 3) == 0);
		CHECK(stry.binarySearch("BBB", 0, 3) == 1);
		CHECK(stry.binarySearch("CCC", 0, 3) == 2);
		CHECK(stry.binarySearch("ZZZ", 0, 3) == 3);
		CHECK(vector.binarySearch(2, 0, vector.getSize()-1) == 0);
		CHECK(vector.binarySearch(45, 0, vector.getSize()-1) == 1);
		CHECK(vector.binarySearch(52, 0, vector.getSize()-1) == 2);
	}

	SECTION("assignment operator tests"){
		Vecty<int> ints;
		Vecty<Stringy> strings;
		ints.push_back(1);
		ints.push_back(2);
		ints.push_back(3);
		ints.push_back(4);
		strings.push_back("one");
		strings.push_back("two");
		strings.push_back("three");
		strings.push_back("four");
		Vecty<int> assignInt;
		assignInt = ints;
		Vecty<Stringy> assignStr;
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

