
template <class T>
ArraySequence<T>::ArraySequence() {
    array = new DynamicArray<T>(0);
}

template <class T>
ArraySequence<T>::ArraySequence(T* items, int count) {
    if (count < 0) {
        throw std::invalid_argument("Count cannot be negative");
    }
    if (count > 0 && items == nullptr) {
        throw std::invalid_argument("Data cannot be null for non-zero count");
    }
    array = new DynamicArray<T>(items, count);
}

template <class T>
ArraySequence<T>::ArraySequence(const LinkedList<T>& list) {
    array = new DynamicArray<T>(list.GetLength());
    for (int i = 0; i < list.GetLength(); i++) {
        array->Set(i, list.Get(i));
    }
}

template <class T>
ArraySequence<T>::~ArraySequence() {
    delete array;
}

template <class T>
T ArraySequence<T>::GetFirst() const {
    if (array->GetSize() == 0) {
        throw std::out_of_range("Sequence is empty");
    }
    return array->Get(0);
}

template <class T>
T ArraySequence<T>::GetLast() const {
    if (array->GetSize() == 0) {
        throw std::out_of_range("Sequence is empty");
    }
    return array->Get(array->GetSize() - 1);
}

template <class T>
T ArraySequence<T>::Get(int index) const {
    if (index < 0 || index >= array->GetSize()) {
        throw std::out_of_range("Index out of range");
    }
    return array->Get(index);
}

template <class T>
Sequence<T>* ArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex < 0 || startIndex >= array->GetSize() || endIndex >= array->GetSize()) {
        throw std::out_of_range("Invalid index");
    }
    if (startIndex > endIndex) {
        throw std::invalid_argument("startIndex must be less than or equal to endIndex");
    }
    ArraySequence<T>* result = Clone();
    result->array->Resize(endIndex - startIndex + 1);
    for (int i = startIndex; i <= endIndex; i++) {
        result->array->Set(i - startIndex, array->Get(i));
    }
    return result;
}

template <class T>
int ArraySequence<T>::GetLength() const {
    return array->GetSize();
}

template <class T>
Sequence<T>* ArraySequence<T>::Append(T item) {
    return Instance()->AppendInternal(item);
}

template <class T>
Sequence<T>* ArraySequence<T>::Prepend(T item) {
    return Instance()->PrependInternal(item);
}

template <class T>
Sequence<T>* ArraySequence<T>::InsertAt(T item, int index) {
    return Instance()->InsertAtInternal(item, index);
}

template <class T>
Sequence<T>* ArraySequence<T>::Concat(Sequence<T>* list) {
    return Instance()->ConcatInternal(list);
}

template <class T>
Sequence<T>* ArraySequence<T>::AppendInternal(T item) {
    array->Resize(array->GetSize() + 1);
    array->Set(array->GetSize() - 1, item);
    return this;
}

template <class T>
Sequence<T>* ArraySequence<T>::PrependInternal(T item) {
    array->Resize(array->GetSize() + 1);
    for (int i = array->GetSize() - 1; i > 0; i--) {
        array->Set(i, array->Get(i - 1));
    }
    array->Set(0, item);
    return this;
}

template <class T>
Sequence<T>* ArraySequence<T>::InsertAtInternal(T item, int index) {
    if (index < 0 || index > array->GetSize()) {
        throw std::out_of_range("Index out of range");
    }
    array->Resize(array->GetSize() + 1);
    for (int i = array->GetSize() - 1; i > index; i--) {
        array->Set(i, array->Get(i - 1));
    }
    array->Set(index, item);
    return this;
}

template <class T>
Sequence<T>* ArraySequence<T>::ConcatInternal(Sequence<T>* list) {
    if (list == nullptr) {
        throw std::invalid_argument("List cannot be null");
    }
    int oldSize = array->GetSize();
    array->Resize(oldSize + list->GetLength());
    for (int i = 0; i < list->GetLength(); i++) {
        array->Set(oldSize + i, list->Get(i));
    }
    return this;
}

template <class T>
ArraySequence<T>* MutableArraySequence<T>::Instance() {
    return this;
}

template <class T>
ArraySequence<T>* MutableArraySequence<T>::Clone() const {
    MutableArraySequence<T>* copy = new MutableArraySequence<T>();
    copy->array->Resize(this->array->GetSize());
    for (int i = 0; i < this->array->GetSize(); i++) {
        copy->array->Set(i, this->array->Get(i));
    }
    return copy;
}

template <class T>
ArraySequence<T>* ImmutableArraySequence<T>::Instance() {
    return Clone();
}

template <class T>
ArraySequence<T>* ImmutableArraySequence<T>::Clone() const {
    ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>();
    copy->array->Resize(this->array->GetSize());
    for (int i = 0; i < this->array->GetSize(); i++) {
        copy->array->Set(i, this->array->Get(i));
    }
    return copy;
}
