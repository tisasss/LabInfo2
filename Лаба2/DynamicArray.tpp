#pragma once
#include <stdexcept>
#include <algorithm>

template <class T>
DynamicArray<T>::DynamicArray() {
    length = 0;
    items = nullptr;
}

template <class T>
DynamicArray<T>::DynamicArray(T* data, int count) {
    if (count < 0) {
        throw std::invalid_argument("Count cannot be negative");
    }
    if (count > 0 && data == nullptr) {
        throw std::invalid_argument("Data cannot be null for non-zero count");
    }
    length = count;
    items = count > 0 ? new T[count] : nullptr;
    for (int i = 0; i < count; i++) {
        items[i] = data[i];
    }
}

template <class T>
DynamicArray<T>::DynamicArray(int size) {
    if (size < 0) {
        throw std::invalid_argument("Size cannot be negative");
    }
    length = size;
    items = size > 0 ? new T[size] : nullptr;
    for (int i = 0; i < size; i++) {
        items[i] = T();
    }
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& array) {
    length = array.length;
    items = length > 0 ? new T[length] : nullptr;
    for (int i = 0; i < length; i++) {
        items[i] = array.items[i];
    }
}

template <class T>
DynamicArray<T>::~DynamicArray() {
    delete[] items;
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if (this != &other) {
        delete[] items;
        length = other.length;
        items = length > 0 ? new T[length] : nullptr;
        for (int i = 0; i < length; i++) {
            items[i] = other.items[i];
        }
    }
    return *this;
}

template <class T>
int DynamicArray<T>::GetSize() const {
    return length;
}

template <class T>
T DynamicArray<T>::Get(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return items[index];
}

template <class T>
T& DynamicArray<T>::GetRef(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return items[index];
}

template <class T>
DynamicArray<T>& DynamicArray<T>::Set(int index, T data) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }
    items[index] = data;
    return *this;
}

template <class T>
DynamicArray<T>& DynamicArray<T>::Resize(int newSize) {
    if (newSize < 0) {
        throw std::invalid_argument("New size cannot be negative");
    }
    T* newItems = newSize > 0 ? new T[newSize] : nullptr;
    int copySize = std::min(length, newSize);
    for (int i = 0; i < copySize; i++) {
        newItems[i] = items[i];
    }
    for (int i = copySize; i < newSize; i++) {
        newItems[i] = T();
    }
    delete[] items;
    items = newItems;
    length = newSize;
    return *this;
}
