#ifndef LinkedList_hpp
#define LinkedList_hpp

#include <stdexcept>

template <class T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;
    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    Node() : next(nullptr), prev(nullptr) {}
};

template <class T>
class LinkedList {
public:
    LinkedList();
    LinkedList(T* items, unsigned int count);
    LinkedList(const LinkedList<T>& list);
    ~LinkedList();
    LinkedList<T>& operator=(const LinkedList<T>& other);
    LinkedList<T>& Append(T value);
    LinkedList<T>& Prepend(T value);
    int GetLength() const;
    T GetFirst() const;
    T GetLast() const;
    T Get(int index) const;
    LinkedList<T>& RemoveAt(int index);
    LinkedList<T>& InsertAt(T value, int index);
    LinkedList<T>* GetSubList(int startIndex, int endIndex) const;
    LinkedList<T>& Concat(LinkedList<T>* list);

    // Новый метод для доступа к узлу
    Node<T>* GetNode(int index) const;

private:
    int length;
    Node<T>* first;
    Node<T>* last;
};

#endif /* LinkedList_hpp */
#include "LinkedList.tpp"
