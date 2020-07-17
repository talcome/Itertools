//
// Created by ko tal on 21/06/2020.
//
#include "doctest.h"
#include <string>
#include <vector>
#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"
using namespace itertools;
using namespace std;

vector<string> strVector = {"I", "Love", "C++","I", "Love", "C++","I", "Love", "C++"};
vector<int> intVector = {50, 60, 47, 35, 22, -17, 44,-30,65};
vector<char> charVector = {'a', 'b', 'c', 'd','e','f','g','h','i'};
vector<double> doubleVector = {3.40, 4.30, 7.9, 11.3, 1.25, 99.9, 0.0,1.1, 10000.00001, 11.11111};
vector<bool> boolVector = {true, false, false, false, true, true, false, false, true};

template<typename T> struct functor{bool operator()(T x){return (x + 1) % 2 == 0;}};

template<typename T> struct boolFunctor{bool operator()(T x){return x > 10;}};

TEST_CASE("Range"){
    int expected = 1;
    for(int i: range(1,11)){
        CHECK(expected == i);
        expected++;
    }
}

TEST_CASE("Range in Accumulate"){
    int index=0;
    for (auto i : accumulate(range(1,5))) {
                CHECK(intVector[index] == i);
        index++;
    }

    index=0;
    for (auto i : accumulate(range(-5,1))) {
                CHECK(intVector[index] == i);
        index++;
    }
}

TEST_CASE("Vector in Accumulate"){
    int index = 0;
    for(string i : accumulate(strVector)){
        CHECK(strVector[index] == i);
        index++;
    }

    index=0;
    for(int i : accumulate(intVector)){
        CHECK(intVector[index] == i);
        index++;
    }

    index=0;
    for(char i : accumulate(charVector)){
        CHECK(charVector[index] == i);
        index++;
    }

    index=0;
    for(double i : accumulate(doubleVector)){
        CHECK(doubleVector[index] == i);
        index++;
    }
}

TEST_CASE("Accumulate"){
    auto a1 = accumulate(vector(intVector), [](int a, int b){return a*b;});
    int expected1[] = {50, 300, 47, 35, 22, -17, 44,-30,65};
    int index = 0;
    for(auto i : a1){
        CHECK(i == expected1[index]);
        index++;
    }

    auto a2 = accumulate(vector(doubleVector), [](int a, int b){return a*b;});
    double expected2[] = {3.40, 4.30, 7.9, 11.3, 1.25, 99.9, 0.0,1.1, 10000.00001, 11.11111};
    index = 0;
    for(auto i : a2){
        CHECK(i == expected2[index]);
        index++;
    }
}

TEST_CASE("Filterfalse"){
    auto ff1 = filterfalse(vector(intVector), functor<int>());
    int expected1[] = {50,22,-17,65};
    int index = 0;
    for(int i : ff1){
        CHECK(i == expected1[index]);
        index++;
    }

    auto ff2 = filterfalse(vector(doubleVector), functor<double>());
    double expected2[] = {3.40, 1.25, 99.9, 11.11111};
    index = 0;
    for(auto i : ff2){
        CHECK(i == expected2[index]);
        index++;
    }

    auto ff3 = filterfalse(vector(strVector), functor<string>());
    string expected3[] = {"I", "Love", "C++", "C++"};
    index = 0;
    for(auto i : ff3){
        CHECK(i == expected3[index]);
        index++;
    }

    auto ff4 = filterfalse(vector(charVector), functor<char>());
    char expected4[] = {'a', 'e','f','g','h','i'};
    index = 0;
    for(auto i : ff4){
        CHECK(i == expected4[index]);
        index++;
    }

    auto ff5 = filterfalse(vector(intVector), boolFunctor<int>());
    int expected5[] = {50, 60, 47, 35, 22, 44, 65};
    index = 0;
    for(int i : ff5){
        CHECK(i == expected5[index]);
        index++;
    }

    auto ff6 = filterfalse(vector(doubleVector), boolFunctor<double>());
    double expected6[] = {11.3, 99.9,10000.00001, 11.11111};
    index = 0;
    for(auto i : ff6){
        CHECK(i == expected6[index]);
        index++;
    }
}

TEST_CASE("Compress"){
    auto c1 = compress(vector(intVector),vector(boolVector));
    int expected1[] = {50,22,-17,65};
    int index = 0;
    for (auto i : c1) {
        CHECK(i == expected1[index]);
        index++;
    }

    auto c2 = compress(vector(doubleVector),vector(boolVector));
    double expected2[] = {3.40, 1.25, 99.9, 11.11111};
    index = 0;
    for (auto i : c2) {
        CHECK(i == expected2[index]);
        index++;
    }

    auto c3 = compress(vector(strVector),vector(boolVector));
    string expected3[] = {"I", "Love", "C++", "C++"};
    index = 0;
    for (auto i : c3) {
        CHECK(i == expected3[index]);
        index++;
    }

    auto c4 = compress(vector(charVector),vector(boolVector));
    char expected4[] = {'a', 'e','f','g','h','i'};
    index = 0;
    for (auto i : c4) {
        CHECK(i == expected4[index]);
        index++;
    }
}
