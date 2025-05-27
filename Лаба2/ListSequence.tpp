#include "ListSequence.hpp"

template <class T>
ListSequence<T>::ListSequence() {
    list = new LinkedList<T>();
}

template <class T>
ListSequence<T>::ListSequence(T* items, int count) {
    if (count < 0) {
        throw std::invalid_argument("Count cannot be negative");
    }
    if (count > 0 && items == nullptr) {
        throw std::invalid_argument("Data cannot be null for non-zero count");
    }
    list = new LinkedList<T>(items, count);
}

template <class T>
ListSequence<T>::ListSequence(const LinkedList<T>& listCopy) {
    list = new LinkedList<T>(listCopy);
}

template <class T>
ListSequence<T>::~ListSequence() {
    delete list;
}

template <class T>
T ListSequence<T>::GetFirst() const {
    if (list->GetLength() == 0) {
        throw std::out_of_range("Sequence is empty");
    }
    return list->GetFirst();
}

template <class T>
T ListSequence<T>::GetLast() const {
    if (list->GetLength() == 0) {
        throw std::out_of_range("Sequence is empty");
    }
    return list->GetLast();
}

template <class T>
T ListSequence<T>::Get(int index) const {
    if (index < 0 || index >= list->GetLength()) {
        throw std::out_of_range("Index out of range");
    }
    return list->Get(index);
}

template <class T>
Sequence<T>* ListSequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex < 0 || startIndex >= list->GetLength() || endIndex >= list->GetLength()) {
        throw std::out_of_range("Invalid index");
    }
    if (startIndex > endIndex) {
        throw std::invalid_argument("startIndex must be less than or equal to endIndex");
    }
    ListSequence<T>* result = Clone();
    LinkedList<T>* subList = list->GetSubList(startIndex, endIndex);
    result->list = subList;
    return result;
}

template <class T>
int ListSequence<T>::GetLength() const {
    return list->GetLength();
}

template <class T>
Sequence<T>* ListSequence<T>::Append(T item) {
    return Instance()->AppendInternal(item);
}

template <class T>
Sequence<T>* ListSequence<T>::Prepend(T item) {
    return Instance()->PrependInternal(item);
}

template <class T>
Sequence<T>* ListSequence<T>::InsertAt(T item, int index) {
    return Instance()->InsertAtInternal(item, index);
}

template <class T>
Sequence<T>* ListSequence<T>::Concat(Sequence<T>* sequence) {
    return Instance()->ConcatInternal(sequence);
}

template <class T>
Sequence<T>* ListSequence<T>::AppendInternal(T item) {
    list->Append(item);
    return this;
}

template <class T>
Sequence<T>* ListSequence<T>::PrependInternal(T item) {
    list->Prepend(item);
    return this;
}

template <class T>
Sequence<T>* ListSequence<T>::InsertAtInternal(T item, int index) {
    if (index < 0 || index > list->GetLength()) {
        throw std::out_of_range("Index out of range");
    }
    list->InsertAt(item, index);
    return this;
}

template <class T>
Sequence<T>* ListSequence<T>::ConcatInternal(Sequence<T>* sequence) {
    if (sequence == nullptr) {
        throw std::invalid_argument("Sequence cannot be null");
    }
    for (int i = 0; i < sequence->GetLength(); i++) {
        list->Append(sequence->Get(i));
    }
    return this;
}

template <class T>
ListSequence<T>* MutableListSequence<T>::Instance() {
    return this;
}

template <class T>
ListSequence<T>* MutableListSequence<T>::Clone() const {
    MutableListSequence<T>* copy = new MutableListSequence<T>();
    for (int i = 0; i < this->list->GetLength(); i++) {
        copy->list->Append(this->list->Get(i));
    }
    return copy;
}

template <class T>
ListSequence<T>* ImmutableListSequence<T>::Instance() {
    return Clone();
}

template <class T>
ListSequence<T>* ImmutableListSequence<T>::Clone() const {
    ImmutableListSequence<T>* copy = new ImmutableListSequence<T>();
    for (int i = 0; i < this->list->GetLength(); i++) {
        copy->list->Append(this->list->Get(i));
    }
    return copy;
}
