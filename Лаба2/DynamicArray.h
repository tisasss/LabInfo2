#ifndef DynamicArray_h
#define DynamicArray_h

#include <stdexcept>

template <class T>
class DynamicArray {
public:
    DynamicArray();
    DynamicArray(T* data, int count);
    DynamicArray(int size);
    DynamicArray(const DynamicArray<T>& array);
    ~DynamicArray();
    DynamicArray<T>& operator=(const DynamicArray<T>& other);
    int GetSize() const;
    T Get(int index) const;
    T& GetRef(int index); // Новый метод для получения ссылки
    DynamicArray<T>& Set(int index, T data);
    DynamicArray<T>& Resize(int newSize);

private:
    int length;
    T* items;
};

#endif /* DynamicArray_h */
#include "DynamicArray.tpp"
