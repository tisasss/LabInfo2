#pragma once

#include <iostream>
#include <string>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "Tests.hpp"

class UI {
public:
    UI();
    void Run();
private:
    Sequence<int>* currentSeq;
    void PrintMenu();
    void SelectSequenceType();
    void PerformOperation();
    void PrintSequence();
    void RunTests();
    void SafeDelete();
};
