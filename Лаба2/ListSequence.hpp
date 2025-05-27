#pragma once

#include "Sequence.hpp"
#include "LinkedList.hpp"

template <class T>
class ListSequence : public Sequence<T> {
public:
    ListSequence();
    ListSequence(T* items, int count);
    ListSequence(const LinkedList<T>& list);
    virtual ~ListSequence();
    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    int GetLength() const override;
    Sequence<T>* Append(T item) override;
    Sequence<T>* Prepend(T item) override;
    Sequence<T>* InsertAt(T item, int index) override;
    Sequence<T>* Concat(Sequence<T>* list) override;

    T operator[](int index) const override {
        return Get(index);
    }
    T& operator[](int index) override {
        if (index < 0 || index >= list->GetLength()) throw std::out_of_range("Index out of range");
        return list->GetNode(index)->data;
    }

protected:
    LinkedList<T>* list;
    virtual ListSequence<T>* Instance() = 0;
    virtual ListSequence<T>* Clone() const = 0;
    Sequence<T>* AppendInternal(T item);
    Sequence<T>* PrependInternal(T item);
    Sequence<T>* InsertAtInternal(T item, int index);
    Sequence<T>* ConcatInternal(Sequence<T>* list);
};

template <class T>
class MutableListSequence : public ListSequence<T> {
public:
    MutableListSequence() : ListSequence<T>() {}
    MutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}
    MutableListSequence(const LinkedList<T>& list) : ListSequence<T>(list) {}
protected:
    ListSequence<T>* Instance() override;
    ListSequence<T>* Clone() const override;
};

template <class T>
class ImmutableListSequence : public ListSequence<T> {
public:
    ImmutableListSequence() : ListSequence<T>() {}
    ImmutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}
    ImmutableListSequence(const LinkedList<T>& list) : ListSequence<T>(list) {}
protected:
    ListSequence<T>* Instance() override;
    ListSequence<T>* Clone() const override;
};
#include "ListSequence.tpp"
