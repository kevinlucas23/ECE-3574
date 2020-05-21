#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include <string>
#include <sstream>

#include "cqsort.hpp"

template <typename T>
bool hey_go(const T &vec) {
	for (auto i = 1; i < vec.size(); ++i) {
		if (vec[i-1] > vec[i]) {
			return false;
		}
	}
	return true;
}

TEST_CASE( "Sequential sort of a vector of int", "[cqsort]" ) {
	// test vector
	std::vector<int> v = {2, 4, 1, 3};

	// cqsort for a int vector with zero additional thread
	CQSort<std::vector<int>> cqsort(0);

	// sort
	cqsort(v);

	// test
	REQUIRE(hey_go(v) == true);
	
	v.clear();
	v.push_back(7);
	v.push_back(84);
	v.push_back(2);
	v.push_back(762);
	v.push_back(52);
	v.push_back(0);
	
	cqsort(v);
	
	REQUIRE(hey_go(v));
	
}

TEST_CASE( "Sequential sort of a vector of double", "[cqsort]" ) {
	// test vector
	std::vector<double> v = {1.045, 7.0546, 0.468, 024.798};

	// cqsort for a int vector with zero additional thread
	CQSort<std::vector<double>> cqsort(0);

	// sort
	cqsort(v);

	// test
	REQUIRE(hey_go(v) == true);
	
	v.clear();
	v.push_back(7.47);
	v.push_back(84.90);
	v.push_back(210.79);
	v.push_back(762.798);
	v.push_back(520.4520);
	v.push_back(0.0001);
	
	cqsort(v);
	
	REQUIRE(hey_go(v));
	
}

TEST_CASE( "Sequential sort of a vector of str", "[cqsort]" ) {
	// test vector
	std::vector<std::string> v = {"k", "a", "z", "b"};

	// cqsort for a string vector with zero additional thread
	CQSort<std::vector<std::string>> cqsort(0);

	// sort
	cqsort(v);

	// test
	REQUIRE(hey_go(v) == true);
}


TEST_CASE( "parallel sort of a vector of int", "[cqsort]" ) {
	// test vector
	std::vector<int> v = {2, 4, 1, 3};

	// cqsort for a int vector with zero additional thread
	CQSort<std::vector<int>> cqsort(4);

	// sort
	cqsort(v);

	// test
	REQUIRE(hey_go(v) == true);
	
	v.clear();
	v.push_back(7);
	v.push_back(84);
	v.push_back(2);
	v.push_back(762);
	v.push_back(52);
	v.push_back(0);
	
	cqsort(v);
	
	REQUIRE(hey_go(v));
	
}

TEST_CASE( "parallel sort of a vector of double", "[cqsort]" ) {
	// test vector
	std::vector<double> v = {1.045, 7.0546, 0.468, 024.798};

	// cqsort for a int vector with zero additional thread
	CQSort<std::vector<double>> cqsort(5);

	// sort
	cqsort(v);

	// test
	REQUIRE(hey_go(v) == true);
	
	v.clear();
	v.push_back(7.47);
	v.push_back(84.90);
	v.push_back(210.79);
	v.push_back(762.798);
	v.push_back(520.4520);
	v.push_back(0.0001);
	
	cqsort(v);
	
	REQUIRE(hey_go(v));
	
}

TEST_CASE( "parallel sort of a vector of str", "[cqsort]" ) {
	// test vector
	std::vector<std::string> v = {"k", "a", "z", "b"};

	// cqsort for a string vector with zero additional thread
	CQSort<std::vector<std::string>> cqsort(8);

	// sort
	cqsort(v);

	// test
	REQUIRE(hey_go(v) == true);
}