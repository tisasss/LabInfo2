#include "UI.hpp"

UI::UI() : currentSeq(nullptr) {}

void UI::Run() {
    while (true) {
        PrintMenu();
        int choice;
        std::cin >> choice;
        if (choice == 0) {
            SafeDelete();
            break;
        }
        if (choice == 1) {
            SafeDelete();
            SelectSequenceType();
        } else if (choice == 2 && currentSeq != nullptr) {
            PerformOperation();
        } else if (choice == 3 && currentSeq != nullptr) {
            PrintSequence();
        } else if (choice == 4) {
            RunTests();
        } else {
            std::cout << "Invalid choice or no sequence selected.\n";
        }
    }
}

void UI::PrintMenu() {
    std::cout << "\n=== Sequence Tester ===\n";
    std::cout << "1. Select sequence type\n";
    std::cout << "2. Perform operation\n";
    std::cout << "3. Print sequence\n";
    std::cout << "4. Run tests\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";
}

void UI::SelectSequenceType() {
    std::cout << "\nSelect sequence type:\n";
    std::cout << "1. Mutable Array Sequence\n";
    std::cout << "2. Immutable Array Sequence\n";
    std::cout << "3. Mutable List Sequence\n";
    std::cout << "4. Immutable List Sequence\n";
    std::cout << "Choice: ";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        currentSeq = new MutableArraySequence<int>();
    } else if (choice == 2) {
        currentSeq = new ImmutableArraySequence<int>();
    } else if (choice == 3) {
        currentSeq = new MutableListSequence<int>();
    } else if (choice == 4) {
        currentSeq = new ImmutableListSequence<int>();
    } else {
        std::cout << "Invalid choice.\n";
    }
}

void UI::PerformOperation() {
    std::cout << "\nSelect operation:\n";
    std::cout << "1. Append\n";
    std::cout << "2. Prepend\n";
    std::cout << "3. InsertAt\n";
    std::cout << "4. Get\n";
    std::cout << "5. GetFirst\n";
    std::cout << "6. GetLast\n";
    std::cout << "7. GetSubsequence\n";
    std::cout << "8. Concat\n";
    std::cout << "9. GetLength\n";
    std::cout << "Choice: ";
    int choice;
    std::cin >> choice;

    try {
        if (choice == 1) {
            std::cout << "Enter item: ";
            int item;
            std::cin >> item;
            Sequence<int>* result = currentSeq->Append(item);
            if (result != currentSeq) {
                SafeDelete();
                currentSeq = result;
            }
            std::cout << "Appended successfully.\n";
        } else if (choice == 2) {
            std::cout << "Enter item: ";
            int item;
            std::cin >> item;
            Sequence<int>* result = currentSeq->Prepend(item);
            if (result != currentSeq) {
                SafeDelete();
                currentSeq = result;
            }
            std::cout << "Prepended successfully.\n";
        } else if (choice == 3) {
            std::cout << "Enter item: ";
            int item;
            std::cin >> item;
            std::cout << "Enter index: ";
            int index;
            std::cin >> index;
            Sequence<int>* result = currentSeq->InsertAt(item, index);
            if (result != currentSeq) {
                SafeDelete();
                currentSeq = result;
            }
            std::cout << "Inserted successfully.\n";
        } else if (choice == 4) {
            std::cout << "Enter index: ";
            int index;
            std::cin >> index;
            int value = currentSeq->Get(index);
            std::cout << "Value at index " << index << ": " << value << "\n";
        } else if (choice == 5) {
            int value = currentSeq->GetFirst();
            std::cout << "First value: " << value << "\n";
        } else if (choice == 6) {
            int value = currentSeq->GetLast();
            std::cout << "Last value: " << value << "\n";
        } else if (choice == 7) {
            std::cout << "Enter start index: ";
            int start;
            std::cin >> start;
            std::cout << "Enter end index: ";
            int end;
            std::cin >> end;
            Sequence<int>* subSeq = currentSeq->GetSubsequence(start, end);
            std::cout << "Subsequence: ";
            for (int i = 0; i < subSeq->GetLength(); i++) {
                std::cout << subSeq->Get(i) << " ";
            }
            std::cout << "\n";
            delete subSeq;
        } else if (choice == 8) {
            Sequence<int>* tempSeq = nullptr;
            std::cout << "Creating new sequence for concatenation...\n";
            SelectSequenceType();
            tempSeq = currentSeq;
            currentSeq = currentSeq->Concat(tempSeq);
            delete tempSeq;
            std::cout << "Concatenated successfully.\n";
        } else if (choice == 9) {
            std::cout << "Length: " << currentSeq->GetLength() << "\n";
        } else {
            std::cout << "Invalid operation.\n";
        }
    } catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << "\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << "\n";
    } catch (const std::bad_alloc&) {
        std::cout << "Error: Memory allocation failed\n";
    }
}

void UI::PrintSequence() {
    std::cout << "Sequence: ";
    if (currentSeq->GetLength() == 0) {
        std::cout << "(empty)";
    } else {
        for (int i = 0; i < currentSeq->GetLength(); i++) {
            std::cout << currentSeq->Get(i) << " ";
        }
    }
    std::cout << "\n";
}

void UI::RunTests() {
    TestSuite tests;
    tests.RunAllTests();
}

void UI::SafeDelete() {
    if (currentSeq != nullptr) {
        delete currentSeq;
        currentSeq = nullptr;
    }
}
