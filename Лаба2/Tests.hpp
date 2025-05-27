#pragma once

#include <iostream>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"

class TestSuite {
public:
    void RunAllTests();
private:
    int totalTests;
    int passedTests;
    void Assert(bool condition, const std::string& testName);
    void TestMutableArraySequence();
    void TestImmutableArraySequence();
    void TestMutableListSequence();
    void TestImmutableListSequence();
};
