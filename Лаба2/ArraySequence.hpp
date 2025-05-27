#pragma once

#include "Sequence.hpp"
#include "DynamicArray.h"
#include "LinkedList.hpp"

template <class T>
class ArraySequence : public Sequence<T> {
public:
    ArraySequence();
    ArraySequence(T* items, int count);
    ArraySequence(const LinkedList<T>& list);
    virtual ~ArraySequence();
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
        if (index < 0 || index >= array->GetSize()) throw std::out_of_range("Index out of range");
        return array->GetRef(index); // Используем GetRef для возврата ссылки
    }

protected:
    DynamicArray<T>* array;
    virtual ArraySequence<T>* Instance() = 0;
    virtual ArraySequence<T>* Clone() const = 0;
    Sequence<T>* AppendInternal(T item);
    Sequence<T>* PrependInternal(T item);
    Sequence<T>* InsertAtInternal(T item, int index);
    Sequence<T>* ConcatInternal(Sequence<T>* list);
};

template <class T>
class MutableArraySequence : public ArraySequence<T> {
public:
    MutableArraySequence() : ArraySequence<T>() {}
    MutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    MutableArraySequence(const LinkedList<T>& list) : ArraySequence<T>(list) {}
protected:
    ArraySequence<T>* Instance() override;
    ArraySequence<T>* Clone() const override;
};

template <class T>
class ImmutableArraySequence : public ArraySequence<T> {
public:
    ImmutableArraySequence() : ArraySequence<T>() {}
    ImmutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    ImmutableArraySequence(const LinkedList<T>& list) : ArraySequence<T>(list) {}
protected:
    ArraySequence<T>* Instance() override;
    ArraySequence<T>* Clone() const override;
};
#include "ArraySequence.tpp"
