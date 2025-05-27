#include "Tests.hpp"

void TestSuite::Assert(bool condition, const std::string& testName) {
    totalTests++;
    if (condition) {
        passedTests++;
        std::cout << "Test " << testName << ": PASSED\n";
    } else {
        std::cout << "Test " << testName << ": FAILED\n";
    }
}

void TestSuite::RunAllTests() {
    totalTests = 0;
    passedTests = 0;
    std::cout << "Running all tests...\n";
    TestMutableArraySequence();
    TestImmutableArraySequence();
    TestMutableListSequence();
    TestImmutableListSequence();
    std::cout << "Test Summary: " << passedTests << "/" << totalTests << " passed\n";
}

void TestSuite::TestMutableArraySequence() {
    MutableArraySequence<int> seq;
    Assert(seq.GetLength() == 0, "MutableArraySequence: Empty constructor");

    int data[] = {1, 2, 3};
    MutableArraySequence<int> seq2(data, 3);
    Assert(seq2.GetLength() == 3, "MutableArraySequence: Array constructor length");
    Assert(seq2.GetFirst() == 1, "MutableArraySequence: Array constructor GetFirst");
    Assert(seq2.GetLast() == 3, "MutableArraySequence: Array constructor GetLast");
    Assert(seq2.Get(1) == 2, "MutableArraySequence: Array constructor Get");

    LinkedList<int> list;
    list.Append(4);
    list.Append(5);
    MutableArraySequence<int> seq3(list);
    Assert(seq3.GetLength() == 2 && seq3.GetFirst() == 4, "MutableArraySequence: LinkedList constructor");

    seq2.Append(4);
    Assert(seq2.GetLength() == 4 && seq2.GetLast() == 4, "MutableArraySequence: Append");

    seq2.Prepend(0);
    Assert(seq2.GetLength() == 5 && seq2.GetFirst() == 0, "MutableArraySequence: Prepend");

    seq2.InsertAt(10, 2);
    Assert(seq2.Get(2) == 10, "MutableArraySequence: InsertAt");

    MutableArraySequence<int> seq4(data, 3);
    seq2.Concat(&seq4);
    Assert(seq2.GetLength() == 8 && seq2.GetLast() == 3, "MutableArraySequence: Concat");

    Sequence<int>* subSeq = seq2.GetSubsequence(1, 3);
    Assert(subSeq->GetLength() == 3 && subSeq->Get(0) == 1, "MutableArraySequence: GetSubsequence");
    delete subSeq;

    bool caught = false;
    try {
        seq.GetFirst();
    } catch (const std::out_of_range&) {
        caught = true;
    }
    Assert(caught, "MutableArraySequence: GetFirst empty throws");

    caught = false;
    try {
        seq2.Get(-1);
    } catch (const std::out_of_range&) {
        caught = true;
    }
    Assert(caught, "MutableArraySequence: Get negative index throws");
}

void TestSuite::TestImmutableArraySequence() {
    ImmutableArraySequence<int> seq;
    Assert(seq.GetLength() == 0, "ImmutableArraySequence: Empty constructor");

    int data[] = {1, 2, 3};
    ImmutableArraySequence<int> seq2(data, 3);
    Assert(seq2.GetLength() == 3, "ImmutableArraySequence: Array constructor length");
    Assert(seq2.GetFirst() == 1, "ImmutableArraySequence: Array constructor GetFirst");

    LinkedList<int> list;
    list.Append(4);
    list.Append(5);
    ImmutableArraySequence<int> seq3(list);
    Assert(seq3.GetLength() == 2 && seq3.GetFirst() == 4, "ImmutableArraySequence: LinkedList constructor");

    Sequence<int>* seq4 = seq2.Append(4);
    Assert(seq2.GetLength() == 3 && seq4->GetLength() == 4 && seq4->GetLast() == 4, "ImmutableArraySequence: Append immutable");
    delete seq4;

    Sequence<int>* seq5 = seq2.Prepend(0);
    Assert(seq2.GetLength() == 3 && seq5->GetLength() == 4 && seq5->GetFirst() == 0, "ImmutableArraySequence: Prepend immutable");
    delete seq5;

    Sequence<int>* seq6 = seq2.InsertAt(10, 1);
    Assert(seq2.GetLength() == 3 && seq6->GetLength() == 4 && seq6->Get(1) == 10, "ImmutableArraySequence: InsertAt immutable");
    delete seq6;

    ImmutableArraySequence<int> seq7(data, 3);
    Sequence<int>* seq8 = seq2.Concat(&seq7);
    Assert(seq2.GetLength() == 3 && seq8->GetLength() == 6 && seq8->GetLast() == 3, "ImmutableArraySequence: Concat immutable");
    delete seq8;

    Sequence<int>* subSeq = seq2.GetSubsequence(0, 1);
    Assert(subSeq->GetLength() == 2 && subSeq->GetFirst() == 1, "ImmutableArraySequence: GetSubsequence");
    delete subSeq;

    bool caught = false;
    try {
        seq.GetLast();
    } catch (const std::out_of_range&) {
        caught = true;
    }
    Assert(caught, "ImmutableArraySequence: GetLast empty throws");
}

void TestSuite::TestMutableListSequence() {
    MutableListSequence<int> seq;
    Assert(seq.GetLength() == 0, "MutableListSequence: Empty constructor");

    int data[] = {1, 2, 3};
    MutableListSequence<int> seq2(data, 3);
    Assert(seq2.GetLength() == 3, "MutableListSequence: Array constructor length");
    Assert(seq2.GetFirst() == 1, "MutableListSequence: Array constructor GetFirst");
    Assert(seq2.GetLast() == 3, "MutableListSequence: Array constructor GetLast");

    LinkedList<int> list;
    list.Append(4);
    list.Append(5);
    MutableListSequence<int> seq3(list);
    Assert(seq3.GetLength() == 2 && seq3.GetFirst() == 4, "MutableListSequence: LinkedList constructor");

    seq2.Append(4);
    Assert(seq2.GetLength() == 4 && seq2.GetLast() == 4, "MutableListSequence: Append");

    seq2.Prepend(0);
    Assert(seq2.GetLength() == 5 && seq2.GetFirst() == 0, "MutableListSequence: Prepend");

    seq2.InsertAt(10, 2);
    Assert(seq2.Get(2) == 10, "MutableListSequence: InsertAt");

    MutableListSequence<int> seq4(data, 3);
    seq2.Concat(&seq4);
    Assert(seq2.GetLength() == 8 && seq2.GetLast() == 3, "MutableListSequence: Concat");

    Sequence<int>* subSeq = seq2.GetSubsequence(1, 3);
    Assert(subSeq->GetLength() == 3 && subSeq->Get(0) == 1, "MutableListSequence: GetSubsequence");
    delete subSeq;

    bool caught = false;
    try {
        seq.Get(0);
    } catch (const std::out_of_range&) {
        caught = true;
    }
    Assert(caught, "MutableListSequence: Get empty throws");
}

void TestSuite::TestImmutableListSequence() {
    ImmutableListSequence<int> seq;
    Assert(seq.GetLength() == 0, "ImmutableListSequence: Empty constructor");

    int data[] = {1, 2, 3};
    ImmutableListSequence<int> seq2(data, 3);
    Assert(seq2.GetLength() == 3, "ImmutableListSequence: Array constructor length");
    Assert(seq2.GetFirst() == 1, "ImmutableListSequence: Array constructor GetFirst");

    LinkedList<int> list;
    list.Append(4);
    list.Append(5);
    ImmutableListSequence<int> seq3(list);
    Assert(seq3.GetLength() == 2 && seq3.GetFirst() == 4, "ImmutableListSequence: LinkedList constructor");

    Sequence<int>* seq4 = seq2.Append(4);
    Assert(seq2.GetLength() == 3 && seq4->GetLength() == 4 && seq4->GetLast() == 4, "ImmutableListSequence: Append immutable");
    delete seq4;

    Sequence<int>* seq5 = seq2.Prepend(0);
    Assert(seq2.GetLength() == 3 && seq5->GetLength() == 4 && seq5->GetFirst() == 0, "ImmutableListSequence: Prepend immutable");
    delete seq5;

    Sequence<int>* seq6 = seq2.InsertAt(10, 1);
    Assert(seq2.GetLength() == 3 && seq6->GetLength() == 4 && seq6->Get(1) == 10, "ImmutableListSequence: InsertAt immutable");
    delete seq6;

    ImmutableListSequence<int> seq7(data, 3);
    Sequence<int>* seq8 = seq2.Concat(&seq7);
    Assert(seq2.GetLength() == 3 && seq8->GetLength() == 6 && seq8->GetLast() == 3, "ImmutableListSequence: Concat immutable");
    delete seq8;

    Sequence<int>* subSeq = seq2.GetSubsequence(0, 1);
    Assert(subSeq->GetLength() == 2 && subSeq->GetFirst() == 1, "ImmutableListSequence: GetSubsequence");
    delete subSeq;

    bool caught = false;
    try {
        seq.GetFirst();
    } catch (const std::out_of_range&) {
        caught = true;
    }
    Assert(caught, "ImmutableListSequence: GetFirst empty throws");
}
