#pragma once
#include <stdexcept>

template <class T>
LinkedList<T>::LinkedList() {
    length = 0;
    first = nullptr;
    last = nullptr;
}

template <class T>
LinkedList<T>::LinkedList(T* items, unsigned int count) {
    if (count > 0 && items == nullptr) {
        throw std::invalid_argument("Data cannot be null for non-zero count");
    }
    length = 0;
    first = nullptr;
    last = nullptr;
    for (unsigned int i = 0; i < count; i++) {
        Append(items[i]);
    }
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    length = 0;
    first = nullptr;
    last = nullptr;
    Node<T>* current = list.first;
    while (current != nullptr) {
        Append(current->data);
        current = current->next;
    }
}

template <class T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = first;
    while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    first = nullptr;
    last = nullptr;
    length = 0;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this != &other) {
        Node<T>* current = first;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        first = nullptr;
        last = nullptr;
        length = 0;
        Node<T>* otherCurrent = other.first;
        while (otherCurrent != nullptr) {
            Append(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }
    }
    return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::Append(T value) {
    Node<T>* newNode = new Node<T>(value);
    if (length == 0) {
        first = newNode;
        last = newNode;
    } else {
        newNode->prev = last;
        last->next = newNode;
        last = newNode;
    }
    length++;
    return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::Prepend(T value) {
    Node<T>* newNode = new Node<T>(value);
    if (length == 0) {
        first = newNode;
        last = newNode;
    } else {
        newNode->next = first;
        first->prev = newNode;
        first = newNode;
    }
    length++;
    return *this;
}

template <class T>
int LinkedList<T>::GetLength() const {
    return length;
}

template <class T>
T LinkedList<T>::GetFirst() const {
    if (length == 0 || first == nullptr) {
        throw std::out_of_range("List is empty");
    }
    return first->data;
}

template <class T>
T LinkedList<T>::GetLast() const {
    if (length == 0 || last == nullptr) {
        throw std::out_of_range("List is empty");
    }
    return last->data;
}

template <class T>
T LinkedList<T>::Get(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }
    if (first == nullptr) {
        throw std::runtime_error("List is invalid");
    }
    Node<T>* current = first;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template <class T>
Node<T>* LinkedList<T>::GetNode(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }
    if (first == nullptr) {
        throw std::runtime_error("List is invalid");
    }
    Node<T>* current = first;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

template <class T>
LinkedList<T>& LinkedList<T>::InsertAt(T value, int index) {
    if (index < 0 || index > length) {
        throw std::out_of_range("Index out of range");
    }
    if (index == 0) {
        return Prepend(value);
    }
    if (index == length) {
        return Append(value);
    }
    Node<T>* newNode = new Node<T>(value);
    Node<T>* current = first;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    newNode->prev = current;
    newNode->next = current->next;
    current->next->prev = newNode;
    current->next = newNode;
    length++;
    return *this;
}

template <class T>
LinkedList<T>* LinkedList<T>::GetSubList(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex < 0 || startIndex >= length || endIndex >= length) {
        throw std::out_of_range("Invalid index");
    }
    if (startIndex > endIndex) {
        throw std::invalid_argument("startIndex must be less than or equal to endIndex");
    }
    LinkedList<T>* result = new LinkedList<T>();
    Node<T>* current = first;
    for (int i = 0; i < startIndex; i++) {
        current = current->next;
    }
    for (int i = startIndex; i <= endIndex; i++) {
        result->Append(current->data);
        current = current->next;
    }
    return result;
}

template <class T>
LinkedList<T>& LinkedList<T>::Concat(LinkedList<T>* list) {
    if (list == nullptr || list->GetLength() == 0) {
        return *this;
    }
    Node<T>* current = list->first;
    while (current != nullptr) {
        Append(current->data);
        current = current->next;
    }
    return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::RemoveAt(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }
    if (length == 0) {
        throw std::out_of_range("List is empty");
    }
    Node<T>* current = first;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    if (current->prev) {
        current->prev->next = current->next;
    } else {
        first = current->next;
    }
    if (current->next) {
        current->next->prev = current->prev;
    } else {
        last = current->prev;
    }
    delete current;
    length--;
    return *this;
}
